#ifndef IMAGE_H
#define IMAGE_H
#include "textureManager.h"
#include "constants.h"

class Image
{
protected:

	Graphics *graphics;    
	TextureManager *textureManager;
	SpriteData spriteData; 
	COLOR_ARGB colorFilter; 
	int     cols;           
	int     startFrame;     
	int     endFrame;       
	int     currentFrame;   
	float   frameDelay;     
	float   animTimer;     
	HRESULT hr;           
	bool    loop;           
	bool    visible;        
	bool    initialized;  
	bool    animComplete;  

public:

	Image();
	virtual ~Image();
	const virtual SpriteData& getSpriteInfo() { return spriteData; }
	virtual bool  getVisible() { return visible; }
	virtual float getX() { return spriteData.x; }
	virtual float getY() { return spriteData.y; }
	virtual float getScale() { return spriteData.scale; }
	virtual int   getWidth() { return spriteData.width; }
	virtual int   getHeight() { return spriteData.height; }
	virtual float getCenterX() { return spriteData.x + spriteData.width / 2 * getScale(); }
	virtual float getCenterY() { return spriteData.y + spriteData.height / 2 * getScale(); }
	virtual float getDegrees() { return spriteData.angle*(180.0f / (float)PI); }
	virtual float getRadians() { return spriteData.angle; }
	virtual float getFrameDelay() { return frameDelay; }
	virtual int   getStartFrame() { return startFrame; }
	virtual int   getEndFrame() { return endFrame; }
	virtual int   getCurrentFrame() { return currentFrame; }
	virtual RECT  getSpriteDataRect() { return spriteData.rect; }
	virtual bool  getAnimationComplete() { return animComplete; }
	virtual COLOR_ARGB getColorFilter() { return colorFilter; }

	virtual void setX(float newX) { spriteData.x = newX; }
	virtual void setY(float newY) { spriteData.y = newY; }
	virtual void setScale(float s) { spriteData.scale = s; }
	virtual void setDegrees(float deg) { spriteData.angle = deg * ((float)PI / 180.0f); }
	virtual void setRadians(float rad) { spriteData.angle = rad; }
	virtual void setVisible(bool v) { visible = v; }
	virtual void setFrameDelay(float d) { frameDelay = d; }
	virtual void setFrames(int s, int e) { startFrame = s; endFrame = e; }
	virtual void setCurrentFrame(int c);
	virtual void setRect();
	virtual void setSpriteDataRect(RECT r) { spriteData.rect = r; }
	virtual void setLoop(bool lp) { loop = lp; }
	virtual void setAnimationComplete(bool a) { animComplete = a; };
	virtual void setColorFilter(COLOR_ARGB color) { colorFilter = color; }
	virtual void setTextureManager(TextureManager *textureM)
	{
		textureManager = textureM;
	}
	virtual bool initialize(Graphics *g, int width, int height,
		int ncols, TextureManager *textureM);
	virtual void flipHorizontal(bool flip) { spriteData.flipHorizontal = flip; }
	virtual void flipVertical(bool flip) { spriteData.flipVertical = flip; }
	virtual void draw(COLOR_ARGB color = graphicsNS::WHITE);
	virtual void draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE); 
	virtual void update(float frameTime);
};

#endif
