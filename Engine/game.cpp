#include "game.h"

Game::Game()
{
	input = new Input();
	paused = false;
	graphics = NULL;
	initialized = false;
}

Game::~Game()
{
	deleteAll();
	ShowCursor(true);
}

LRESULT Game::messageHandler(HWND hw, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (initialized)
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_KEYDOWN: case WM_SYSKEYDOWN:
			input->keyDown(wParam);
			return 0;
		case WM_KEYUP: case WM_SYSKEYUP:
			input->keyUp(wParam);
			return 0;
		case WM_CHAR:
			input->keyIn(wParam);
				return 0;
		case WM_MOUSEMOVE:
			input->mouseIn(lParam);
				return 0;
		case WM_INPUT:
			input->mouseRawIn(lParam);
				return 0;
		case WM_LBUTTONDOWN:
			input->setMouseLButton(true);
			input->mouseIn(lParam);
			return 0;
		case WM_LBUTTONUP:
			input->setMouseLButton(false);
			input->mouseIn(lParam);
			return 0;
		case WM_RBUTTONDOWN:
			input->setMouseRButton(true);
			input->mouseIn(lParam);
			return 0;
		case WM_RBUTTONUP:
			input->setMouseRButton(false);
			input->mouseIn(lParam);
			return 0; 
		case WM_MBUTTONDOWN:
				input->setMouseMButton(true);
				input->mouseIn(lParam);
				return 0;
		case WM_MBUTTONUP:
				input->setMouseMButton(false);
				input->mouseIn(lParam);
				return 0;
		case WM_XBUTTONDOWN: case WM_XBUTTONUP:
			input->setMouseXButton(wParam);
			input->mouseIn(lParam);
			return 0;
		case WM_MOUSEHWHEEL:
			input->mouseWheelIn(wParam);
			return 0;
		case WM_DEVICECHANGE:
			input->checkControllers();
			return 0;
		}
	}
	return DefWindowProc(hw,msg,wParam,lParam);
}

void Game::initialize(HWND hw)
{
}

void Game::run(HWND)
{
}

void Game::releaseAll()
{
}

void Game::resetAll()
{
}

void Game::deleteAll()
{
}

void Game::renderGame()
{
}

void Game::handleLostGraphicsDevice()
{
}
