#include "block.h"

Block::Block() : Entity()
{
    spriteData.x    = blockNS::X;
    spriteData.y    = blockNS::Y;
	spriteData.width = blockNS::WIDTH;
	spriteData.height = blockNS::HEIGHT;
	spriteData.rect.bottom = blockNS::HEIGHT;
	spriteData.rect.right = blockNS::WIDTH;
    radius          = blockNS::COLLISION_RADIUS;
    mass            = blockNS::MASS;
	frameDelay      = 1;
    startFrame      = 0;
    endFrame        = 0;
    setCurrentFrame(startFrame);
	edge.top    = -blockNS::HEIGHT / 2;
	edge.bottom = blockNS::HEIGHT / 2;
	edge.left   = -blockNS::WIDTH / 2;
	edge.right  = blockNS::WIDTH / 2;
	collisionType = entityNS::ROTATED_BOX;

}
void Block::update(float frameTime)
{
	Entity::update(frameTime);
	if (spriteData.x > GAME_WIDTH - blockNS::WIDTH)
		spriteData.x = GAME_WIDTH - blockNS::WIDTH;
	else if (spriteData.x < 0)
		spriteData.x = 0;
}
