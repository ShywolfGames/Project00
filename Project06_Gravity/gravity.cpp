#include "gravity.h"

Gravity::Gravity()
{
}

Gravity::~Gravity()
{
	releaseAll();
}

void Gravity::initialize(HWND hw)
{
	Game::initialize(hw);

	//graphics->setBackColor(graphicsNS::WHITE);
	if (!backdropTexture.initialize(graphics, BACKDROP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error loading nebula  texture"));

	if (!ballTexture.initialize(graphics, BALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error loading planet  texture"));
	if (!paddleTexture.initialize(graphics, PADDLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error loading planet  texture"));


	if (!backdrop.initialize(graphics, 0,0,0,&backdropTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing nebula"));

	if (!paddle.initialize(this, paddleNS::WIDTH,paddleNS::HEIGHT,0,&paddleTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing planet"));

	if (!ball.initialize(this, ballNS::WIDTH, ballNS::HEIGHT, 0, &ballTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing planet"));
	ball.setX(GAME_WIDTH / 4 - ballNS::WIDTH);
	ball.setY(GAME_HEIGHT / 2- ballNS::HEIGHT);
	ball.setVelocity(VECTOR2(ballNS::SPEED, -ballNS::SPEED));
	


	return;	
}

void Gravity::update()
{
	if (input->isKeyDown(LEFT_KEY))
		paddle.setX(paddle.getX() - paddleNS::SPEED*frameTime);
	if (input->isKeyDown(RIGHT_KEY))
		paddle.setX(paddle.getX() + paddleNS::SPEED*frameTime);
	ball.update(frameTime);
	paddle.update(frameTime);

}

void Gravity::ai()
{
}

void Gravity::collisions()
{
	VECTOR2 collisionVector;

	if (ball.collidesWith(paddle, collisionVector))
			ball.bounce(collisionVector, paddle);
	
}

void Gravity::render()
{
	graphics->spriteBegin();
	backdrop.draw();
	ball.draw();
	paddle.draw();
	graphics->spriteEnd();
}

void Gravity::releaseAll()
{
	ballTexture.onLostDevice();
	paddleTexture.onLostDevice();
	backdropTexture.onLostDevice();
	Game::releaseAll();
}

void Gravity::resetAll()
{
	ballTexture.onResetDevice();
	paddleTexture.onResetDevice();
	backdropTexture.onResetDevice();
	Game::resetAll();
	return;
}
