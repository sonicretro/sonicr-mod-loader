#include "stdafx.h"
#include <MMSystem.h>
#include "SonicRModLoader.h"
#include "FileReplacement.h"
#include "bass_vgmstream.h"
#include "Music.h"

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