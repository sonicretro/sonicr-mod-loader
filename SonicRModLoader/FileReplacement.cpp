#include "stdafx.h"
#include <MMSystem.h>
#include "FileReplacement.h"
#include "MemAccess.h"

// File replacement map.
// NOTE: Do NOT mark this as static.
// MediaFns.cpp needs to access the FileMap.
FileMap fileMap;

/**
* CreateFileA() wrapper using _ReplaceFile().
* @param lpFileName
* @param dwDesiredAccess
* @param dwShareMode
* @param lpSecurityAttributes
* @param dwCreationDisposition
* @param dwFlagsAndAttributes
* @param hTemplateFile
* @return
*/
HANDLE WINAPI MyCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
	return CreateFileA(fileMap.replaceFile(lpFileName), dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

FunctionPointer(MMRESULT, sub_446320, (LPCSTR pszFileName, int a2, int a3, int a4, HMMIO hmmio), 0x446320);
MMRESULT __cdecl sub_446320_r(LPCSTR pszFileName, int a2, int a3, int a4, HMMIO hmmio)
{
	return sub_446320(fileMap.replaceFile(pszFileName), a2, a3, a4, hmmio);
}

/**
* C wrapper to call sadx_fileMap.replaceFile() from asm.
* @param lpFileName Filename.
* @return Replaced filename, or original filename if not replaced by a mod.
*/
const char *_ReplaceFile(const char *lpFileName)
{
	return fileMap.replaceFile(lpFileName);
}
