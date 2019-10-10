#pragma once
#include <cstdio>
#include "MemAccess.h"

#if !defined(_M_IX86) && !defined(__i386__)
#error Mods must be built targeting 32-bit x86, change your settings.
#endif

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

enum Characters
{
	Characters_Sonic,
	Characters_Tails,
	Characters_Knuckles,
	Characters_Amy,
	Characters_Eggman,
	Characters_MetalSonic,
	Characters_TailsDoll,
	Characters_MetalKnuckles,
	Characters_EggRobo,
	Characters_SuperSonic
};


struct PlayerData
{
	int XPosition;
	int YPosition;
	int ZPosition;
	int XRotation;
	int YRotation;
	int ZRotation;
	int RingCount;
	int field_1C;
	int field_20;
	int field_24;
	int field_28;
	int XSpeed;
	int YSpeed;
	int ZSpeed;
	int GroundHeight;
	int field_3C;
	__int16 InWater;
	__int16 WaterSinkTime;
	int ForwardsSpeed;
	int field_48;
	int DistanceOnTrack;
	__int16 Lap1Time;
	__int16 field_52;
	__int16 Lap2Time;
	__int16 field_56;
	__int16 Lap3Time;
	__int16 field_5A;
	__int16 RacePosition;
	__int16 CurrentLap;
	int field_60;
	__int16 LastItem;
	__int16 ItemTimer;
	__int16 WaterSplashTimer;
	__int16 DepthInWater;
	__int16 AcceleratePressed;
	__int16 field_6E;
	__int16 CameraYRotation;
	__int16 OnGround;
	__int16 FlightMode;
	__int16 field_76;
	int field_78;
	int field_7C;
	int field_80;
	int field_84;
	int field_88;
	int field_8C;
	int field_90;
	__int16 field_94;
	__int16 FlightTime;
	__int16 CurrentAnimation;
	__int16 field_9A;
	int AnimationFrame;
	int OnLoop;
	int CollisionLayer;
	int field_A8;
	int field_AC;
	__int16 AboveGeometry;
	__int16 field_B2;
	__int16 SlopeRX;
	__int16 SlopeMagnitude;
	__int16 SlopeRZ;
	__int16 field_BA;
	int field_BC;
	int LoopSidePosition;
	int LoopDistance;
	int field_C8;
	int LoopSideMomentum;
	int LoopMomentum;
	__int16 DriftDirection;
	__int16 field_D6;
	int field_D8;
	int field_DC;
	int field_E0;
	int field_E4;
	int field_E8;
	int field_EC;
	__int16 field_F0;
	__int16 Character;
	char field_F4[236];
	int PlayerModel;
	char field_1E4[16];
	__int16 BalloonCounter;
	char field_1F6[1317];
	char field_71B;
};


DataArray(char, WindowName, 0x45F664, 8);
DataPointer(int, HorizontalResolution, 0x461520);
DataPointer(int, VerticalResolution, 0x461524);
DataPointer(WNDCLASSA, WndClass, 0x4B5398);
DataPointer(HINSTANCE, hInstance, 0x4B53C4);
DataPointer(HWND, hWnd, 0x4B53C8);
DataPointer(int, CurrentMusicTrack, 0x502360);
DataArray(char *, TPageBuffers, 0x5D359C, 51);
DataPointer(int, Windowed, 0x5EDD24);
DataPointer(int, FrameEndTime, 0x7349F8);
DataPointer(int, FrameStartTime, 0x7356B0);
DataPointer(int, MusicVolume, 0x7AF1B4);
DataArray(PlayerData, Players, 0x7B7388, 5);

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