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
    startFrame = 3;      
    endFrame    =3;    
    currentFrame = startFrame;
    radius = shipNS::WIDTH/2.0;
	mass = shipNS::MASS;
	collision = false;
    collisionType = entityNS::CIRCLE;
	target = false;
}

bool Ship::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM)
{
	return (Entity::initialize(gamePtr,width,height,ncols,textureM));
}

void Ship::update(float frameTime)
{
	switch (direction)
	{
	case shipNS::LEFT:
		spriteData.angle -= frameTime * shipNS::ROTATION_RATE;
		break;
	case shipNS::RIGHT:
		spriteData.angle += frameTime * shipNS::ROTATION_RATE;
		break;
	
	}
  
    spriteData.x += frameTime * velocity.x;  
	velocity.x = 0;
    spriteData.y += frameTime * velocity.y;     
	velocity.y = 0;


	Entity::update(frameTime);

	if (spriteData.x > GAME_WIDTH)
		spriteData.x = -shipNS::WIDTH;
	else if (spriteData.x < -shipNS::WIDTH)
		spriteData.x = GAME_WIDTH;

	if (spriteData.y < -shipNS::HEIGHT)
		spriteData.y = GAME_HEIGHT;
	else if (spriteData.y > GAME_HEIGHT)
		spriteData.y = -shipNS::HEIGHT;
  

}
