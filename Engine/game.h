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
#include "audio.h"
#include "textDX.h"
#include "console.h"
namespace gameNS
{
	const char FONT[] = "Courier New"; 
	const int POINT_SIZE = 14;          
	const COLOR_ARGB FONT_COLOR = SETCOLOR_ARGB(255, 255, 255, 255);    
}

class Game
{
protected:
	Graphics *graphics;
	Input *input;
	Audio* audio;
	Console *console;
	HWND hwnd;
	HRESULT hr;
	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;
	LARGE_INTEGER timerFreq;
	float frameTime;

	float fps;
	TextDX dxFont;
	bool fpsOn;
	std::string command;

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
	void setDisplayMode(graphicsNS::DISPLAY_MODE mode = graphicsNS::TOGGLE);
	Graphics * getGraphics() { return graphics; }
	Input* getInput() { return input; }
	void exitGame() { PostMessage(hwnd, WM_DESTROY, 0, 0); }
	Audio * getAudio() { return audio; }
	virtual void consoleCommand();
	virtual void update() = 0;
	virtual void ai() = 0;
	virtual void collisions() = 0;
	virtual void render() = 0;

};
#endif
