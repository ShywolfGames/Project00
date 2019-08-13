#pragma once
#ifndef _GAME_H
#define _GAME_H
#define WIN32_LEAN_AND_MEAN
#include<Windows.h>
#include<mmsystem.h>
#include"graphics.h"
#include"input.h"
#include"constants.h"
#include"gameError.h"

class Game;




class Game
{
protected:
	Graphics *graphics;
	Input *input;
	HWND hwnd;
	HRESULT hr;
	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;
	LARGE_INTEGER timerFreq;
	float frameTime;
	float fps;
	DWORD sleepTime;
	bool paused;
	bool initialized;
public:
	Game();
	virtual ~Game();
	LRESULT messageHandler(HWND hw, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual void initialize(HWND hw); 
	virtual void run(HWND);
	virtual void releaseAll();
	virtual void resetAll();
	virtual void deleteAll();
	virtual void renderGame();
	virtual void handleLostGraphicsDevice();
	Graphics * getGraphics() { return graphics; }
	Input* getInput() { return input; }
	void exitGame() { PostMessage(hwnd, WM_DESTROY, 0, 0); }
	virtual void update() = 0;
	virtual void ai() = 0;
	virtual void collisions() = 0;
	virtual void render() = 0;

};
#endif
