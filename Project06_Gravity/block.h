
#ifndef _BLOCK_H               
#define _BLOCK_H              
#define WIN32_LEAN_AND_MEAN

#include "..\Engine\entity.h"
#include "..\Engine\constants.h"

namespace blockNS
{
    const int   WIDTH = 30;                
    const int   HEIGHT = 30;               
    const int   COLLISION_RADIUS = 30/2;   
    const int   X = GAME_WIDTH/2 - WIDTH; 
    const int   Y = GAME_HEIGHT - HEIGHT*2;
    const float MASS = 1.0e6f;             
    const int   SPEED = 0;           
         
}

class Block : public Entity 
{
public:

	Block();
	void update(float frameTime);
};
#endif

