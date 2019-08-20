#include "EntityCollision.h"

EntityCollision::EntityCollision()
{
}

EntityCollision::~EntityCollision()
{
	releaseAll();
}

void EntityCollision::initialize(HWND hw)
{
	Game::initialize(hw);

	graphics->setBackColor(graphicsNS::WHITE);
	if (!nebulaTexture.initialize(graphics, NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error loading nebula  texture"));
	if (!planetTexture.initialize(graphics, PLANET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error loading planet  texture"));
	if (!shipTexture.initialize(graphics, SHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error loading ship  texture"));
	if (!nebula.initialize(graphics, 0,0,0,&nebulaTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing nebula"));
	if (!planet.initialize(graphics, 0,0,0,&planetTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing planet"));
	planet.setX(GAME_WIDTH*0.5f - planet.getWidth()*0.5f);
	planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);
	
	if (!ship.initialize(graphics, SHIP_WIDTH, SHIP_HEIGHT, SHIP_COLS, &shipTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing planet"));
	ship.setX(GAME_WIDTH / 4);
	ship.setY(GAME_HEIGHT / 4);
	ship.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);
	ship.setCurrentFrame(SHIP_START_FRAME);
	ship.setFrameDelay(SHIP_ANIMATION_DELAY);
	


	return;	
}

void EntityCollision::update()
{
	ship.update(frameTime);
	//ship.setDegrees(ship.getDegrees() + frameTime * ROTATION_RATE);
	//ship.setScale(ship.getScale() - frameTime * SCALE_RATE);
	if (input->isKeyDown(SHIP_RIGHT_KEY))
	{
		ship.setX(ship.getX() + frameTime * SHIP_SPEED);
		if (ship.getX() > GAME_WIDTH)
		{
			ship.setX((float)-ship.getWidth());
		}
	}
	if (input->isKeyDown(SHIP_LEFT_KEY))
	{
		ship.setX(ship.getX() - frameTime * SHIP_SPEED);
		if (ship.getX() < -ship.getX())
		{
			ship.setX((float)GAME_WIDTH);
		}
	}	
	if (input->isKeyDown(SHIP_UP_KEY))
	{
		ship.setY(ship.getY() - frameTime * SHIP_SPEED);
		if (ship.getY() < -ship.getY())
		{
			ship.setY((float)GAME_HEIGHT);

		}
	}	
	if (input->isKeyDown(SHIP_DOWN_KEY))
	{
		ship.setY(ship.getY() + frameTime * SHIP_SPEED);
		if (ship.getY() > GAME_HEIGHT)
		{
			ship.setY((float)-ship.getHeight());
	
		}
	}

}

void EntityCollision::ai()
{
}

void EntityCollision::collisions()
{
}

void EntityCollision::render()
{
	graphics->spriteBegin();
	nebula.draw();
	planet.draw();
	ship.draw();
	graphics->spriteEnd();
}

void EntityCollision::releaseAll()
{
	shipTexture.onLostDevice();
	planetTexture.onLostDevice();
	nebulaTexture.onLostDevice();
	Game::releaseAll();
}

void EntityCollision::resetAll()
{
	shipTexture.onResetDevice();
	nebulaTexture.onResetDevice();
	planetTexture.onResetDevice();
	Game::resetAll();
	return;
}
