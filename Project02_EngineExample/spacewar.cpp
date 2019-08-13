#include "spacewar.h"

Spacewar::Spacewar()
{
}

Spacewar::~Spacewar()
{
	releaseAll();
}

void Spacewar::intialize(HWND hw)
{
	Game::initialize(hw);
	return;
}

void Spacewar::update()
{
}

void Spacewar::ai()
{
}

void Spacewar::collisions()
{
}

void Spacewar::render()
{
}

void Spacewar::releaseAll()
{
	Game::releaseAll();
}

void Spacewar::resetAll()
{
	Game::resetAll();
	return;
}
