// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <dbghelp.h>
#include <fstream>
#include <memory>
#include <algorithm>
#include <vector>
#include <sstream>
#include <Objbase.h>
#include <MMSystem.h>
#include <GdiPlus.h>
#include <d3d9.h>
#include "git.h"
#include "CodeParser.hpp"
#include "IniFile.hpp"
#include "TextConv.hpp"
#include "FileMap.hpp"
#include "FileSystem.h"
#include "FileReplacement.h"
#include "Events.h"
#include "SonicRModLoader.h"
#include "bass_vgmstream.h"

using std::ifstream;
using std::string;
using std::wstring;
using std::unique_ptr;
using std::vector;
using std::unordered_map;

/**
* Hook Sonic R's CreateFileA() import.
*/
static void HookCreateFileA(void)
{
	ULONG ulSize = 0;
	PROC pNewFunction;
	PROC pActualFunction;

	PCSTR pcszModName;

	// SADX module handle. (main executable)
	HMODULE hModule = GetModuleHandle(nullptr);
	PIMAGE_IMPORT_DESCRIPTOR pImportDesc;

	pNewFunction = (PROC)MyCreateFileA;
	// Get the actual CreateFileA() using GetProcAddress().
	pActualFunction = GetProcAddress(GetModuleHandle(L"Kernel32.dll"), "CreateFileA");

	pImportDesc = (PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToData(
		hModule, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &ulSize);

	if (pImportDesc == nullptr)
		return;

	for (; pImportDesc->Name; pImportDesc++)
	{
		// get the module name
		pcszModName = (PCSTR)((PBYTE)hModule + pImportDesc->Name);

		// check if the module is kernel32.dll
		if (pcszModName != nullptr && _stricmp(pcszModName, "Kernel32.dll") == 0)
		{
			// get the module
			PIMAGE_THUNK_DATA pThunk = (PIMAGE_THUNK_DATA)((PBYTE)hModule + pImportDesc->FirstThunk);

			for (; pThunk->u1.Function; pThunk++)
			{
				PROC* ppfn = (PROC*)&pThunk->u1.Function;
				if (*ppfn == pActualFunction)
				{
					// Found CreateFileA().
					DWORD dwOldProtect = 0;
					VirtualProtect(ppfn, sizeof(pNewFunction), PAGE_WRITECOPY, &dwOldProtect);
					WriteData(ppfn, pNewFunction);
					VirtualProtect(ppfn, sizeof(pNewFunction), dwOldProtect, &dwOldProtect);
					// FIXME: Would it be listed multiple times?
					break;
				} // Function that we are looking for
			}
		}
	}
}

void CheckPauseMusic();
// Code Parser.
static CodeParser codeParser;

static void __cdecl ProcessCodes(int fps)
{
	codeParser.processCodeList();
	RaiseEvents(modFrameEvents);
	CheckPauseMusic();
	int v1 = 1000 / fps;
	int v2 = abs(GetTime() - FrameStartTime);
	if (v2 < v1)
	{
		do
		{
			if (v1 - v2 > 1)
				Sleep((v1 - v2) >> 1);
			v2 = abs(GetTime() - FrameStartTime);
		} while (v2 < v1);
	}
	FrameEndTime = 1000 / (v2 + 1);
}

static bool dbgConsole;
// File for logging debugging output.
static FILE *dbgFile = nullptr;

/**
* Sonic R Debug Output function.
* @param Format Format string.
* @param args Arguments.
* @return Return value from vsnprintf().
*/
static int __cdecl SonicRDebugOutput(const char *Format, ...)
{
	va_list ap;
	va_start(ap, Format);
	int result = vsnprintf(nullptr, 0, Format, ap) + 1;
	va_end(ap);
	char *buf = new char[result + 1];
	va_start(ap, Format);
	result = vsnprintf(buf, result + 1, Format, ap);
	va_end(ap);

	// Console output.
	if (dbgConsole)
	{
		fputs(buf, stdout);
		fflush(stdout);
	}

	// File output.
	if (dbgFile)
	{
		fputs(buf, dbgFile);
		fflush(dbgFile);
	}

	delete[] buf;
	return result;
}

/**
* Callback for BASS. Called when it needs more data.
*/
DWORD CALLBACK rawStreamProc(HSTREAM handle, void *buffer, DWORD length, void *user)
{
	FILE *file = (FILE*)user;
	DWORD c = fread(buffer, 1, length, file); // read the file into the buffer
	if (feof(file)) c |= BASS_STREAMPROC_END; // end of the file/stream
	return c;
}

/**
* Called when the BASS handle is closed
*/
void CALLBACK rawStreamOnFree(HSYNC handle, DWORD channel, DWORD data, void *user)
{
	fclose((FILE*)user);
}

bool bassinit = false;
void InitMusic()
{
	bassinit = BASS_Init(-1, 44100, 0, nullptr, nullptr) ? true : false;
}

void DeInitMusic()
{
	if (bassinit)
	{
		BASS_Free();
		bassinit = false;
	}
}

int GetCurrentTrackNumber()
{
	return CurrentMusicTrack;
}

static void __stdcall onTrackEnd(HSYNC handle, DWORD channel, DWORD data, void *user)
{
	BASS_ChannelStop(channel);
	BASS_StreamFree(channel);
	CurrentMusicTrack = -1;
	*(int*)0x502F0C = 0;
}

float volumelevels[] = { 0, 0.002511886f, 0.007079458f, 0.031622777f, 0.079432823f, 0.125892541f, 0.354813389f, 0.630957344f, 1 };
int basschan = 0;
int wasPaused = 0;
DataPointer(int, IsGamePaused, 0x7C1BC0);
void PlayMusic(int track)
{
	if (!bassinit) return;
	if (basschan != 0)
	{
		BASS_ChannelStop(basschan);
		BASS_StreamFree(basschan);
	}
	char buf[MAX_PATH];
	snprintf(buf, sizeof(buf), "music\\track%u.son", track);
	const char *filename = fileMap.replaceFile(buf);
	basschan = BASS_VGMSTREAM_StreamCreate(filename, 0);
	if (basschan == 0)
		basschan = BASS_StreamCreateFile(false, filename, 0, 0, 0);
	if (basschan == 0)
	{
		FILE *file = fopen(filename, "rb");
		if (file)
		{
			basschan = BASS_StreamCreate(44100, 2, 0, rawStreamProc, file);
			if (basschan != 0)
				BASS_ChannelSetSync(basschan, BASS_SYNC_FREE | BASS_SYNC_MIXTIME, 0, rawStreamOnFree, file);
		}
	}
	if (basschan != 0)
	{
		// Stream opened!
		BASS_ChannelPlay(basschan, false);
		BASS_ChannelSetAttribute(basschan, BASS_ATTRIB_VOL, volumelevels[MusicVolume]);
		BASS_ChannelSetSync(basschan, BASS_SYNC_END, 0, onTrackEnd, nullptr);
		CurrentMusicTrack = track;
		*(int*)0x502F0C = 1;
		wasPaused = IsGamePaused = 0;
	}
	else
	{
		CurrentMusicTrack = -1;
		*(int*)0x502F0C = 0;
		PrintDebug("Could not play music file \"%s\".", filename);
	}
}

void StopMusic_r()
{
	if (basschan != 0)
	{
		BASS_ChannelStop(basschan);
		BASS_StreamFree(basschan);
		CurrentMusicTrack = -1;
		*(int*)0x502F0C = 0;
	}
}

void UpdateMusicVolume_r()
{
	if (basschan != 0)
		BASS_ChannelSetAttribute(basschan, BASS_ATTRIB_VOL, volumelevels[MusicVolume]);
}

void CheckPauseMusic()
{
	if (basschan != 0)
	{
		if (wasPaused && !IsGamePaused)
			BASS_ChannelPlay(basschan, false);
		else if (!wasPaused && IsGamePaused)
			BASS_ChannelPause(basschan);
		wasPaused = IsGamePaused;
	}
}

static Gdiplus::Bitmap* backgroundImage = nullptr;
enum windowmodes { windowed, fullscreen };
struct windowsize { int x; int y; int width; int height; };
struct windowdata { int x; int y; int width; int height; DWORD style; DWORD exStyle; };

// Used for borderless windowed mode.
// Defines the size of the outer-window which wraps the game window and draws the background.
static windowdata outerSizes[] = {
	{ CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, WS_CAPTION | WS_SYSMENU | WS_VISIBLE, 0 }, // windowed
	{ 0, 0, CW_USEDEFAULT, CW_USEDEFAULT, WS_POPUP | WS_VISIBLE, WS_EX_APPWINDOW } // fullscreen
};

// Used for borderless windowed mode.
// Defines the size of the inner-window on which the game is rendered.
static windowsize innerSizes[2] = {};

static WNDCLASS outerWindowClass = {};
static HWND accelWindow = nullptr;
static windowmodes windowMode = windowmodes::windowed;

static LRESULT CALLBACK WrapperWndProc(HWND wrapper, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		SendMessage(hWnd, WM_CLOSE, wParam, lParam);
		return 0;

	case WM_ERASEBKGND:
	{
		if (backgroundImage == nullptr)
		{
			break;
		}

		Gdiplus::Graphics gfx((HDC)wParam);
		gfx.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);

		RECT rect;
		GetClientRect(wrapper, &rect);

		auto w = rect.right - rect.left;
		auto h = rect.bottom - rect.top;

		if (w == innerSizes[windowMode].width && h == innerSizes[windowMode].height)
		{
			break;
		}

		gfx.DrawImage(backgroundImage, 0, 0, w, h);
		return 0;
	}

	default:
		break;
	}

	// alternatively we can return SendMe
	return DefWindowProc(wrapper, uMsg, wParam, lParam);
}

