#pragma once
#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

const char CLASS_NAME[] = "WinMain";
const char GAME_TITLE[] = "DirectX Window";
const UINT GAME_WIDTH = 640;
const UINT GAME_HEIGHT = 480;

const UCHAR ESC_KEY = VK_ESCAPE;
template<typename T>
inline void safeRelease(T& ptr)
{
	if (ptr)
	{
		ptr->Release();
		ptr = NULL;
	}
}
#define SAFE_RELEASE safeRelease

template<typename T>
inline void safeRelease(T& ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = NULL;
	}
}
#define SAFE_DELETE safeDelete

template<typename T>
inline void safeRelease(T& ptr)
{
	if (ptr)
	{
		delete[] ptr;
		ptr = NULL;
	}
}
#define SAFE_DELETE_ARRAY safeDeleteArray

#endif
