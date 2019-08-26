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

	//graphics->setBackColor(graphicsNS::WHITE);
	if (!nebulaTexture.initialize(graphics, NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error loading nebula  texture"));

	if (!gameTextures.initialize(graphics, TEXTURES_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error loading planet  texture"));


	if (!nebula.initialize(graphics, 0,0,0,&nebulaTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing nebula"));

	if (!planet.initialize(this, planetNS::WIDTH,planetNS::HEIGHT,2,&gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing planet"));

	//planet.setX(GAME_WIDTH*0.5f - planet.getWidth()*0.5f);
	//planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);
	
	if (!ship.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing planet"));
	ship.setX(GAME_WIDTH / 4 );
	ship.setY(GAME_HEIGHT / 4);
	ship.setFrames(shipNS::SHIP_START_FRAME, shipNS::SHIP_END_FRAME);
	ship.setCurrentFrame(shipNS::SHIP_START_FRAME);
	ship.setVelocity(VECTOR2(shipNS::SPEED, -shipNS::SPEED));

	if (!ship1.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing planet"));
	ship1.setX(GAME_WIDTH-GAME_WIDTH / 4);
	ship1.setY(GAME_HEIGHT / 4);
	ship1.setFrames(8, 11);
	ship1.setCurrentFrame(8);
	ship1.setVelocity(VECTOR2(shipNS::SPEED, -shipNS::SPEED));
	


	return;	
}

void EntityCollision::update()
{
	ship.update(frameTime);
	ship1.update(frameTime);
	planet.update(frameTime);

}

void EntityCollision::ai()
{
}

void EntityCollision::collisions()
{
	VECTOR2 collisionVector;

	if (ship.collidesWith(planet, collisionVector))
	{
	
		ship.bounce(collisionVector, planet);
		ship.damage(PLANET);
	}
	if (ship1.collidesWith(planet, collisionVector))
	{

		ship1.bounce(collisionVector, planet);
		ship1.damage(PLANET);
	}
	if (ship.collidesWith(ship1, collisionVector))
	{

		ship.bounce(collisionVector, ship1);
		ship.damage(SHIP);
		//ship1.bounce((collisionVector*-1), ship);
		collisionVector *= -1;
		ship1.bounce(collisionVector, ship);
		ship1.damage(SHIP);
	}
}

void EntityCollision::render()
{
	graphics->spriteBegin();
	nebula.draw();
	planet.draw();
	ship.draw();
	ship1.draw();
	graphics->spriteEnd();
}

void EntityCollision::releaseAll()
{
	gameTextures.onLostDevice();
	nebulaTexture.onLostDevice();
	Game::releaseAll();
}

void EntityCollision::resetAll()
{
	nebulaTexture.onResetDevice();
	gameTextures.onResetDevice();
	Game::resetAll();
	return;
}
