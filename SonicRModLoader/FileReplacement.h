#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <MMSystem.h>
#include "FileMap.hpp"

extern FileMap fileMap;

HANDLE __stdcall MyCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
MMRESULT __cdecl sub_446320_r(LPCSTR pszFileName, int a2, int a3, int a4, HMMIO hmmio);
const char * _ReplaceFile(const char * lpFileName);
