#include "stdafx.h"
#include <algorithm>
#include <Shlwapi.h>
#include <GdiPlus.h>
#include "TextConv.hpp"
#include "FileReplacement.h"
#include "FileSystem.h"
#include "Textures.h"
#include "SonicRModLoader.h"
#include "D3DStuff.h"

using std::string;
using namespace Gdiplus;

const char *extensions[] = { ".png", ".gif", ".bmp" };
Bitmap* HiResTexData[TPageBuffers.size()];

DataArray(int, dword_5D34C8, 0x5D34C8, 52);
void __cdecl D3D_LoadTPageRGB_r(int page, char* filename)
{
	PrintDebug("D3D_LoadTPageRGB(%i,%s)\n", page, filename);
	if (HiResTexData[page] != nullptr)
	{
		delete HiResTexData[page];
		HiResTexData[page] = nullptr;
	}
	D3D_ReleaseTexture(page);
	CreateTPageBuffer(page);
	char* buf = TPageBuffers[page];
	string fp = filename;
	for (size_t i = 0; i < LengthOfArray(extensions); i++)
	{
		ReplaceFileExtension(fp, extensions[i]);
		string f2 = fileMap.replaceFile(fp.c_str());
		if (FileExists(f2))
		{
			Bitmap* bmp = Bitmap::FromFile(MBStoUTF16(f2, CP_ACP).c_str());
			if (bmp->GetWidth() == 256 && bmp->GetHeight() == 256 && !(bmp->GetPixelFormat() & PixelFormatAlpha))
			{
				Rect rect(0, 0, bmp->GetWidth(), bmp->GetHeight());
				BitmapData bmpd;
				bmp->LockBits(&rect, ImageLockModeRead, PixelFormat24bppRGB, &bmpd);
				memcpy(buf, bmpd.Scan0, abs(bmpd.Stride) * bmpd.Height);
				bmp->UnlockBits(&bmpd);
				delete bmp;
				for (int p = 0; p < 0x30000; p += 3)
					std::swap(buf[p], buf[p + 2]);
				TextureSizes[2 * page] = 256;
				dword_5D34C8[page] = 2;
				TextureSizes[2 * page + 1] = 256;
				return;
			}
			else
				HiResTexData[page] = bmp;
			break;
		}
	}
	D3D_ReadTPageRGB(filename, buf, 0x10000);
	TextureSizes[2 * page] = 256;
	dword_5D34C8[page] = 2;
	TextureSizes[2 * page + 1] = 256;
}

void LoadHiResParallax(const char* filename)
{
	string fp = filename;
	for (size_t i = 0; i < LengthOfArray(extensions); i++)
	{
		ReplaceFileExtension(fp, extensions[i]);
		string f2 = fileMap.replaceFile(fp.c_str());
		if (FileExists(f2))
		{
			Bitmap* bmp = Bitmap::FromFile(MBStoUTF16(f2, CP_ACP).c_str());
			Rect rect(0, 0, bmp->GetWidth(), bmp->GetHeight());
			int texwidth = (int)(rect.Width / 6.5);
			int texheight = rect.Height * 2;
			Rect r2(0, 0, texwidth, texheight);
			BitmapData bmpd;
			bmp->LockBits(&rect, ImageLockModeRead, PixelFormat24bppRGB, &bmpd);
			const char* srcdata = static_cast<const char*>(bmpd.Scan0);
			for (int page = 0; page < 3; page++)
			{
				if (HiResTexData[BackgroundTPage + page] != nullptr)
					delete HiResTexData[BackgroundTPage + page];
				HiResTexData[BackgroundTPage + page] = new Bitmap(texwidth, texheight, PixelFormat24bppRGB);
				BitmapData bmpd2;
				HiResTexData[BackgroundTPage + page]->LockBits(&r2, ImageLockModeWrite, PixelFormat24bppRGB, &bmpd2);
				char* dstdata = static_cast<char*>(bmpd2.Scan0);
				const char* srcline = srcdata;
				for (int y = 0; y < rect.Height; y++)
				{
					memcpy(dstdata, srcline, texwidth * 3);
					srcline += bmpd.Stride;
					dstdata += bmpd2.Stride;
				}
				srcdata += texwidth * 3;
				srcline = srcdata;
				for (int y = 0; y < rect.Height; y++)
				{
					memcpy(dstdata, srcline, texwidth * 3);
					srcline += bmpd.Stride;
					dstdata += bmpd2.Stride;
				}
				srcdata += texwidth * 3;
				HiResTexData[BackgroundTPage + page]->UnlockBits(&bmpd2);
			}
			if (HiResTexData[BackgroundTPage + 3] != nullptr)
				delete HiResTexData[BackgroundTPage + 3];
			HiResTexData[BackgroundTPage + 3] = new Bitmap(texwidth, texheight, PixelFormat24bppRGB);
			BitmapData bmpd2;
			HiResTexData[BackgroundTPage + 3]->LockBits(&r2, ImageLockModeWrite, PixelFormat24bppRGB, &bmpd2);
			char* dstdata = static_cast<char*>(bmpd2.Scan0);
			const char* srcline = srcdata;
			ptrdiff_t rem = static_cast<char*>(bmpd.Scan0) + rect.Width * 3 - srcdata;
			for (int y = 0; y < rect.Height; y++)
			{
				memcpy(dstdata, srcline, rem);
				srcline += bmpd.Stride;
				dstdata += bmpd2.Stride;
			}
			HiResTexData[BackgroundTPage + 3]->UnlockBits(&bmpd2);
			bmp->UnlockBits(&bmpd);
			delete bmp;
			return;
		}
	}
}

