#include "textureManager.h"

TextureManager::TextureManager()
{
	texture = NULL;
	width = 0;
	height = 0;
	file = NULL;
	graphics = NULL;
	initialized = false;
}

TextureManager::~TextureManager()
{
	safeRelease(texture);
}

bool TextureManager::initialize(Graphics * g, const char * f)
{
	try
	{
		graphics = g;
		file = f;
		hr = graphics->loadTexture(file, TRANSCOLOR, width, height, texture);
		if (FAILED(hr))
		{
			safeRelease(texture);
			return false;
		}
	}
	catch (...)
	{
		return false;
	}
	initialized = true;
	return true;
}

void TextureManager::onLostDevice()
{
	if (!initialized)
		return;
	safeRelease(texture);
}

void TextureManager::onResetDevice()
{
	if (!initialized)
		return;
	graphics->loadTexture(file, TRANSCOLOR, width, height, texture);

}
