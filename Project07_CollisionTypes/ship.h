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
    const int WIDTH = 64;                   
    const int HEIGHT = 64;                 
    const int X = GAME_WIDTH/2 - WIDTH/2;  
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float ROTATION_RATE = (float)PI/3; 
    const float SPEED = 100;                
    const float MASS = 300.0f;    
	enum DIRECTION{NONE,LEFT,RIGHT};
    const int   TEXTURE_COLS = 8;          
    const int   SHIP_START_FRAME = 0;       
    const int   SHIP_END_FRAME = 3;         
    const float SHIP_ANIMATION_DELAY = 0.2f; 
}

class Ship : public Entity
{
private:
	bool collision;
	bool target;
	shipNS::DIRECTION direction;
public:

	Ship();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);
	void setCollision(bool c) { collision = c; }
	virtual void setCollisionType(entityNS::COLLISION_TYPE ctype)
	{
		collisionType = ctype;
	}
	void setEdge(RECT e) { edge = e; }
	void setTarget(bool t) { target = t; }
	bool getCollision() { return collision; }
	entityNS::COLLISION_TYPE getCollisionType() { return collisionType; }
	void rotate(shipNS::DIRECTION dir) { direction = dir; }
	void forward() 
	{
		velocity.x = (float)cos(spriteData.angle)*shipNS::SPEED;
		velocity.y = (float)sin(spriteData.angle)*shipNS::SPEED;
	}
	void reverse()
	{
		velocity.x = -(float)cos(spriteData.angle)*shipNS::SPEED;
		velocity.y = -(float)sin(spriteData.angle)*shipNS::SPEED;
	}

};
#endif