void D3D_LoadPlayfieldTilesRGB_r(const char* filename)
{
	D3D_LoadPlayfieldTilesRGB(filename);
	string fp = filename;
	for (size_t i = 0; i < LengthOfArray(extensions); i++)
	{
		ReplaceFileExtension(fp, extensions[i]);
		string f2 = fileMap.replaceFile(fp.c_str());
		if (FileExists(f2))
		{
			Bitmap* bmp = Bitmap::FromFile(MBStoUTF16(f2, CP_ACP).c_str());
			Rect rect(0, 0, bmp->GetWidth(), bmp->GetHeight());
			int tilewidth = rect.Width / 10;
			int tileheight = rect.Height / 12;
			int texwidth = tilewidth * 8;
			int texheight = tileheight * 8;
			Rect r2(0, 0, texwidth, texheight);
			BitmapData bmpd;
			bmp->LockBits(&rect, ImageLockModeRead, PixelFormat32bppARGB, &bmpd);
			const char* srcdata = static_cast<const char*>(bmpd.Scan0);
			int tilenum = 0;
			Bitmap* tex = nullptr;
			BitmapData bmpd2;
			if (HiResTexData[PlayfieldTPage] != nullptr)
				delete HiResTexData[PlayfieldTPage];
			tex = new Bitmap(texwidth, texheight, PixelFormat32bppARGB);
			HiResTexData[PlayfieldTPage] = tex;
			tex->LockBits(&r2, ImageLockModeWrite, PixelFormat32bppARGB, &bmpd2);
			char* dstdata = static_cast<char*>(bmpd2.Scan0);
			char* dstline = dstdata;
			for (int row = 0; row < 12; ++row)
			{
				const char* srcline = srcdata;
				for (int col = 0; col < 10; ++col)
				{
					if (tilenum == 64)
					{
						tex->UnlockBits(&bmpd2);
						if (HiResTexData[PlayfieldTPage + 1] != nullptr)
							delete HiResTexData[PlayfieldTPage + 1];
						tex = new Bitmap(texwidth, texheight, PixelFormat32bppARGB);
						HiResTexData[PlayfieldTPage + 1] = tex;
						tex->LockBits(&r2, ImageLockModeWrite, PixelFormat32bppARGB, &bmpd2);
						dstdata = static_cast<char*>(bmpd2.Scan0);
						dstline = dstdata;
					}
					const char* srctile = srcline;
					char* dsttile = dstline;
					for (int y = 0; y < tileheight; ++y)
					{
						memcpy(dsttile, srctile, tilewidth << 2);
						srctile += bmpd.Stride;
						dsttile += bmpd2.Stride;
					}
					srcline += tilewidth << 2;
					if (++tilenum % 8)
						dstline += tilewidth << 2;
					else
					{
						dstdata += bmpd2.Stride * tileheight;
						dstline = dstdata;
					}
				}
				srcdata += bmpd.Stride * tileheight;
			}
			tex->UnlockBits(&bmpd2);
			bmp->UnlockBits(&bmpd);
			delete bmp;
			return;
		}
	}
}

