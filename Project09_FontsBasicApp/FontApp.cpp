#include "FontApp.h"

FontApp::FontApp()
{
	fontCK = new Text();
}

FontApp::~FontApp()
{
	releaseAll();
	safeDelete(fontCK);
}

void FontApp::initialize(HWND hw)
{
	Game::initialize(hw);

	if (!nebulaTexture.initialize(graphics, NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error loading nebula  texture"));


	if (!nebula.initialize(graphics, 0,0,0,&nebulaTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing nebula"));

	if (!fontCK->initialize(graphics, FONT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing font"));

	return;	
}

void FontApp::update()
{

}

void FontApp::ai()
{
}

void FontApp::collisions()
{

}

void FontApp::render()
{
	graphics->spriteBegin();
	nebula.draw();
	fontCK->setProportional(false);
	fontCK->setFontColor(graphicsNS::BLACK);
	fontCK->setBackColor(graphicsNS::TRANSCOLOR);
	fontCK->setFontHeight(textNS::FONT_HEIGHT * 2);
	fontCK->print("C", 20, 100);
	fontCK->setFontHeight(textNS::FONT_HEIGHT);
	fontCK->print("C", 114, 148);
	fontCK->setFontHeight(textNS::FONT_HEIGHT / 4);
	fontCK->print("C", 164, 184);
	graphics->spriteEnd();
}

void FontApp::releaseAll()
{
	nebulaTexture.onLostDevice();
	Game::releaseAll();
}

void FontApp::resetAll()
{
	nebulaTexture.onResetDevice();
	Game::resetAll();
	return;
}
