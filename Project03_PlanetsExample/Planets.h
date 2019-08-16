#pragma once
#ifndef _SPACEWAR_H
#define _SPACEWAR_H
#define WIN32_LEAN_AND_MEAN
#include"..\Engine\game.h"
#include"..\Engine\textureManager.h"
#include"..\Engine\image.h"
const char NEBULA_IMAGE[] = "pictures\\orion.jpg";  
const char PLANET_IMAGE[] = "pictures\\planet.png"; 

class Planets : public Game
{
private:
	TextureManager nebulaTexture;
	TextureManager planetTexture;
	Image planet;
	Image nebula;

public:
	Planets();
	virtual ~Planets();
	void initialize(HWND hw);
	void update();
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();

};
#endif
