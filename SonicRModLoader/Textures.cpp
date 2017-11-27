#include "stdafx.h"
#include <algorithm>
#include <Shlwapi.h>
#include <GdiPlus.h>
#include "TextConv.hpp"
#include "FileReplacement.h"
#include "FileSystem.h"
#include "Textures.h"
#include "SonicRModLoader.h"

using std::string;
using namespace Gdiplus;

const char *extensions[] = { ".png", ".gif", ".bmp" };

signed int __cdecl D3D_ReadTPageRGB_r(const char *FilePath, char *Buffer, int BytesPerChannel)
{
	string fp =  FilePath;
	for (size_t i = 0; i < LengthOfArray(extensions); i++)
	{
		ReplaceFileExtension(fp, extensions[i]);
		string f2 = fileMap.replaceFile(fp.c_str());
		if (FileExists(f2))
		{
			Bitmap *bmp = Bitmap::FromFile(MBStoUTF16(f2, CP_ACP).c_str());
			Rect rect(0, 0, bmp->GetWidth(), bmp->GetHeight());
			BitmapData bmpd;
			bmp->LockBits(&rect, ImageLockModeRead, PixelFormat24bppRGB, &bmpd);
			memcpy(Buffer, bmpd.Scan0, abs(bmpd.Stride) * bmpd.Height);
			bmp->UnlockBits(&bmpd);
			delete bmp;
			for (int p = 0; p < BytesPerChannel; p++)
				std::swap(Buffer[p * 3], Buffer[p * 3 + 2]);
			return 1;
		}
	}
	return D3D_ReadTPageRGB(FilePath, Buffer, BytesPerChannel);
}