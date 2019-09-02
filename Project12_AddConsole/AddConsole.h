#pragma once
#ifndef _FONTAPP_H
#define _FONTAPP_H
#define WIN32_LEAN_AND_MEAN
#include"..\Engine\game.h"
#include"..\Engine\textureManager.h"
#include"..\Engine\image.h"
#include"..\Engine\text.h"
#include"..\Engine\textDX.h"

const char NEBULA_IMAGE[] = "pictures\\orion.jpg";  
const char FONT_IMAGE[] = "pictures\\CKfont.png";

const UCHAR SHIP_LEFT_KEY = VK_LEFT;     // left arrow
const UCHAR SHIP_RIGHT_KEY = VK_RIGHT;    // right arrow
const UCHAR SHIP_UP_KEY = VK_UP;       // up arrow
const UCHAR SHIP_DOWN_KEY = VK_DOWN;     // down arrow
const int BUF_SIZE = 20;
const float FALLING_SPEED = 100.0f;
const float FALLING_Y = -100.0f;
const float POINT_SIZE_SPEED = 200.0f;
const float MAX_POINT_SIZE = 480.0f;
const float CH_TIME = 0.1f;
class AddConsole : public Game
{
private:

	Text    *fontCK;                    // sprite based font
	TextDX  *dxFont14;                  // DirectX fonts
	TextDX  *dxFont24;
	TextDX  *dxFont48;
	TextDX  *dxFont48B;                 // bold
	TextDX  *dxFont96;
	TextDX  *dxFont24F;                 // 24 point fixed pitch

	// game variables
	double  alignmentTimer;             // used to change text alignment display
	bool    spriteText;                 // true for sprite text, false for DirectX text
	byte red, green, blue;
	char buffer[BUF_SIZE];
	VECTOR2 position;                   // used to position items on screen
	float fallingY;
	float angle;
	float pointSize;                    // for changing point size
	float chTimer;
	UCHAR ch;
	char st[2];

public:
	AddConsole();
	virtual ~AddConsole();
	void initialize(HWND hw);
	void update();
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();

};
#endif
