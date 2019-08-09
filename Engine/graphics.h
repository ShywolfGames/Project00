#pragma once
#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#define WIN32_LEAN_AND_MEAN
#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif

class Graphics;

#include <d3d9.h>
#include "constants.h"
#include "gameError.h"

#define LP_3DDEVICE LPDIRECT3DDEVICE9
#define LP_3D LPDIRECT3D9
#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b)\
((COLOR_ARGB)((((a)&oxff)<<24)|(((r)&oxff)<<16)|(((g)&oxff)<<8)|((b)&oxff)))

class Graphics
{
private:
	LP_3D direct3d;
	LP_3DDEVICE device3d;
	D3DPRESENT_PARAMETERS d3dpp;
	HRESULT result;
	HWND hwnd;
	bool fullscreen;
	int width;
	int height;
	void initD3Dpp();
public:
	Graphics();
	virtual ~Graphics();
	void releaseAll();
	void initialize(HWND hw,int width, int height,bool fullscreen);
	HRESULT showBackBuffer();

};

#endif
