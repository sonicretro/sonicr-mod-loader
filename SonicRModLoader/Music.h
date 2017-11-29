#pragma once

void InitMusic();
void DeInitMusic();
int GetCurrentTrackNumber();
void PlayMusic(int track);
void StopMusic_r();
void UpdateMusicVolume_r();
void CheckPauseMusic();
