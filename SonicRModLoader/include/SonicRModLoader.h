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
DataPointer(int, Windowed, 0x5EDD24);
DataPointer(int, FrameEndTime, 0x7349F8);
DataPointer(int, FrameStartTime, 0x7356B0);

FunctionPointer(void, FrameDelay, (int fps), 0x404A90);
static void(__cdecl *(__cdecl *const DisplayFatalErrorWithTrace)(char *file, int line))(char *, ...) = (decltype(DisplayFatalErrorWithTrace))0x404AF0;
static void(__cdecl *(__cdecl *const PrintDebugWithTrace)(char *file, int line))(char *, ...) = (decltype(PrintDebugWithTrace))0x404BC0;
FunctionPointer(int, GetTime, (), 0x404D30);
FunctionPointer(int, PrintDebug, (const char *fmt, ...), 0x404D80);
VoidFunc(CalculateClockSpeed, 0x4332B0);
FunctionPointer(void, ProcessCommandLine, (const char *a1), 0x433400);
FunctionPointer(int, MainGameLoop, (), 0x43AA60);