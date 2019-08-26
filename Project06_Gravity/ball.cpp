#include "ball.h"

Ball::Ball() : Entity()
{
    spriteData.width = ballNS::WIDTH;
    spriteData.height = ballNS::HEIGHT;
    spriteData.x = ballNS::X;
    spriteData.y = ballNS::Y;
    spriteData.rect.bottom = ballNS::HEIGHT;
    spriteData.rect.right = ballNS::WIDTH;
    velocity.x = ballNS::SPEED;
    velocity.y = ballNS::SPEED;
    frameDelay = 1;
    startFrame = 0;
    endFrame     = 0;
    currentFrame = startFrame;
    radius = ballNS::WIDTH/2.0;
	mass = ballNS::MASS;
    collisionType = entityNS::CIRCLE;
}


void Ball::update(float frameTime)
{
    Entity::update(frameTime);
    spriteData.x += frameTime * velocity.x;     
    spriteData.y += frameTime * velocity.y;     

    if (spriteData.x > GAME_WIDTH- ballNS::WIDTH)
    {
        spriteData.x = GAME_WIDTH- ballNS::WIDTH;
        velocity.x = -velocity.x;               
    } 
    else if (spriteData.x < 0)                 
    {
        spriteData.x = 0;                       
        velocity.x = -velocity.x;              
    }

    if (spriteData.y > GAME_HEIGHT- ballNS::HEIGHT)
    {
        spriteData.y = GAME_HEIGHT- ballNS::HEIGHT;
        velocity.y = -ballNS::ENERGY_LOSS;
		if (velocity.y< ballNS::MIN_VY)
		{
			spriteData.y = GAME_HEIGHT / 4;
			velocity.x = ballNS::SPEED;
		}
		velocity.y = -velocity.y;
    }
    else if (spriteData.y < 0)                  
    {
        spriteData.y = 0;                       
        velocity.y = -velocity.y;                                                                                                                                                              
    }
	velocity.y += frameTime *                                 GRAVITY;
	                                                            
}

                                                                                                                                                        