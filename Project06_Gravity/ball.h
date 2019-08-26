// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.h v1.0

#ifndef _SHIP_H                 // Prevent multiple definitions if this 
#define _SHIP_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "..\Engine\entity.h"
#include "..\Engine\constants.h"
const float GRAVITY = 500.0f;
namespace ballNS
{
    const int WIDTH = 60;                   
    const int HEIGHT = 60;                 
    const int X = GAME_WIDTH/2 - WIDTH/2;  
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float ROTATION_RATE = (float)PI/4; 
    const float SPEED = 10; 
	const float ENERGY_LOSS = 100;
	const float MIN_VY = 1.0f;
    const float MASS = 1.0f;             

}

class Ball : public Entity
{
private:
public:
    
	Ball();
    void update(float frameTime);

};
#endif