void __cdecl SetPresentParameters(D3DPRESENT_PARAMETERS *pp, D3DFORMAT bufferFormat, D3DFORMAT depthStencilFormat, int bufferWidth, signed int bufferHeight, int refreshRate, int windowed)
{
	memset(pp, 0, sizeof(D3DPRESENT_PARAMETERS));
	pp->AutoDepthStencilFormat = depthStencilFormat;
	pp->SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp->EnableAutoDepthStencil = 1;
	pp->Windowed = windowed;
	pp->BackBufferFormat = bufferFormat;
	pp->BackBufferWidth = bufferWidth;
	pp->BackBufferHeight = bufferHeight;
	pp->FullScreen_RefreshRateInHz = refreshRate;
	pp->hDeviceWindow = hWnd;
}

StdcallFunctionPointer(int, _WinMain, (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd), 0x4330A0);
FunctionPointer(int, sub_432F10, (int *a1), 0x432F10);
FunctionPointer(int, sub_432EB0, (char a1), 0x432EB0);
VoidFunc(sub_432F90, 0x432F90);
FunctionPointer(void, sub_404CB0, (HWND hwnd), 0x404CB0);
FunctionPointer(void, sub_442070, (HWND hwnd), 0x442070);
int __stdcall InitMods(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	FILE *f_ini = _wfopen(L"mods\\SonicRModLoader.ini", L"r");
	if (!f_ini)
	{
		MessageBox(nullptr, L"mods\\SonicRModLoader.ini could not be read!", L"Sonic R Mod Loader", MB_ICONWARNING);
		return _WinMain(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
	}
	unique_ptr<IniFile> ini(new IniFile(f_ini));
	fclose(f_ini);

	HookCreateFileA();

	TIMECAPS tc;
	timeGetDevCaps(&tc, sizeof(tc));
	timeBeginPeriod(tc.wPeriodMin);

	// Get exe's path and filename.
	wchar_t pathbuf[MAX_PATH];
	GetModuleFileName(nullptr, pathbuf, MAX_PATH);
	wstring exepath(pathbuf);
	wstring exefilename;
	string::size_type slash_pos = exepath.find_last_of(L"/\\");
	if (slash_pos != string::npos)
	{
		exefilename = exepath.substr(slash_pos + 1);
		if (slash_pos > 0)
			exepath = exepath.substr(0, slash_pos);
	}

	// Convert the EXE filename to lowercase.
	transform(exefilename.begin(), exefilename.end(), exefilename.begin(), ::towlower);

	// Process the main Mod Loader settings.
	const IniGroup *settings = ini->getGroup("");

	if (settings->getBool("DebugConsole"))
	{
		// Enable the debug console.
		// TODO: setvbuf()?
		AllocConsole();
		SetConsoleTitle(L"Sonic R Mod Loader output");
		freopen("CONOUT$", "wb", stdout);
		dbgConsole = true;
	}

	if (settings->getBool("DebugFile"))
	{
		// Enable debug logging to a file.
		// dbgFile will be nullptr if the file couldn't be opened.
		dbgFile = _wfopen(L"mods\\SonicRModLoader.log", L"a+");
	}

	// Is any debug method enabled?
	if (dbgConsole || dbgFile)
	{
		WriteJump(PrintDebug, SonicRDebugOutput);
		WriteData((void**)0x404BD3, (void*)&SonicRDebugOutput);
		// There's a couple other functions that were compiled out and got merged with the debug printing function.
		// This code replaces those calls with nops, otherwise the game would crash on invalid pointers, or print garbage.
		char jmpnop[5] = { 0x90u, 0x90u, 0x90u, 0x90u, 0x90u };
		WriteData((void*)0x43AB3D, jmpnop);
		WriteData((void*)0x43A567, jmpnop);
		WriteData((void*)0x43A843, jmpnop);
		WriteData((void*)0x41489E, jmpnop);
		WriteData((void*)0x41534D, jmpnop);
		WriteData((void*)0x41DA7B, jmpnop);
		WriteData((void*)0x43844A, jmpnop);
		WriteData((void*)0x41C477, jmpnop);
		WriteData((void*)0x41C485, jmpnop);
		WriteData((void*)0x41C425, jmpnop);
		WriteData((void*)0x41C433, jmpnop);
		PrintDebug("Sonic R Mod Loader (API version %d), built " __TIMESTAMP__ "\n",
			ModLoaderVer);
#ifdef MODLOADER_GIT_VERSION
#ifdef MODLOADER_GIT_DESCRIBE
		PrintDebug("%s, %s\n", MODLOADER_GIT_VERSION, MODLOADER_GIT_DESCRIBE);
#else /* !MODLOADER_GIT_DESCRIBE */
		PrintDebug("%s\n", MODLOADER_GIT_VERSION);
#endif /* MODLOADER_GIT_DESCRIBE */
#endif /* MODLOADER_GIT_VERSION */
	}

	Windowed = settings->getBool("Windowed");

	int hres = settings->getInt("HorizontalResolution", 640);
	if (hres > 0)
		HorizontalResolution = hres;

	int vres = settings->getInt("VerticalResolution", 480);
	if (vres > 0)
		VerticalResolution = vres;

	bool borderlessWindow = settings->getBool("WindowedFullscreen");
	bool scaleScreen = settings->getBool("StretchFullscreen", true);
	bool customWindowSize = settings->getBool("CustomWindowSize");
	int customWindowWidth = settings->getInt("WindowWidth", 640);
	int customWindowHeight = settings->getInt("WindowHeight", 480);

	*(int*)0x502F18 = 1;
	*(int*)0x502F1C = 1;
	WriteData<6>((void*)0x43A6DF, 0x90u);
	WriteData((char*)0x43D050, (char)0xC3u); // FindSonicRCD
	WriteCall((void*)0x43CB26, InitMusic);
	WriteJump((void*)0x43CB2B, (void*)0x43CB6D);
	WriteCall((void*)0x43CEAA, DeInitMusic);
	WriteJump((void*)0x43CEAF, (void*)0x43CECA);
	WriteJump(GetCurrentMusicTrack, GetCurrentTrackNumber);
	WriteData((char*)0x43C1F0, (char)0xC3u); // SetMusicPlayerEmptyDiscPath
	WriteJump(PlayMusicTrack, PlayMusic);
	WriteJump(StopMusic, StopMusic_r);
	WriteJump(UpdateMusicVolume, UpdateMusicVolume_r);

	fileMap.scanSoundFolder("music");

	// Map of files to replace and/or swap.
	// This is done with a second map instead of fileMap directly
	// in order to handle multiple mods.
	unordered_map<string, string> filereplaces;

	vector<std::pair<ModInitFunc, string>> initfuncs;
	vector<std::pair<string, string>> errors;

	PrintDebug("Loading mods...\n");
	for (unsigned int i = 1; i <= 999; i++)
	{
		char key[8];
		snprintf(key, sizeof(key), "Mod%u", i);
		if (!settings->hasKey(key))
			break;

		const string mod_dirA = "mods\\" + settings->getString(key);
		const wstring mod_dir = L"mods\\" + settings->getWString(key);
		const wstring mod_inifile = mod_dir + L"\\mod.ini";
		FILE *f_mod_ini = _wfopen(mod_inifile.c_str(), L"r");
		if (!f_mod_ini)
		{
			PrintDebug("Could not open file mod.ini in \"mods\\%s\".\n", mod_dirA.c_str());
			errors.push_back(std::pair<string, string>(mod_dirA, "mod.ini missing"));
			continue;
		}
		unique_ptr<IniFile> ini_mod(new IniFile(f_mod_ini));
		fclose(f_mod_ini);

		const IniGroup *const modinfo = ini_mod->getGroup("");
		const string mod_nameA = modinfo->getString("Name");
		PrintDebug("%u. %s\n", i, mod_nameA.c_str());

		if (ini_mod->hasGroup("IgnoreFiles"))
		{
			const IniGroup *group = ini_mod->getGroup("IgnoreFiles");
			auto data = group->data();
			for (unordered_map<string, string>::const_iterator iter = data->begin();
				iter != data->end(); ++iter)
			{
				fileMap.addIgnoreFile(iter->first, i);
				PrintDebug("Ignored file: %s\n", iter->first.c_str());
			}
		}

		if (ini_mod->hasGroup("ReplaceFiles"))
		{
			const IniGroup *group = ini_mod->getGroup("ReplaceFiles");
			auto data = group->data();
			for (unordered_map<string, string>::const_iterator iter = data->begin();
				iter != data->end(); ++iter)
			{
				filereplaces[FileMap::normalizePath(iter->first)] =
					FileMap::normalizePath(iter->second);
			}
		}

		if (ini_mod->hasGroup("SwapFiles"))
		{
			const IniGroup *group = ini_mod->getGroup("SwapFiles");
			auto data = group->data();
			for (unordered_map<string, string>::const_iterator iter = data->begin();
				iter != data->end(); ++iter)
			{
				filereplaces[FileMap::normalizePath(iter->first)] =
					FileMap::normalizePath(iter->second);
				filereplaces[FileMap::normalizePath(iter->second)] =
					FileMap::normalizePath(iter->first);
			}
		}

		// Check for Data replacements.
		const string modSysDirA = mod_dirA + "\\files";
		if (DirectoryExists(modSysDirA))
			fileMap.scanFolder(modSysDirA, i);

		// Check if the mod has a DLL file.
		if (modinfo->hasKeyNonEmpty("DLLFile"))
		{
			// Prepend the mod directory.
			// TODO: SetDllDirectory().
			wstring dll_filename = mod_dir + L'\\' + modinfo->getWString("DLLFile");
			HMODULE module = LoadLibrary(dll_filename.c_str());
			if (module == nullptr)
			{
				DWORD error = GetLastError();
				LPSTR buffer;
				size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
					nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&buffer, 0, nullptr);

				string message(buffer, size);
				LocalFree(buffer);

				const string dll_filenameA = UTF16toMBS(dll_filename, CP_ACP);
				PrintDebug("Failed loading mod DLL \"%s\": %s\n", dll_filenameA.c_str(), message.c_str());
				errors.push_back(std::pair<string, string>(mod_nameA, "DLL error - " + message));
			}
			else
			{
				const ModInfo *info = (const ModInfo *)GetProcAddress(module, "SonicRModInfo");
				if (info)
				{
					const ModInitFunc init = (const ModInitFunc)GetProcAddress(module, "Init");
					if (init)
						initfuncs.push_back({ init, mod_dirA });
					const PatchList *patches = (const PatchList *)GetProcAddress(module, "Patches");
					if (patches)
						for (int j = 0; j < patches->Count; j++)
							WriteData(patches->Patches[j].address, patches->Patches[j].data, patches->Patches[j].datasize);
					const PointerList *jumps = (const PointerList *)GetProcAddress(module, "Jumps");
					if (jumps)
						for (int j = 0; j < jumps->Count; j++)
							WriteJump(jumps->Pointers[j].address, jumps->Pointers[j].data);
					const PointerList *calls = (const PointerList *)GetProcAddress(module, "Calls");
					if (calls)
						for (int j = 0; j < calls->Count; j++)
							WriteCall(calls->Pointers[j].address, calls->Pointers[j].data);
					const PointerList *pointers = (const PointerList *)GetProcAddress(module, "Pointers");
					if (pointers)
						for (int j = 0; j < pointers->Count; j++)
							WriteData((void **)pointers->Pointers[j].address, pointers->Pointers[j].data);
					RegisterEvent(modFrameEvents, module, "OnFrame");
				}
				else
				{
					const string dll_filenameA = UTF16toMBS(dll_filename, CP_ACP);
					PrintDebug("File \"%s\" is not a valid mod file.\n", dll_filenameA.c_str());
					errors.push_back(std::pair<string, string>(mod_nameA, "Not a valid mod file."));
				}
			}
		}
	}

	if (!errors.empty())
	{
		std::stringstream message;
		message << "The following mods didn't load correctly:" << std::endl;

		for (auto& i : errors)
			message << std::endl << i.first << ": " << i.second;

		MessageBoxA(nullptr, message.str().c_str(), "Mods failed to load", MB_OK | MB_ICONERROR);
	}

	// Replace filenames. ("ReplaceFiles", "SwapFiles")
	for (auto iter = filereplaces.cbegin(); iter != filereplaces.cend(); ++iter)
	{
		fileMap.addReplaceFile(iter->first, iter->second);
	}

	for (unsigned int i = 0; i < initfuncs.size(); i++)
		initfuncs[i].first(initfuncs[i].second.c_str());

	PrintDebug("Finished loading mods\n");

	// Check for patches.
	ifstream patches_str("mods\\Patches.dat", ifstream::binary);
	if (patches_str.is_open())
	{
		CodeParser patchParser;
		static const char codemagic[6] = { 'c', 'o', 'd', 'e', 'v', '5' };
		char buf[sizeof(codemagic)];
		patches_str.read(buf, sizeof(buf));
		if (!memcmp(buf, codemagic, sizeof(codemagic)))
		{
			int codecount_header;
			patches_str.read((char*)&codecount_header, sizeof(codecount_header));
			PrintDebug("Loading %d patches...\n", codecount_header);
			patches_str.seekg(0);
			int codecount = patchParser.readCodes(patches_str);
			if (codecount >= 0)
			{
				PrintDebug("Loaded %d patches.\n", codecount);
				patchParser.processCodeList();
			}
			else
			{
				PrintDebug("ERROR loading patches: ");
				switch (codecount)
				{
				case -EINVAL:
					PrintDebug("Patch file is not in the correct format.\n");
					break;
				default:
					PrintDebug("%s\n", strerror(-codecount));
					break;
				}
			}
		}
		else
		{
			PrintDebug("Patch file is not in the correct format.\n");
		}
		patches_str.close();
	}

	// Check for codes.
	ifstream codes_str("mods\\Codes.dat", ifstream::binary);
	if (codes_str.is_open())
	{
		static const char codemagic[6] = { 'c', 'o', 'd', 'e', 'v', '5' };
		char buf[sizeof(codemagic)];
		codes_str.read(buf, sizeof(buf));
		if (!memcmp(buf, codemagic, sizeof(codemagic)))
		{
			int codecount_header;
			codes_str.read((char*)&codecount_header, sizeof(codecount_header));
			PrintDebug("Loading %d codes...\n", codecount_header);
			codes_str.seekg(0);
			int codecount = codeParser.readCodes(codes_str);
			if (codecount >= 0)
			{
				PrintDebug("Loaded %d codes.\n", codecount);
				codeParser.processCodeList();
			}
			else
			{
				PrintDebug("ERROR loading codes: ");
				switch (codecount)
				{
				case -EINVAL:
					PrintDebug("Code file is not in the correct format.\n");
					break;
				default:
					PrintDebug("%s\n", strerror(-codecount));
					break;
				}
			}
		}
		else
		{
			PrintDebug("Code file is not in the correct format.\n");
		}
		codes_str.close();
	}

	WriteJump(FrameDelay, ProcessCodes);

	WriteData<6>((void*)0x404DED, 0x90u);
	WriteCall((void*)0x442131, SetPresentParameters);

	ProcessCommandLine(lpCmdLine);
	CalculateClockSpeed();
	unsigned int v4 = (signed int)(*(int*)0x7A9FD8 + ((unsigned __int64)(0xFFFFFFFF88888889i64 * *(int*)0x7A9FD8) >> 32)) >> 4;
	*(int*)0x7AF078 = (v4 >> 31) + v4;
	if (sub_432F10((int*)0x45F67C))
		sub_432EB0(2u);
	sub_432F90();
	::hInstance = hInstance;
	WndClass.style = CS_NOCLOSE | CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)0x433080;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIconA(hInstance, MAKEINTRESOURCEA(101));
	WndClass.hCursor = LoadCursor(0, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = 0;
	WndClass.lpszClassName = WindowName;
	if (!RegisterClassA(&WndClass))
		goto end;
	CoInitialize(0);
	RECT windowRect;
	windowRect.top = 0;
	windowRect.left = 0;
	if (customWindowSize)
	{
		windowRect.right = customWindowWidth;
		windowRect.bottom = customWindowHeight;
	}
	else
	{
		windowRect.right = HorizontalResolution;
		windowRect.bottom = VerticalResolution;
	}

	int screenX, screenY, screenW, screenH, wsX, wsY, wsW, wsH;
	screenX = wsX = 0;
	screenY = wsY = 0;
	screenW = wsW = GetSystemMetrics(SM_CXSCREEN);
	screenH = wsH = GetSystemMetrics(SM_CYSCREEN);

	if (borderlessWindow)
	{
		AdjustWindowRectEx(&windowRect, outerSizes[windowed].style, false, 0);

		outerSizes[windowed].width = windowRect.right - windowRect.left;
		outerSizes[windowed].height = windowRect.bottom - windowRect.top;

		outerSizes[windowed].x = wsX + ((wsW - outerSizes[windowed].width) / 2);
		outerSizes[windowed].y = wsY + ((wsH - outerSizes[windowed].height) / 2);

		outerSizes[fullscreen].x = screenX;
		outerSizes[fullscreen].y = screenY;
		outerSizes[fullscreen].width = screenW;
		outerSizes[fullscreen].height = screenH;

		if (customWindowSize)
		{
			float num = min((float)customWindowWidth / (float)HorizontalResolution, (float)customWindowHeight / (float)VerticalResolution);
			innerSizes[windowed].width = (int)((float)HorizontalResolution * num);
			innerSizes[windowed].height = (int)((float)VerticalResolution * num);
			innerSizes[windowed].x = (customWindowWidth - innerSizes[windowed].width) / 2;
			innerSizes[windowed].y = (customWindowHeight - innerSizes[windowed].height) / 2;
		}
		else
		{
			innerSizes[windowed].width = HorizontalResolution;
			innerSizes[windowed].height = VerticalResolution;
			innerSizes[windowed].x = 0;
			innerSizes[windowed].y = 0;
		}

		if (scaleScreen)
		{
			float num = min((float)screenW / (float)HorizontalResolution, (float)screenH / (float)VerticalResolution);
			innerSizes[fullscreen].width = (int)((float)HorizontalResolution * num);
			innerSizes[fullscreen].height = (int)((float)VerticalResolution * num);
		}
		else
		{
			innerSizes[fullscreen].width = HorizontalResolution;
			innerSizes[fullscreen].height = VerticalResolution;
		}

		innerSizes[fullscreen].x = (screenW - innerSizes[fullscreen].width) / 2;
		innerSizes[fullscreen].y = (screenH - innerSizes[fullscreen].height) / 2;

		windowMode = Windowed ? windowed : fullscreen;

		if (FileExists(L"mods\\Border.png"))
		{
			Gdiplus::GdiplusStartupInput gdiplusStartupInput;
			ULONG_PTR gdiplusToken;
			Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
			backgroundImage = Gdiplus::Bitmap::FromFile(L"mods\\Border.png");
		}

		// Register a window class for the wrapper window.
		WNDCLASS w;
		w.style = CS_NOCLOSE;
		w.lpfnWndProc = WrapperWndProc;
		w.cbClsExtra = 0;
		w.cbWndExtra = 0;
		w.hInstance = hInstance;
		w.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(101));
		w.hCursor = LoadCursor(nullptr, IDC_ARROW);
		w.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		w.lpszMenuName = nullptr;
		w.lpszClassName = L"WrapperWindow";
		if (!RegisterClass(&w))
			goto end;

		const auto& outerSize = outerSizes[windowMode];

		accelWindow = CreateWindowEx(outerSize.exStyle,
			L"WrapperWindow",
			L"Sonic R",
			outerSize.style,
			outerSize.x, outerSize.y, outerSize.width, outerSize.height,
			nullptr, nullptr, hInstance, nullptr);

		if (accelWindow == nullptr)
			goto end;

		const auto& innerSize = innerSizes[windowMode];

		hWnd = CreateWindowExA(0,
			WindowName,
			WindowName,
			WS_CHILD | WS_VISIBLE,
			innerSize.x, innerSize.y, innerSize.width, innerSize.height,
			accelWindow, nullptr, hInstance, nullptr);

		SetFocus(hWnd);
		ShowWindow(accelWindow, 1);
		UpdateWindow(accelWindow);
		SetForegroundWindow(accelWindow);

		Windowed = true;

		WriteData((HWND**)0x42233E, &accelWindow);
		WriteData((HWND**)0x422440, &accelWindow);
	}
	else
	{
		DWORD dwStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE;
		DWORD dwExStyle = 0;
		AdjustWindowRectEx(&windowRect, dwStyle, false, dwExStyle);
		int w = windowRect.right - windowRect.left;
		int h = windowRect.bottom - windowRect.top;
		int x = wsX + ((wsW - w) / 2);
		int y = wsY + ((wsH - h) / 2);
		hWnd = CreateWindowExA(dwExStyle, WindowName, WindowName, dwStyle, x, y, w, h, 0, 0, hInstance, 0);
		if (!hWnd)
		{
			auto v6 = DisplayFatalErrorWithTrace("H:\\projects\\SonicR.Win\\SonicR\\pc\\pcmain.cpp", 277);
			v6("Failed to create window - gor blimey guv'nor");
		}
		ShowWindow(hWnd, 1);
		UpdateWindow(hWnd);
		SetFocus(hWnd);
	}
	MSG Msg;
	while (PeekMessageA(&Msg, 0, 0, 0, 1u))
	{
		TranslateMessage(&Msg);
		DispatchMessageA(&Msg);
	}
	sub_404CB0(hWnd);
	sub_442070(hWnd);
	try { MainGameLoop(); }
	catch (const std::exception&) {}
end:
	timeEndPeriod(tc.wPeriodMin);
	return 0;
}

static const char verchk[] = "Sonic R";
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if (memcmp(verchk, WindowName, sizeof(verchk)) != 0)
			MessageBox(nullptr, L"The mod loader was not designed for this version of the game. You will need the 2004 version of Sonic R to use mods.", L"Sonic R Mod Loader", MB_ICONWARNING);
		else
			WriteCall((void*)0x449E92, InitMods);
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

