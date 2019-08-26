#include "collisionTypes.h"

CollisionTypes::CollisionTypes()
{
	menuOn = true;
}

CollisionTypes::~CollisionTypes()
{
	releaseAll();
}

void CollisionTypes::initialize(HWND hw)
{
	Game::initialize(hw);

	//graphics->setBackColor(graphicsNS::WHITE);
	if (!menuTexture.initialize(graphics, MENU_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error loading nebula  texture"));

	if (!gameTextures.initialize(graphics, TEXTURES_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error loading planet  texture"));


	if (!menu.initialize(graphics, 0,0,0,&menuTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing nebula"));

	
	// rectangle
	if (!rectangle.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing rectangle"));
	rectangle.setFrames(RECTANGLE_START_FRAME, RECTANGLE_END_FRAME);
	rectangle.setCurrentFrame(RECTANGLE_START_FRAME);
	rectangle.setX(GAME_WIDTH / 4);
	rectangle.setY(GAME_HEIGHT / 2);
	rectangle.setCollisionType(entityNS::ROTATED_BOX);
	// edge specifies the collision box relative to the center of the entity.
	rectangle.setEdge(COLLISION_RECTANGLE);
	rectangle.setDegrees(45);
	rectangle.setTarget(true);

	// square
	if (!square.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing square"));
	square.setFrames(SQUARE_START_FRAME, SQUARE_END_FRAME);
	square.setCurrentFrame(SQUARE_START_FRAME);
	square.setX(GAME_WIDTH / 2);
	square.setY(GAME_HEIGHT / 2);
	square.setCollisionType(entityNS::BOX);
	// edge specifies the collision box relative to the center of the entity.
	square.setEdge(COLLISION_BOX);
	square.setTarget(true);

	// circle
	if (!circle.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing circle"));
	circle.setFrames(CIRCLE_START_FRAME, CIRCLE_END_FRAME);
	circle.setCurrentFrame(CIRCLE_START_FRAME);
	circle.setX(GAME_WIDTH - GAME_WIDTH / 4);
	circle.setY(GAME_HEIGHT / 2);
	circle.setCollisionType(entityNS::CIRCLE);
	circle.setCollisionRadius(COLLISION_RADIUS);
	circle.setTarget(true);

	// ship
	if (!ship.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));
	ship.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);
	ship.setCurrentFrame(SHIP_START_FRAME);
	ship.setX(GAME_WIDTH / 2);
	ship.setY(GAME_HEIGHT / 4);
	ship.setCollisionType(entityNS::CIRCLE);
	// edge specifies the collision box relative to the center of the entity.
	ship.setEdge(COLLISION_BOX);
	ship.setCollisionRadius(COLLISION_RADIUS);

	// line
	if (!line.initialize(graphics, shipNS::WIDTH, shipNS::HEIGHT, TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing line"));
	line.setFrames(LINE_START_FRAME, LINE_END_FRAME);
	line.setCurrentFrame(LINE_START_FRAME);
	line.setScale(LINE_SCALE);
	line.setX(0);
	line.setY(0);

	return;	
}

void CollisionTypes::update()
{
	if (menuOn)
	{
		if (input->anyKeyPressed())
		{
			menuOn = false;
			input->clearAll();
		}
	}
	else
	{
		if (input->isKeyDown(SHIP_UP_KEY))
			ship.forward();
		if (input->isKeyDown(SHIP_DOWN_KEY))
			ship.reverse();
		ship.rotate(shipNS::NONE);
		if (input->isKeyDown(SHIP_LEFT_KEY))   // if turn ship0 left
			ship.rotate(shipNS::LEFT);
		if (input->isKeyDown(SHIP_RIGHT_KEY))  // if turn ship0 right
			ship.rotate(shipNS::RIGHT);
	}

	rectangle.update(frameTime);
	square.update(frameTime);
	circle.update(frameTime);
	ship.update(frameTime);
	line.update(frameTime);

	if (input->getCharIn() == '1')
	{
		ship.setEdge(COLLISION_RECTANGLE);
		ship.setCollisionType(entityNS::ROTATED_BOX);
	}
	if (input->getCharIn() == '2')
	{
		ship.setEdge(COLLISION_BOX);
		ship.setCollisionType(entityNS::BOX);
	}
	if (input->getCharIn() == '3')
		ship.setCollisionType(entityNS::CIRCLE);
}
void CollisionTypes::ai()
{
}

void CollisionTypes::collisions()
{
	collisionVector.x = 0;
	collisionVector.y = 0;
	ship.setCollision(false);
	rectangle.setCollision(false);
	square.setCollision(false);
	circle.setCollision(false);

	if (ship.collidesWith(rectangle,collisionVector))
	{
		ship.setCollision(true);
		rectangle.setCollision(true);
		lineEnds[1].x=rectangle.getCollisionCenter()->x;
		lineEnds[1].y=rectangle.getCollisionCenter()->y;
	}
	if (ship.collidesWith(square, collisionVector))
	{
		ship.setCollision(true);
		square.setCollision(true);
		lineEnds[1].x= square.getCollisionCenter()->x;
		lineEnds[1].y= square.getCollisionCenter()->y;
	}
	if (ship.collidesWith(circle, collisionVector))
	{
		ship.setCollision(true);
		circle.setCollision(true);
		lineEnds[1].x= circle.getCollisionCenter()->x;
		lineEnds[1].y= circle.getCollisionCenter()->y;
	}
	lineEnds[0].x=ship.getCollisionCenter()->x;
	lineEnds[0].y=ship.getCollisionCenter()->y;
}

void CollisionTypes::render()
{
	float angle;
	graphics->spriteBegin();
	if (menuOn)
		menu.draw();
	else 
	{
		if (rectangle.getCollision())      
			rectangle.draw(graphicsNS::RED & graphicsNS::ALPHA50);   
		else
			rectangle.draw(graphicsNS::GREEN);

		if (square.getCollision())          
			square.draw(graphicsNS::RED & graphicsNS::ALPHA50);   
		else
			square.draw(graphicsNS::YELLOW);

		if (circle.getCollision())           
			circle.draw(graphicsNS::RED & graphicsNS::ALPHA50);  
		else
			circle.draw(graphicsNS::ORANGE);

		ship.draw();

		if (ship.getCollision())             
		{
	
			if (square.getCollision() && ship.getCollisionType() == entityNS::BOX)
			{
				angle = ship.getRadians();
				ship.setRadians(0);
				square.draw(ship.getSpriteInfo(), graphicsNS::RED & graphicsNS::ALPHA50);
				ship.setRadians(angle);
			}
			else
			{
				if (ship.getCollisionType() == entityNS::ROTATED_BOX)
					rectangle.draw(ship.getSpriteInfo(), graphicsNS::RED & graphicsNS::ALPHA50);

				else if (ship.getCollisionType() == entityNS::BOX)
					square.draw(ship.getSpriteInfo(), graphicsNS::RED & graphicsNS::ALPHA50);
	
				else if (ship.getCollisionType() == entityNS::CIRCLE)
					circle.draw(ship.getSpriteInfo(), graphicsNS::RED & graphicsNS::ALPHA50);
			}

			lineRadians = std::atan2(lineEnds[1].y - lineEnds[0].y, lineEnds[1].x - lineEnds[0].x);
			line.setRadians(lineRadians);
			AxBx = lineEnds[0].x - lineEnds[1].x;
			AyBy = lineEnds[0].y - lineEnds[1].y;
			lineLength = std::sqrt(AxBx*AxBx + AyBy * AyBy);
			RECT rect = line.getSpriteDataRect();
			rect.right = (LONG)(LINE_LENGTH + lineLength / LINE_SCALE);
			line.setSpriteDataRect(rect);
			line.setX(lineEnds[0].x - LINE_LENGTH * LINE_SCALE);
			line.setY(lineEnds[0].y - LINE_LENGTH * LINE_SCALE);
			line.draw(graphicsNS::CYAN);
		}
		else    
		{

			if (ship.getCollisionType() == entityNS::ROTATED_BOX)
				rectangle.draw(ship.getSpriteInfo(), graphicsNS::ALPHA50);

			else if (ship.getCollisionType() == entityNS::BOX)
			{
				angle = ship.getRadians();
				ship.setRadians(0);
				square.draw(ship.getSpriteInfo(), graphicsNS::ALPHA50);
				ship.setRadians(angle);
			}
			else if (ship.getCollisionType() == entityNS::CIRCLE)
				circle.draw(ship.getSpriteInfo(), graphicsNS::ALPHA50);
		}
	}
	graphics->spriteEnd();
}

void CollisionTypes::releaseAll()
{
	gameTextures.onLostDevice();
	menuTexture.onLostDevice();
	Game::releaseAll();
}

void CollisionTypes::resetAll()
{
	menuTexture.onResetDevice();
	gameTextures.onResetDevice();
	Game::resetAll();
	return;
}