void D3D_LoadWallpaper_r(const char* filename)
{
	D3D_LoadWallpaper(filename);
	string fp = filename;
	for (size_t i = 0; i < LengthOfArray(extensions); i++)
	{
		ReplaceFileExtension(fp, extensions[i]);
		string f2 = fileMap.replaceFile(fp.c_str());
		if (FileExists(f2))
		{
			Bitmap* bmp = Bitmap::FromFile(MBStoUTF16(f2, CP_ACP).c_str());
			Rect rect(0, 0, bmp->GetWidth(), bmp->GetHeight());
			int texwidth = (int)(rect.Width / 2.5);
			int texheight = (int)(rect.Height / 1.875);
			Rect r2(0, 0, texwidth, texheight);
			BitmapData bmpd;
			bmp->LockBits(&rect, ImageLockModeRead, PixelFormat24bppRGB, &bmpd);
			const char* srcdata = static_cast<const char*>(bmpd.Scan0);
			int page = 0;
			for (int y = 0; y < 2; ++y)
			{
				const char* srcline = srcdata;
				int height = min(rect.Height - (texheight * y), texheight);
				for (int x = 0; x < 3; ++x)
				{
					if (HiResTexData[WallpaperTPage + page] != nullptr)
						delete HiResTexData[WallpaperTPage + page];
					HiResTexData[WallpaperTPage + page] = new Bitmap(texwidth, texheight, PixelFormat24bppRGB);
					BitmapData bmpd2;
					HiResTexData[WallpaperTPage + page]->LockBits(&r2, ImageLockModeWrite, PixelFormat24bppRGB, &bmpd2);
					char* dstdata = static_cast<char*>(bmpd2.Scan0);
					const char* srctile = srcline;
					int width = min(rect.Width - (texwidth * x), texwidth) * 3;
					for (int y = 0; y < height; y++)
					{
						memcpy(dstdata, srctile, width);
						srctile += bmpd.Stride;
						dstdata += bmpd2.Stride;
					}
					srcline += width;
					HiResTexData[WallpaperTPage + page]->UnlockBits(&bmpd2);
					++page;
				}
				srcdata += bmpd.Stride * height;
			}
			bmp->UnlockBits(&bmpd);
			delete bmp;
			return;
		}
	}
}

void LoadHiResTPageSection(char* filename, char* buffer, int srcWidth, int srcHeight, int dstLeft, int dstTop)
{
	Bitmap* dst = nullptr;
	for (size_t i = 0; i < TPageBuffers.size(); ++i)
		if (TPageBuffers[i] == buffer)
		{
			dst = HiResTexData[i];
			break;
		}
	if (dst == nullptr) return;
	string fp = filename;
	for (size_t i = 0; i < LengthOfArray(extensions); i++)
	{
		ReplaceFileExtension(fp, extensions[i]);
		string f2 = fileMap.replaceFile(fp.c_str());
		if (FileExists(f2))
		{
			srcWidth *= (int)(dst->GetWidth() / 256.0);
			srcHeight *= (int)(dst->GetHeight() / 256.0);
			dstLeft *= (int)(dst->GetWidth() / 256.0);
			dstTop *= (int)(dst->GetHeight() / 256.0);
			Graphics gfx(dst);
			gfx.SetCompositingMode(CompositingModeSourceCopy);
			Bitmap* bmp = Bitmap::FromFile(MBStoUTF16(f2, CP_ACP).c_str());
			if (bmp->GetWidth() % srcWidth == 0 && bmp->GetHeight() % srcHeight == 0)
				gfx.SetInterpolationMode(InterpolationModeNearestNeighbor);
			else
				gfx.SetInterpolationMode(InterpolationModeHighQualityBicubic);
			gfx.DrawImage(bmp, dstLeft, dstTop, srcWidth, srcHeight);
			delete bmp;
			return;
		}
	}
}

