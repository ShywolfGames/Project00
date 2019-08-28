#include "ship.h"

Ship::Ship() : Entity()
{
    spriteData.width = shipNS::WIDTH;         
    spriteData.height = shipNS::HEIGHT;
    spriteData.x = shipNS::X;                   
    spriteData.y = shipNS::Y;
    spriteData.rect.bottom = shipNS::HEIGHT;    
    spriteData.rect.right = shipNS::WIDTH;
    velocity.x = 0;                             
    velocity.y = 0;                             
    frameDelay = shipNS::SHIP_ANIMATION_DELAY;
    startFrame = shipNS::SHIP_START_FRAME;      
    endFrame     = shipNS::SHIP_END_FRAME;    
    currentFrame = startFrame;
    radius = shipNS::WIDTH/2.0;
	mass = shipNS::MASS;
    collisionType = entityNS::CIRCLE;
}

void Ship::draw()
{
	Image::draw();
	if (shieldOn)
		shield.draw(spriteData, graphicsNS::ALPHA50& colorFilter);

}

bool Ship::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM)
{
	shield.initialize(gamePtr->getGraphics(),width,height,ncols,textureM);
	shield.setFrames(24, 27);
	shield.setCurrentFrame(24);
	shield.setFrameDelay(.1f);
	shield.setLoop(false);
	return (Entity::initialize(gamePtr,width,height,ncols,textureM));
}

void Ship::update(float frameTime)
{
    Entity::update(frameTime);
    spriteData.angle += frameTime * shipNS::ROTATION_RATE; 
    spriteData.x += frameTime * velocity.x;     
    spriteData.y += frameTime * velocity.y;     

    if (spriteData.x > GAME_WIDTH-shipNS::WIDTH*getScale())
    {
        spriteData.x = GAME_WIDTH-shipNS::WIDTH*getScale();
        velocity.x = -velocity.x;   
		audio->playCue(BEEP1);
    } 
    else if (spriteData.x < 0)                 
    {
        spriteData.x = 0;                       
        velocity.x = -velocity.x;
		audio->playCue(BEEP2);
    }

    if (spriteData.y > GAME_HEIGHT-shipNS::HEIGHT*getScale())
    {
        spriteData.y = GAME_HEIGHT-shipNS::HEIGHT*getScale();
        velocity.y = -velocity.y;   
		audio->playCue(BEEP3);
    }
    else if (spriteData.y < 0)                  
    {
        spriteData.y = 0;                       
        velocity.y = -velocity.y;   
		audio->playCue(BEEP4);
    }
	if (shieldOn)
	{
		shield.update(frameTime);
		if (shield.getAnimationComplete())
		{
			shieldOn = false;
			shield.setAnimationComplete(false);
		}
	}
}

void Ship::damage(WEAPON)
{
	shieldOn = true;
	audio->playCue(HIT);
}
