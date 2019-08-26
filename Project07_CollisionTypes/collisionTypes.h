#pragma once
#ifndef _SPACEWAR_H
#define _SPACEWAR_H
#define WIN32_LEAN_AND_MEAN
#include"..\Engine\game.h"
#include"..\Engine\textureManager.h"
#include"..\Engine\image.h"
#include "ship.h"
 
const char MENU_IMAGE[]   = "pictures\\menu.png";
const char TEXTURES_IMAGE[] = "pictures\\textures2.png";

const int   TEXTURE_COLS = 4;           // texture has 4 columns
const int   RECTANGLE_START_FRAME = 0;  // rectangle starts at frame 0
const int   RECTANGLE_END_FRAME = 0;    // rectangle not animated
const int   SQUARE_START_FRAME = 1;     // square starts at frame 1
const int   SQUARE_END_FRAME = 1;       // square not animated
const int   CIRCLE_START_FRAME = 2;     // circle starts at frame 2
const int   CIRCLE_END_FRAME = 2;       // circle not animated
const int   SHIP_START_FRAME = 3;       // ship starts at frame 3
const int   SHIP_END_FRAME = 3;         // ship not animated
const int   LINE_START_FRAME = 4;       // line starts at frame 4
const int   LINE_END_FRAME = 4;         // line not animated
const float LINE_LENGTH = 32.0f;
const float LINE_SCALE = 3.0f;         // this makes the line 96 pixels long
const RECT  COLLISION_RECTANGLE = { -30,-16,30,16 };
const RECT  COLLISION_BOX = { -30,-30,30,30 };
const float   COLLISION_RADIUS = 29;

const UCHAR SHIP_LEFT_KEY = VK_LEFT;     // left arrow
const UCHAR SHIP_RIGHT_KEY = VK_RIGHT;    // right arrow
const UCHAR SHIP_UP_KEY = VK_UP;       // up arrow
const UCHAR SHIP_DOWN_KEY = VK_DOWN;     // down arrow

class CollisionTypes : public Game
{
private:
	TextureManager menuTexture;
	TextureManager gameTextures;
	Ship rectangle;
	Ship square;
	Ship circle;
	Ship ship;;

	Image menu;
	bool menuOn;
	VECTOR2 collisionVector;
	Image line;
	float lineRadians;
	float lineScalee;
	float AxBx;
	float AyBy;
	float lineLength;
	VECTOR2 lineEnds[2];


public:
	CollisionTypes();
	virtual ~CollisionTypes();
	void initialize(HWND hw);
	void update();
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();

};
#endif