void __cdecl D3D_ConvertTPagesToTextures_r()
{
	IDirect3DDevice9* v0; // eax
	int v1; // ebx
	unsigned int v2; // edi
	uint8_t* v3; // ebp
	char* v4; // ecx
	int v5; // edi
	_BYTE* v6; // ebp
	int v7; // esi
	void (*v8)(char*, ...); // eax
	void (*v9)(char*, ...); // eax
	int v10; // [esp+38h] [ebp-20h]
	int v11; // [esp+3Ch] [ebp-1Ch]
	int v12; // [esp+40h] [ebp-18h]
	D3DLOCKED_RECT v16; // [esp+50h] [ebp-8h] BYREF

	v0 = D3DDevice;
	v1 = 0;
	if (D3DDevice)
	{
		for (v2 = 0; v2 < TPageBuffers.size(); ++v2)
		{
			if (TPageBuffers[v2] && !D3DTextures[v2])
			{
				if (HiResTexData[v2])
				{
					Bitmap* bmp = HiResTexData[v2];
					int width = bmp->GetWidth();
					int height = bmp->GetHeight();
					if (v0->CreateTexture(width, height, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &D3DTextures[v2], 0) < 0)
					{
						v9 = DisplayFatalErrorWithTrace(__FILE__, __LINE__);
						v9("Unable to create texture");
					}
					else if (D3DTextures[v2]->LockRect(0, &v16, 0, 0) < 0)
					{
						v8 = DisplayFatalErrorWithTrace(__FILE__, __LINE__);
						v8("Failed to lock surface");
					}
					else
					{
						v3 = (uint8_t*)v16.pBits;
						Rect rect(0, 0, width, height);
						BitmapData bmpd;
						bmp->LockBits(&rect, ImageLockModeRead, PixelFormat32bppARGB, &bmpd);
						char* src = (char*)bmpd.Scan0;
						for (v12 = 0; v12 < height; ++v12)
						{
							v6 = v3;
							v4 = src;
							for (v5 = 0; v5 < width; ++v5)
							{
								if ((*(int*)v4 & 0xFFF8F8F8) != 0xFF00F800)
									*(int*)v6 = *(int*)v4;
								else
									*(int*)v6 = 0;
								v4 += 4;
								v6 += 4;
							}
							v3 += v16.Pitch;
							src += bmpd.Stride;
						}
						bmp->UnlockBits(&bmpd);
						D3DTextures[v2]->UnlockRect(0);
					}
				}
				else
				{
					if (v0->CreateTexture(256, 256, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &D3DTextures[v2], 0) < 0)
					{
						v9 = DisplayFatalErrorWithTrace(__FILE__, __LINE__);
						v9("Unable to create texture");
					}
					else if (D3DTextures[v2]->LockRect(0, &v16, 0, 0) < 0)
					{
						v8 = DisplayFatalErrorWithTrace(__FILE__, __LINE__);
						v8("Failed to lock surface");
					}
					else
					{
						v3 = (uint8_t*)v16.pBits;
						v4 = TPageBuffers[v2];
						for (v12 = 0; v12 < 256; ++v12)
						{
							v6 = v3;
							for (v5 = 0; v5 < 256; ++v5)
							{
								if ((v4[1] & 0xF8) != 0xF8 || (v4[0] & 0xF8) != 0 || (v4[2] & 0xF8) != 0)
								{
									v6[3] = -1;
									v6[2] = v4[0];
									v6[1] = v4[1];
									v6[0] = v4[2];
								}
								else
								{
									v7 = 0;
									v10 = 0;
									v11 = 0;
									if (v5 && ((v4[-2] & 0xF8) != 248 || (v4[-3] & 0xF8) != 0 || (v4[-1] & 0xF8) != 0))
									{
										v11 = (unsigned __int8)v4[-2];
										v1 = (unsigned __int8)v4[-3];
										v7 = 1;
										v10 = (unsigned __int8)v4[-1];
									}
									if (v5 < 255 && ((v4[4] & 0xF8) != 248 || (v4[3] & 0xF8) != 0 || (v4[5] & 0xF8) != 0))
									{
										v1 += (unsigned __int8)v4[3];
										v11 += (unsigned __int8)v4[4];
										v10 += (unsigned __int8)v4[5];
										++v7;
									}
									if (v12 && ((v4[-767] & 0xF8) != 248 || (v4[-768] & 0xF8) != 0 || (v4[-766] & 0xF8) != 0))
									{
										v1 += (unsigned __int8)v4[-768];
										v11 += (unsigned __int8)v4[-767];
										v10 += (unsigned __int8)v4[-766];
										++v7;
									}
									if (v12 < 255 && ((v4[769] & 0xF8) != 248 || (v4[768] & 0xF8) != 0 || (v4[770] & 0xF8) != 0))
									{
										v1 += (unsigned __int8)v4[768];
										v11 += (unsigned __int8)v4[769];
										v10 += (unsigned __int8)v4[770];
										++v7;
									}
									if (v7)
									{
										v1 /= v7;
										v11 /= v7;
										v10 /= v7;
									}
									v6[3] = 0;
									v6[0] = v10;
									v6[1] = v11;
									v6[2] = v1;
									v1 = 0;
								}
								v4 += 3;
								v6 += 4;
							}
							v3 += v16.Pitch;
						}
						D3DTextures[v2]->UnlockRect(0);
					}
				}
			}
		}
	}
}