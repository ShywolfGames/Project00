#pragma once
#ifndef _SPACEWAR_H
#define _SPACEWAR_H
#define WIN32_LEAN_AND_MEAN
#include"..\Engine\game.h"
#include"..\Engine\textureManager.h"
#include"..\Engine\image.h"
#include "ship.h"
#include"planet.h"

const char NEBULA_IMAGE[] = "pictures\\orion.jpg";  
const char PLANET_IMAGE[] = "pictures\\planet.png"; 
const char SHIP_IMAGE[]   = "pictures\\ship.png";
const char TEXTURES_IMAGE[] = "pictures\\textures.png";


const UCHAR SHIP_LEFT_KEY = VK_LEFT;     // left arrow
const UCHAR SHIP_RIGHT_KEY = VK_RIGHT;    // right arrow
const UCHAR SHIP_UP_KEY = VK_UP;       // up arrow
const UCHAR SHIP_DOWN_KEY = VK_DOWN;     // down arrow

class EntityCollision : public Game
{
private:
	TextureManager nebulaTexture;
	TextureManager gameTextures;

	Planet planet;
	Image nebula;
	Ship ship;
	Ship ship1;

public:
	EntityCollision();
	virtual ~EntityCollision();
	void initialize(HWND hw);
	void update();
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();

};
#endif
