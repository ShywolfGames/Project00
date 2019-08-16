#include "Planets.h"

Planets::Planets()
{
}

Planets::~Planets()
{
	releaseAll();
}

void Planets::initialize(HWND hw)
{
	Game::initialize(hw);

	graphics->setBackColor(graphicsNS::WHITE);
	if (!nebulaTexture.initialize(graphics, NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error loading nebula  texture"));
	if (!planetTexture.initialize(graphics, PLANET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error loading planet  texture"));
	if (!nebula.initialize(graphics, 0,0,0,&nebulaTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing nebula"));
	if (!planet.initialize(graphics, 0,0,0,&planetTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing planet"));

	planet.setX(GAME_WIDTH*0.5f - planet.getWidth()*0.5f);
	planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);
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
	graphics->spriteBegin();
	nebula.draw();
	planet.draw();
	graphics->spriteEnd();
}

void Planets::releaseAll()
{
	planetTexture.onLostDevice();
	nebulaTexture.onLostDevice();
	Game::releaseAll();
}

void Planets::resetAll()
{
	nebulaTexture.onResetDevice();
	planetTexture.onResetDevice();
	Game::resetAll();
	return;
}
