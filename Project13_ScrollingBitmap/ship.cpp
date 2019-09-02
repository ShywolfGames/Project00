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
	oldX = shipNS::X;
	oldY = shipNS::Y;
	oldAngle = 0.0f;
	rotation = 0.0f;
	direction = shipNS::NONE;                   // direction of rotation thruster
	engineOn = false;
	shieldOn = false;
	explosionOn = false;
    collisionType = entityNS::CIRCLE;
}

void Ship::draw()
{
	if (explosionOn)
		explosion.draw(spriteData);
	else 
	{
		Image::draw();
		if (engineOn)
			engine.draw(spriteData);
		if (shieldOn)
			shield.draw(spriteData, graphicsNS::ALPHA50& colorFilter);
	}

}

bool Ship::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM)
{
	engine.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	engine.setFrames(shipNS::ENGINE_START_FRAME, shipNS::ENGINE_END_FRAME);
	engine.setCurrentFrame(shipNS::ENGINE_START_FRAME);
	engine.setFrameDelay(shipNS::ENGINE_ANIMATION_DELAY);

	shield.initialize(gamePtr->getGraphics(),width,height,ncols,textureM);
	shield.setFrames(24, 27);
	shield.setCurrentFrame(24);
	shield.setFrameDelay(.1f);
	shield.setLoop(false);

	explosion.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	explosion.setFrames(shipNS::EXPLOSION_START_FRAME, shipNS::EXPLOSION_END_FRAME);
	explosion.setCurrentFrame(shipNS::EXPLOSION_START_FRAME);
	explosion.setFrameDelay(shipNS::EXPLOSION_ANIMATION_DELAY);
	explosion.setLoop(false);              
	return (Entity::initialize(gamePtr,width,height,ncols,textureM));
}

void Ship::update(float frameTime)
{
    Entity::update(frameTime);
	oldX = spriteData.x;                        // save current position
	oldY = spriteData.y;
	oldAngle = spriteData.angle;

	switch (direction)                          // rotate ship
	{
	case shipNS::LEFT:
		rotation -= frameTime * shipNS::ROTATION_RATE;  // rotate left
		break;
	case shipNS::RIGHT:
		rotation += frameTime * shipNS::ROTATION_RATE;  // rotate right
		break;
	}
	spriteData.angle += frameTime * rotation;   // apply rotation

	if (explosionOn)
	{
		explosion.update(frameTime);
		if (explosion.getAnimationComplete())    // if explosion animation complete
		{
			explosionOn = false;                // turn off explosion
			visible = false;
			explosion.setAnimationComplete(false);
			explosion.setCurrentFrame(shipNS::EXPLOSION_START_FRAME);
		}
	}
	if (engineOn)
	{
		velocity.x += (float)cos(spriteData.angle) * shipNS::SPEED * frameTime;
		velocity.y += (float)sin(spriteData.angle) * shipNS::SPEED * frameTime;
		engine.update(frameTime);
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
}

void Ship::explode()
{
}

void Ship::repair()
{
	active = true;
	health = FULL_HEALTH;
	explosionOn = false;
	engineOn = false;
	shieldOn = false;
	rotation = 0.0f;
	direction = shipNS::NONE;           
	visible = true;
}
