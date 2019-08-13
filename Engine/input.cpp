#include "input.h"

BYTE Input::getGamepadLeftTrigger(UINT n)
{
	return 0;
}

BYTE Input::getGamepadRightTrigger(UINT n)
{
	return 0;
}

BYTE Input::getGamepadThumbLX(UINT n)
{
	return 0;
}

BYTE Input::getGamepadThumbLY(UINT n)
{
	return 0;
}

BYTE Input::getGamepadThumbRX(UINT n)
{
	return 0;
}

BYTE Input::getGamepadThumbRY(UINT n)
{
	return 0;
}

void Input::checkControllers()
{
}

void Input::readCOntrollers()
{
}

Input::Input()
{
}

Input::~Input()
{
}

void Input::initialize(HWND hw, bool capt)
{
}

void Input::keyDown(WPARAM)
{
}

void Input::keyUp(WPARAM)
{
}

bool Input::isKeyDown(UCHAR vkey) const
{
	return false;
}

bool Input::wasKeyPressed(UCHAR vkey) const
{
	return false;
}

bool Input::anyKeyPressed() const
{
	return false;
}

void Input::clearKeyPress(UCHAR vkey)
{
}

void Input::clear(UCHAR what)
{
}

void Input::mouseIn(LPARAM)
{
}

void Input::mouseRawIn(LPARAM)
{
}

void Input::mouseWheelIn(WPARAM)
{
}
