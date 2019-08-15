#include "Planets.h"

Planets::Planets()
{
}

Planets::~Planets()
{
	releaseAll();
}

void Planets::intialize(HWND hw)
{
	Game::initialize(hw);
	return;
}

void Planets::update()
{
}

void Planets::ai()
{
}

void Planets::collisions()
{
}

void Planets::render()
{
}

void Planets::releaseAll()
{
	Game::releaseAll();
}

void Planets::resetAll()
{
	Game::resetAll();
	return;
}
