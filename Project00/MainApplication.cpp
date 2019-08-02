// Project00
// Learning to program Games August 1, 2019 1:33PM EST
//#include <iostream>
//int main()
//{
//	return 0;
//}

//TODO left off at page 24 in the book
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
const char CLASS_NAME[] = "WinMain";
const char APP_TITLE[] = "Hello World";
const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;

HDC hdc;
TCHAR ch = ' ';
RECT rect;
PAINTSTRUCT ps;
HINSTANCE hinst;

LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CHAR:
		switch (wParam)
		{
		case 0x08:
		case 0x09:
		case 0x0A:
		case 0x0D:
		case 0x1B:
			MessageBeep((UINT)-1);
			return 0;
		default:
			ch = (TCHAR)wParam;
			InvalidateRect(hWnd, NULL, TRUE);

		}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		TextOut(hdc, rect.right / 2, rect.bottom / 2, &ch, 1);
		EndPaint(hWnd, &ps);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
bool CreateMainWIndow(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcx;
	HWND hwnd;

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
		CLASS_NAME, APP_TITLE, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, (HWND)NULL, (HMENU)NULL, hInstance, (LPVOID)NULL);

	if (!hwnd)
	{
		return false;
	}
		
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	return true;

}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	if (!CreateMainWIndow(hInstance, nCmdShow))
		return false;
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
	}
	return msg.wParam;
}
