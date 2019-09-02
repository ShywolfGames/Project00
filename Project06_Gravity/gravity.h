#pragma once
#ifndef _SPACEWAR_H
#define _SPACEWAR_H
#define WIN32_LEAN_AND_MEAN
#include"..\Engine\game.h"
#include"..\Engine\textureManager.h"
#include"..\Engine\image.h"
#include "ball.h"
#include"paddle.h"
#include"block.h"

const char BACKDROP_IMAGE[] = "pictures\\backdrop.png";
const char BALL_IMAGE[] = "pictures\\ball.png";
const char PADDLE_IMAGE[]   = "pictures\\paddle.png";
const char BLOCK_IMAGE[] = "pictures\\paddle.png";


const UCHAR LEFT_KEY = VK_LEFT;      // left arrow
const UCHAR RIGHT_KEY = VK_RIGHT;     // right arrow


class Gravity : public Game
{
private:
	TextureManager backdropTexture;
	TextureManager ballTexture;
	TextureManager paddleTexture;
	TextureManager blockTexture;

	Paddle paddle;
	Image backdrop;
	Ball ball;
	Block block;

public:
	Gravity();
	virtual ~Gravity();
	void initialize(HWND hw);
	void update();
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();

};
#endif
