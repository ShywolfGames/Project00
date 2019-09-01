#include "FontDXApp.h"

FontDXApp::FontDXApp()
{
	dxFontSmall = new TextDX();   
	dxFontMedium = new TextDX();
	dxFontLarge = new TextDX();
}

FontDXApp::~FontDXApp()
{
	releaseAll();
	SAFE_DELETE(dxFontSmall);
	SAFE_DELETE(dxFontMedium);
	SAFE_DELETE(dxFontLarge);
}

void FontDXApp::initialize(HWND hw)
{
	Game::initialize(hw);
	graphics->setBackColor(graphicsNS::BLUE);

	if (dxFontSmall->initialize(graphics, 15, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	if (dxFontMedium->initialize(graphics, 62, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	if (dxFontLarge->initialize(graphics, 124, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	
	return;	
}

void FontDXApp::update()
{

}

void FontDXApp::ai()
{
}

void FontDXApp::collisions()
{

}

void FontDXApp::render()
{
	graphics->spriteBegin();
	dxFontSmall->setFontColor(graphicsNS::BLACK);
	dxFontMedium->setFontColor(graphicsNS::BLACK);
	dxFontLarge->setFontColor(graphicsNS::BLACK);
	dxFontLarge->print("C", 20, 100);
	dxFontMedium->print("C", 114, 148);
	dxFontSmall->print("C", 164, 184);
	graphics->spriteEnd();
}

void FontDXApp::releaseAll()
{
	dxFontSmall->onLostDevice();
	dxFontMedium->onLostDevice();
	dxFontLarge->onLostDevice();
	Game::releaseAll();
}

void FontDXApp::resetAll()
{
	dxFontSmall->onResetDevice();
	dxFontMedium->onResetDevice();
	dxFontLarge->onResetDevice();
	Game::resetAll();
	return;
}
