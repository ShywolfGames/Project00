#include "paddle.h"

Paddle::Paddle() : Entity()
{
    spriteData.x    = paddleNS::X;
    spriteData.y    = paddleNS::Y;
	spriteData.width = paddleNS::WIDTH;
	spriteData.height = paddleNS::HEIGHT;
	spriteData.rect.bottom = paddleNS::HEIGHT;
	spriteData.rect.right = paddleNS::WIDTH;
    radius          = paddleNS::COLLISION_RADIUS;
    mass            = paddleNS::MASS;
	frameDelay      = 1;
    startFrame      = 0;
    endFrame        = 0;
    setCurrentFrame(startFrame);
	edge.top    = -paddleNS::HEIGHT / 2;
	edge.bottom = paddleNS::HEIGHT / 2;
	edge.left   = -paddleNS::WIDTH / 2;
	edge.right  = paddleNS::WIDTH / 2;
	collisionType = entityNS::ROTATED_BOX;

}
void Paddle::update(float frameTime)
{
	Entity::update(frameTime);
	if (spriteData.x > GAME_WIDTH - paddleNS::WIDTH)
		spriteData.x = GAME_WIDTH - paddleNS::WIDTH;
	else if (spriteData.x < 0)
		spriteData.x = 0;
}
