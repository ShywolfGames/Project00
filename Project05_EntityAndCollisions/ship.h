// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.h v1.0

#ifndef _SHIP_H                 // Prevent multiple definitions if this 
#define _SHIP_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "..\Engine\entity.h"
#include "..\Engine\constants.h"

namespace shipNS
{
    const int WIDTH = 32;                   
    const int HEIGHT = 32;                 
    const int X = GAME_WIDTH/2 - WIDTH/2;  
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float ROTATION_RATE = (float)PI/4; 
    const float SPEED = 100;                
    const float MASS = 300.0f;             
    const int   TEXTURE_COLS = 8;          
    const int   SHIP_START_FRAME = 0;       
    const int   SHIP_END_FRAME = 3;         
    const float SHIP_ANIMATION_DELAY = 0.2f; 
}

class Ship : public Entity
{
private:
	bool shieldOn;
	Image shield;
public:
    
    Ship();
	virtual void draw();
	virtual bool initialize(Game *gamePtr,int width,int height,int ncols,TextureManager *textureM);
    
    void update(float frameTime);
	void damage(WEAPON);
};
#endif

