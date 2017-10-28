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

DataPointer(int, FrameEndTime, 0x7349F8);
DataPointer(int, FrameStartTime, 0x7356B0);

FunctionPointer(void, FrameDelay, (int fps), 0x404A90);
FunctionPointer(int, GetTime, (), 0x404D30);
FunctionPointer(int, PrintDebug, (const char *fmt, ...), 0x404D80);