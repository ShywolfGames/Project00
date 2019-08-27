#pragma once
#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#define WIN32_LEAN_AND_MEAN
#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif

class Graphics;

#include <d3d9.h>
#include <d3dx9.h>
#include "constants.h"
#include "gameError.h"

#define LP_3DDEVICE LPDIRECT3DDEVICE9
#define LP_3D LPDIRECT3D9
#define LP_TEXTURE LPDIRECT3DTEXTURE9
#define LP_SPRITE LPD3DXSPRITE
#define VECTOR2     D3DXVECTOR2


#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b)\
((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

namespace graphicsNS
{
	// Some common colors
	// ARGB numbers range from 0 through 255
	// A = Alpha channel (transparency where 255 is opaque)
	// R = Red, G = Green, B = Blue
	const COLOR_ARGB ORANGE = D3DCOLOR_ARGB(255, 255, 165, 0);
	const COLOR_ARGB BROWN = D3DCOLOR_ARGB(255, 139, 69, 19);
	const COLOR_ARGB LTGRAY = D3DCOLOR_ARGB(255, 192, 192, 192);
	const COLOR_ARGB GRAY = D3DCOLOR_ARGB(255, 128, 128, 128);
	const COLOR_ARGB OLIVE = D3DCOLOR_ARGB(255, 128, 128, 0);
	const COLOR_ARGB PURPLE = D3DCOLOR_ARGB(255, 128, 0, 128);
	const COLOR_ARGB MAROON = D3DCOLOR_ARGB(255, 128, 0, 0);
	const COLOR_ARGB TEAL = D3DCOLOR_ARGB(255, 0, 128, 128);
	const COLOR_ARGB GREEN = D3DCOLOR_ARGB(255, 0, 128, 0);
	const COLOR_ARGB NAVY = D3DCOLOR_ARGB(255, 0, 0, 128);
	const COLOR_ARGB WHITE = D3DCOLOR_ARGB(255, 255, 255, 255);
	const COLOR_ARGB YELLOW = D3DCOLOR_ARGB(255, 255, 255, 0);
	const COLOR_ARGB MAGENTA = D3DCOLOR_ARGB(255, 255, 0, 255);
	const COLOR_ARGB RED = D3DCOLOR_ARGB(255, 255, 0, 0);
	const COLOR_ARGB CYAN = D3DCOLOR_ARGB(255, 0, 255, 255);
	const COLOR_ARGB LIME = D3DCOLOR_ARGB(255, 0, 255, 0);
	const COLOR_ARGB BLUE = D3DCOLOR_ARGB(255, 0, 0, 255);
	const COLOR_ARGB BLACK = D3DCOLOR_ARGB(255, 0, 0, 0);
	const COLOR_ARGB FILTER = D3DCOLOR_ARGB(0, 0, 0, 0);  // use to specify drawing with colorFilter
	const COLOR_ARGB ALPHA25 = D3DCOLOR_ARGB(64, 255, 255, 255);  // AND with color to get 25% alpha
	const COLOR_ARGB ALPHA50 = D3DCOLOR_ARGB(128, 255, 255, 255);  // AND with color to get 50% alpha
	const COLOR_ARGB BACK_COLOR = NAVY;                         // background color of game
	const COLOR_ARGB TRANSCOLOR = MAGENTA;
	enum DISPLAY_MODE { TOGGLE, FULLSCREEN, WINDOW };
}
struct SpriteData
{
	int width;
	int height;
	float x;
	float y;
	float scale;
	float angle;
	RECT rect;
	LP_TEXTURE texture;
	bool flipHorizontal;
	bool flipVertical;
};

class Graphics
{
private:
	LP_3D direct3d;
	LP_3DDEVICE device3d;
	LP_SPRITE sprite;

	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE pMode;
	IDirect3DQuery9* pOcclusionQuery;   // for pixel perfect collision detection
	DWORD   numberOfPixelsColliding;    // for pixel perfect collision detection

	HRESULT result;
	HWND hwnd;
	bool fullscreen;
	bool stencilSupport;
	int width;
	int height;
	COLOR_ARGB backColor;

	void initD3Dpp();
public:
	Graphics();
	virtual ~Graphics();
	void releaseAll();
	void initialize(HWND hw,int width, int height,bool fullscreen);
	HRESULT showBackBuffer();
	bool isAdapterCompatible();
	HRESULT reset();
	LP_3D get3D() { return direct3d; }
	LP_3DDEVICE get3Ddevice() { return device3d; }
	HDC getDC() { return GetDC(hwnd); }
	HRESULT getDeviceState();
	void setBackColor(COLOR_ARGB c) { backColor = c; }


	HRESULT loadTexture(const char* filename, COLOR_ARGB transcolor, UINT &width, UINT &height, LP_TEXTURE &texture);
	void drawSprite(const SpriteData &spriteData, COLOR_ARGB color = graphicsNS::WHITE);
	void changeDisplayMode(graphicsNS::DISPLAY_MODE mode = graphicsNS::TOGGLE);
	LP_SPRITE getSprite() { return sprite; }
	bool    getFullscreen() { return fullscreen; }

	static float    Vector2Length(const VECTOR2 *v) { return D3DXVec2Length(v); }
	static float    Vector2Dot(const VECTOR2 *v1, const VECTOR2 *v2) { return D3DXVec2Dot(v1, v2); }
	static void     Vector2Normalize(VECTOR2 *v) { D3DXVec2Normalize(v, v); }
	static VECTOR2* Vector2Transform(VECTOR2 *v, D3DXMATRIX *m) { return D3DXVec2TransformCoord(v, v, m); }

	DWORD pixelCollision(const SpriteData &sprite1, const SpriteData &sprite2);
	IDirect3DQuery9* getPOcclusionQuery() { return pOcclusionQuery; }
	bool getStencilSupport() { return stencilSupport; }
	HRESULT beginScene()
	{
		result = E_FAIL;
		if (device3d == NULL)
			return result;
		device3d->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, backColor, 1.0f, 0);
		result = device3d->BeginScene();
		return result;
	}
	HRESULT endScene()
	{
		result = E_FAIL;
		if (device3d)
			result = device3d->EndScene();
		return result;
	}
	void spriteBegin()
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
	}
	void spriteEnd()
	{
		sprite->End();
	}
};

#endif
