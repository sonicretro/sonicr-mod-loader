#pragma once
#include <cstdio>
#include "MemAccess.h"

static const int ModLoaderVer = 1;

struct PatchInfo
{
	void *address;
	const void *data;
	int datasize;
};

struct PatchList
{
	const PatchInfo *Patches;
	int Count;
};

struct PointerInfo
{
	void *address;
	void *data;
};

struct PointerList
{
	const PointerInfo *Pointers;
	int Count;
};

typedef void(__cdecl *ModInitFunc)(const char *path);

typedef void(__cdecl *ModEvent)();

struct ModInfo
{
	int LoaderVersion;
};

typedef uint32_t _DWORD;
typedef uint16_t _WORD;
typedef uint8_t _BYTE;

DataArray(char, WindowName, 0x45F664, 8);
DataPointer(int, HorizontalResolution, 0x461520);
DataPointer(int, VerticalResolution, 0x461524);
DataPointer(WNDCLASSA, WndClass, 0x4B5398);
DataPointer(HINSTANCE, hInstance, 0x4B53C4);
DataPointer(HWND, hWnd, 0x4B53C8);
DataPointer(int, CurrentMusicTrack, 0x502360);
DataArray(char *, TPageBuffers, 0x5D359C, 1);
DataPointer(int, Windowed, 0x5EDD24);
DataPointer(int, FrameEndTime, 0x7349F8);
DataPointer(int, FrameStartTime, 0x7356B0);
DataPointer(int, MusicVolume, 0x7AF1B4);

FunctionPointer(void, FrameDelay, (int fps), 0x404A90);
static void(__cdecl *(__cdecl *const DisplayFatalErrorWithTrace)(char *file, int line))(char *, ...) = (decltype(DisplayFatalErrorWithTrace))0x404AF0;
static void(__cdecl *(__cdecl *const PrintDebugWithTrace)(char *file, int line))(char *, ...) = (decltype(PrintDebugWithTrace))0x404BC0;
FunctionPointer(int, GetTime, (), 0x404D30);
FunctionPointer(int, PrintDebug, (const char *fmt, ...), 0x404D80);
FunctionPointer(int, D3D_ReadTPageRGB, (const char *FilePath, char *Buffer, int BytesPerChannel), 0x407950);
FunctionPointer(void, D3D_LoadTPageRGB, (int page, char *filename), 0x407A00);
FunctionPointer(void, CreateTPageBuffer, (int page), 0x442720);
FunctionPointer(void, D3D_ReleaseTexture, (int page), 0x4427D0);
VoidFunc(CalculateClockSpeed, 0x4332B0);
FunctionPointer(void, ProcessCommandLine, (const char *a1), 0x433400);
FunctionPointer(int, MainGameLoop, (), 0x43AA60);
FunctionPointer(int, GetCurrentMusicTrack, (), 0x43C180);
FunctionPointer(void, PlayMusicTrack, (int track), 0x43C210);
VoidFunc(StopMusic, 0x43C260);
VoidFunc(UpdateMusicVolume, 0x43D190);
FunctionPointer(
    void, D3D_Render2DObject, (
	int XPos, int YPos, float ZPos, int XScale, int YScale, int TexPage,
	int TexXOff, int TexYOff, int TexWidth, int TexHeight, int TexTint
    ), 0x40C270
);
FunctionPointer(void, D3D_RenderHUD_MainTimer, (int XPos, int YPos, float ZPos, int Time, int Unk), 0x43D4C0);
FunctionPointer(void, D3D_RenderHUD_LapTimer, (int XPos, int YPos, int Time), 0x43D860);
DataPointer(int, MP_HUD2PSplit, 0x7344EC);
DataPointer(int, MP_WindowCount, 0x7AF280);
DataPointer(int, Game_TAttackMode, 0x7BCB80);