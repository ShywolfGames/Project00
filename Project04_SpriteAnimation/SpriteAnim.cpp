#include "SpriteAnim.h"

SpriteAnim::SpriteAnim()
{
}

SpriteAnim::~SpriteAnim()
{
	releaseAll();
}

void SpriteAnim::initialize(HWND hw)
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

void SpriteAnim::update()
{
}

void SpriteAnim::ai()
{
}

void SpriteAnim::collisions()
{
}

void SpriteAnim::render()
{
	graphics->spriteBegin();
	nebula.draw();
	planet.draw();
	graphics->spriteEnd();
}

void SpriteAnim::releaseAll()
{
	planetTexture.onLostDevice();
	nebulaTexture.onLostDevice();
	Game::releaseAll();
}

void SpriteAnim::resetAll()
{
	nebulaTexture.onResetDevice();
	planetTexture.onResetDevice();
	Game::resetAll();
	return;
}
