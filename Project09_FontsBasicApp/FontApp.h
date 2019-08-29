#pragma once
#ifndef _FONTAPP_H
#define _FONTAPP_H
#define WIN32_LEAN_AND_MEAN
#include"..\Engine\game.h"
#include"..\Engine\textureManager.h"
#include"..\Engine\image.h"
#include"..\Engine\text.h"

const char NEBULA_IMAGE[] = "pictures\\orion.jpg";  
const char FONT_IMAGE[] = "pictures\\CKfont.png";

const UCHAR SHIP_LEFT_KEY = VK_LEFT;     // left arrow
const UCHAR SHIP_RIGHT_KEY = VK_RIGHT;    // right arrow
const UCHAR SHIP_UP_KEY = VK_UP;       // up arrow
const UCHAR SHIP_DOWN_KEY = VK_DOWN;     // down arrow

class FontApp : public Game
{
private:
	TextureManager nebulaTexture;
	Text *fontCK;
	Image nebula;

public:
	FontApp();
	virtual ~FontApp();
	void initialize(HWND hw);
	void update();
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();

};
#endif
