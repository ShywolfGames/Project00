#define _CRTDBG_MAP_ALLOC
#define WIN32_LEAN_AND_MEAN

#include<windows.h>
#include<stdlib.h>
#include<crtdbg.h>
#include"graphics.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
bool CreateMainWindow(HWND &, HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;
Graphics *graphics;



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	MSG msg;
	HWND hwnd = NULL;

	if (!CreateMainWindow(hwnd,hInstance, nCmdShow))
		return 1;
	try {
		graphics = new Graphics;
		graphics->initialize(hwnd, GAME_WIDTH, GAME_HEIGHT, FULLSCREEN);

		int done = 0;
		while (!done)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					done = 1;
				TranslateMessage(&msg);
				DispatchMessage(&msg);

			}
			else
				graphics->showBackBuffer();

		}
		safeDelete(graphics);
		return msg.wParam;
	}
	catch (const GameError &err)
	{
		MessageBox(NULL, err.getMessage(),"Error", MB_OK);
	}
	catch (...)
	{
		MessageBox(NULL, "Unknown Error Occured in Game","Error", MB_OK);
	}
	safeDelete(graphics);
	return 0;
}
LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
bool CreateMainWindow(HWND &hwnd, HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcx;
	

	wcx.cbSize = sizeof(wcx);
	wcx.style = CS_HREDRAW | CS_VREDRAW;
	wcx.lpfnWndProc = WinProc;
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = hInstance;
	wcx.hIcon = NULL;
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = CLASS_NAME;
	wcx.hIconSm = NULL;

	if (RegisterClassEx(&wcx) == 0)
		return false;
	hwnd = CreateWindow(
		CLASS_NAME, GAME_TITLE, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, GAME_WIDTH, GAME_HEIGHT, (HWND)NULL, (HMENU)NULL, hInstance, (LPVOID)NULL);

	if (!hwnd)
	{
		return false;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	return true;

}