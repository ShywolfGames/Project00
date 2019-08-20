#pragma once
#ifndef _SPACEWAR_H
#define _SPACEWAR_H
#define WIN32_LEAN_AND_MEAN
#include"..\Engine\game.h"
#include"..\Engine\textureManager.h"
#include"..\Engine\image.h"
const char NEBULA_IMAGE[] = "pictures\\orion.jpg";  
const char PLANET_IMAGE[] = "pictures\\planet.png"; 
const char SHIP_IMAGE[] = "pictures\\ship.png";

const int SHIP_START_FRAME = 0;
const int SHIP_END_FRAME = 3;
const float SHIP_ANIMATION_DELAY = 0.2f;
const int SHIP_COLS = 2;
const int SHIP_WIDTH = 32;
const int SHIP_HEIGHT = 32;
const float ROTATION_RATE = 180.0f;
const float SCALE_RATE = 0.2f;
const float SHIP_SPEED = 100.0f;
const float SHIP_SCALE = 1.5f;

const UCHAR SHIP_LEFT_KEY = VK_LEFT;     // left arrow
const UCHAR SHIP_RIGHT_KEY = VK_RIGHT;    // right arrow
const UCHAR SHIP_UP_KEY = VK_UP;       // up arrow
const UCHAR SHIP_DOWN_KEY = VK_DOWN;     // down arrow

class SpriteAnim : public Game
{
private:
	TextureManager nebulaTexture;
	TextureManager planetTexture;
	TextureManager shipTexture;
	Image planet;
	Image nebula;
	Image ship;

public:
	SpriteAnim();
	virtual ~SpriteAnim();
	void initialize(HWND hw);
	void update();
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();

};
#endif
