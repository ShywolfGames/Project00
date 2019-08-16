#pragma once
#ifndef _SPACEWAR_H
#define _SPACEWAR_H
#define WIN32_LEAN_AND_MEAN
#include"..\Engine\game.h"
class Spacewar;
const char NEBULA_IMAGE[] = "pictures\\orion.jpg";  // photo source NASA/courtesy of nasaimages.org 
const char PLANET_IMAGE[] = "pictures\\planet.png"; // picture of planet

class Spacewar : public Game
{
private:

public:
	Spacewar();
	virtual ~Spacewar();
	void intialize(HWND hw);
	void update();
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();

};
#endif
