#include "planet.h"

Planet::Planet() : Entity()
{
    spriteData.x    = planetNS::X;            
    spriteData.y    = planetNS::Y;
    radius          = planetNS::COLLISION_RADIUS;
    mass            = planetNS::MASS;
    startFrame      = planetNS::START_FRAME;    
    endFrame        = planetNS::END_FRAME;    
    setCurrentFrame(startFrame);
}