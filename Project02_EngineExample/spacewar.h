#pragma once
#ifndef _SPACEWAR_H
#define _SPACEWAR_H
#define WIN32_LEAN_AND_MEAN
#include"..\Engine\game.h"
class Spacewar;


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
