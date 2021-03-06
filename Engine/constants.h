#pragma once
#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

const char CLASS_NAME[] = "WinMain";
const char GAME_TITLE[] = "DirectX Window";
const bool FULLSCREEN = false;
const UINT GAME_WIDTH = 1024;
const UINT GAME_HEIGHT = 768;
/////////////////////////////
const float FULL_HEALTH = 100;
const int SPACE_SCALE = 2;                 
const int SPACE_WIDTH = 640 * SPACE_SCALE;  
const int SPACE_HEIGHT = 480 * SPACE_SCALE; 
const UINT MOON_SIZE = 64;                  
const UINT MOON1_FRAME = 12;               
const UINT NEBULA_SIZE = 128;               
/////////////////////////////
//#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)
/////
const char WAVE_BANK[] = "audio\\Win\\waveBank.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\soundBank.xsb";
// audio cues
//const char BEEP1[] = "beep1";
//const char BEEP2[] = "beep2";
//const char BEEP3[] = "beep3";
//const char BEEP4[] = "beep4";
//const char HIT[] = "hit";
const char CHEER[] = "cheer";
const char COLLIDE[] = "collide";
const char EXPLODE[] = "explode";
const char ENGINE1[] = "engine1";
const char ENGINE2[] = "engine2";
const char TORPEDO_CRASH[] = "torpedoCrash";
const char TORPEDO_FIRE[] = "torpedoFire";
const char TORPEDO_HIT[] = "torpedoHit";
/////
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;
const float MIN_FRAME_RATE = 10.0f;
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE;

const UCHAR ESC_KEY = VK_ESCAPE;
const UCHAR ALT_KEY = VK_MENU;
const UCHAR ENTER_KEY = VK_RETURN;
const UCHAR CONSOLE_KEY = '`';
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
inline void safeDelete(T& ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = NULL;
	}
}
#define SAFE_DELETE safeDelete

template<typename T>
inline void safeDeleteArray(T& ptr)
{
	if (ptr)
	{
		delete[] ptr;
		ptr = NULL;
	}
}
#define SAFE_DELETE_ARRAY safeDeleteArray

#endif
