#pragma once
#ifndef _SPACEWAR_H
#define _SPACEWAR_H
#define WIN32_LEAN_AND_MEAN
#include"..\Engine\game.h"
#include"..\Engine\textureManager.h"
#include"..\Engine\image.h"
#include "ship.h"

const char SPACE_IMAGE[] = "pictures\\space.jpg";   // photo source NASA/courtesy of nasaimages.org 
const char TEXTURES1_IMAGE[] = "pictures\\textures1.png";  // game textures
const char MENU_IMAGE[] = "pictures\\menu1.png";     // menu texture

const UCHAR SHIP_LEFT_KEY = VK_LEFT;     // left arrow
const UCHAR SHIP_RIGHT_KEY = VK_RIGHT;    // right arrow
const UCHAR SHIP_UP_KEY = VK_UP;       // up arrow
const UCHAR SHIP_DOWN_KEY = VK_DOWN;     // down arrow

class ScrollingBitmap : public Game
{
private:

	TextureManager menuTexture, spaceTexture, gameTextures;   // textures
	Ship    ship;              // spaceships
	Image   space;              // backdrop image
	Image   menu;               // menu image
	bool    menuOn;
	bool    countDownOn;        // true when count down is displayed
	float   countDownTimer;
	TextDX  fontBig;            // DirectX font for game banners
	TextDX  fontScore;
	char buffer[20];
	bool    ship1Scored;        // true if ship scored during round
	bool    roundOver;          // true when round is over
	float   roundTimer;         // time until new round starts
	int     ship1Score; // scores

	Image planet;
	Image moons[4];
public:
	ScrollingBitmap();
	virtual ~ScrollingBitmap();
	void initialize(HWND hw);
	void update();
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();

	void roundStart();

};
#endif
