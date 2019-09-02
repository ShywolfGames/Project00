#include "ScrollingBitmap.h"

ScrollingBitmap::ScrollingBitmap()
{
	menuOn = true;
	countDownOn = false;
	roundOver = false;
}

ScrollingBitmap::~ScrollingBitmap()
{
	releaseAll();
}

void ScrollingBitmap::initialize(HWND hw)
{
	Game::initialize(hw);

	fontBig.initialize(graphics, 256, false, false, "Arial Bold");
	fontBig.setFontColor(graphicsNS::YELLOW);

	if (!gameTextures.initialize(graphics, TEXTURES1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error loading planet  texture"));

	if (!menuTexture.initialize(graphics, MENU_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));

	if (!spaceTexture.initialize(graphics, SPACE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing space texture"));

	if (!menu.initialize(graphics, 0, 0, 0, &menuTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));

	if (!space.initialize(graphics, 0, 0, 0, &spaceTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing space"));
	space.setScale((float)SPACE_SCALE);


	for (int i = 0; i < 4; i++)
	{
		if (!moons[i].initialize(graphics, MOON_SIZE, MOON_SIZE, 4, &gameTextures))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing moons"));
		moons[i].setFrames(MOON1_FRAME + i, MOON1_FRAME + i);
		moons[i].setCurrentFrame(MOON1_FRAME + i);
		// Start moons in center
		moons[i].setX(GAME_WIDTH / 2 - MOON_SIZE / 2);
		moons[i].setY(GAME_HEIGHT / 2 - MOON_SIZE / 2);
	}

	// planet
	if (!planet.initialize(graphics, 128, 128, 2, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));
	planet.setFrames(1, 1);
	planet.setCurrentFrame(1);
	// Start planet in centet
	planet.setX(GAME_WIDTH / 2 - 128 / 2);
	planet.setY(GAME_HEIGHT / 2 - 128 / 2);

	if (!ship.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing planet"));
	ship.setX(GAME_WIDTH / 2 - shipNS::WIDTH);
	ship.setY(GAME_HEIGHT / 2 - shipNS::HEIGHT);
	ship.setFrames(shipNS::SHIP_START_FRAME, shipNS::SHIP_END_FRAME);
	ship.setCurrentFrame(shipNS::SHIP_START_FRAME);
	ship.setColorFilter(SETCOLOR_ARGB(255, 230, 230, 255));
	//ship.setVelocity(VECTOR2(shipNS::SPEED, -shipNS::SPEED));

	return;	
}

void ScrollingBitmap::update()
{
	if (menuOn)
	{
		if (input->anyKeyPressed())
		{
			menuOn = false;
			input->clearAll();
			roundStart();
		}
	}
	else if (countDownOn)
	{
		countDownTimer -= frameTime;
		if (countDownTimer <= 0)
			countDownOn = false;
	}
	else
	{
		if (ship.getActive())
		{
			if (input->isKeyDown(SHIP_UP_KEY) || input->getGamepadDPadUp(0))   // if engine on
			{
				ship.setEngineOn(true);
				audio->playCue(ENGINE1);
			}
			else
			{
				ship.setEngineOn(false);
				audio->stopCue(ENGINE1);
			}
			ship.rotate(shipNS::NONE);
			if (input->isKeyDown(SHIP_LEFT_KEY) || input->getGamepadDPadLeft(0))   // if turn ship1 left
				ship.rotate(shipNS::LEFT);
			if (input->isKeyDown(SHIP_RIGHT_KEY) || input->getGamepadDPadRight(0)) // if turn ship1 right
				ship.rotate(shipNS::RIGHT);
		}
		if (roundOver)
		{
			roundTimer -= frameTime;
			if (roundTimer <= 0)
				roundStart();
		}
	}

	// Update the entities
	ship.update(frameTime);

	planet.setX(planet.getX() - frameTime * ship.getVelocity().x);
	// move planet along Y
	planet.setY(planet.getY() - frameTime * ship.getVelocity().y);
	planet.update(frameTime);
	for (int i = 0; i < 4; i++)      // move moons
	{
		// reduce scroll speed by 20% for each moon
		moons[i].setX(moons[i].getX() - frameTime * ship.getVelocity().x * 0.2f * (4 - i));
		moons[i].setY(moons[i].getY() - frameTime * ship.getVelocity().y * 0.2f * (4 - i));
	}
	// move space in X direction opposite ship
	space.setX(space.getX() - frameTime * ship.getVelocity().x);
	// move space in Y direction opposite ship
	space.setY(space.getY() - frameTime * ship.getVelocity().y);

	// Wrap space image around at edge
	// if left edge of space > screen left edge
	if (space.getX() > 0)
		// move space image left by SPACE_WIDTH
		space.setX(space.getX() - SPACE_WIDTH);
	// if space image off screen left
	if (space.getX() < -SPACE_WIDTH)
		// move space image right by SPACE_WIDTH
		space.setX(space.getX() + SPACE_WIDTH);
	// if top edge of space > screen top edge
	if (space.getY() > 0)
		// move space image up by SPACE_HEIGHT
		space.setY(space.getY() - SPACE_HEIGHT);
	// if space image off screen top
	if (space.getY() < -SPACE_HEIGHT)
		// move space image down by SPACE_IMAGE
		space.setY(space.getY() + SPACE_HEIGHT);


}
void ScrollingBitmap::roundStart()
{
	space.setX(0);
	space.setY(0);

	// Start ship in center
	ship.setX(GAME_WIDTH / 2 - shipNS::WIDTH);
	ship.setY(GAME_HEIGHT / 2 - shipNS::HEIGHT);

	ship.setDegrees(0);
	countDownTimer = 2;
	countDownOn = true;
	roundOver = false;
}
void ScrollingBitmap::ai()
{
}

void ScrollingBitmap::collisions()
{
	VECTOR2 collisionVector;


}

void ScrollingBitmap::render()
{
	float x = space.getX();
	float y = space.getY();

	graphics->spriteBegin();                // begin drawing sprites

	// Wrap space image around at edges
	space.draw();                           // draw at current location
	// if space image right edge visible
	if (space.getX() < -SPACE_WIDTH + (int)GAME_WIDTH)
	{
		space.setX(space.getX() + SPACE_WIDTH); // wrap around to left edge
		space.draw();                           // draw again
	}
	// if space image bottom edge visible
	if (space.getY() < -SPACE_HEIGHT + (int)GAME_HEIGHT)
	{
		space.setY(space.getY() + SPACE_HEIGHT); // wrap around to top edge
		space.draw();                           // draw again
		space.setX(x);                          // restore x position
		// if space image right edge visible
		// wrap around to left edge
		if (x < -SPACE_WIDTH + (int)GAME_WIDTH)
			space.draw();                       // draw again
	}
	space.setX(x);      // restore x position
	space.setY(y);      // restore y position

	for (int i = 3; i >= 0; i--)
		moons[i].draw();                    
	planet.draw();
	ship.draw();       // draw the spaceship

	if (menuOn)
		menu.draw();
	if (countDownOn)
	{
		_snprintf_s(buffer, 20, "%d", (int)(ceil(countDownTimer)));
		fontBig.print(buffer, GAME_WIDTH / 2 - 256 / 4 , GAME_WIDTH / 2 - 256 / 2);
	}
}

void ScrollingBitmap::releaseAll()
{
	gameTextures.onLostDevice();
	menuTexture.onLostDevice();
	spaceTexture.onLostDevice();
	fontScore.onLostDevice();
	fontBig.onLostDevice();
	Game::releaseAll();
}

void ScrollingBitmap::resetAll()
{

	gameTextures.onResetDevice();
	fontBig.onResetDevice();
	fontScore.onResetDevice();
	spaceTexture.onResetDevice();
	menuTexture.onResetDevice();
	Game::resetAll();
	return;
}
