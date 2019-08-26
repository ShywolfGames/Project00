
#ifndef _PLANET_H               
#define _PLANET_H              
#define WIN32_LEAN_AND_MEAN

#include "..\Engine\entity.h"
#include "..\Engine\constants.h"

namespace paddleNS
{
    const int   WIDTH = 120;                
    const int   HEIGHT = 30;               
    const int   COLLISION_RADIUS = 120/2;   
    const int   X = GAME_WIDTH/2 - WIDTH; 
    const int   Y = GAME_HEIGHT - HEIGHT*2;
    const float MASS = 1.0e6f;             
    const int   SPEED = 200;           
         
}

class Paddle : public Entity 
{
public:

	Paddle();
	void update(float frameTime);
};
#endif

