#pragma once

void __cdecl D3D_LoadTPageRGB_r(int page, char* filename);
void LoadHiResParallax(const char* a1);
void D3D_LoadPlayfieldTilesRGB_r(const char* filename);
void D3D_LoadWallpaper_r(const char* filename);
void LoadHiResTPageSection(char* filename, char* buffer, int srcWidth, int srcHeight, int dstLeft, int dstTop);
void __cdecl D3D_ConvertTPagesToTextures_r();