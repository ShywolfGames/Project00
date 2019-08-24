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
    } 
    else if (spriteData.x < 0)                 
    {
        spriteData.x = 0;                       
        velocity.x = -velocity.x;              
    }

    if (spriteData.y > GAME_HEIGHT-shipNS::HEIGHT*getScale())
    {
        spriteData.y = GAME_HEIGHT-shipNS::HEIGHT*getScale();
        velocity.y = -velocity.y;              
    }
    else if (spriteData.y < 0)                  
    {
        spriteData.y = 0;                       
        velocity.y = -velocity.y;              
    }
}
