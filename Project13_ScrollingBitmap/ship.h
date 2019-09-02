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
	enum DIRECTION { NONE, LEFT, RIGHT };
    const int   TEXTURE_COLS = 8;          
    const int   SHIP_START_FRAME = 0;       
    const int   SHIP_END_FRAME = 3;         
	const int   SHIP2_START_FRAME = 8;     
	const int   SHIP2_END_FRAME = 11;       
	const float SHIP_ANIMATION_DELAY = 0.2f;   
	const int   EXPLOSION_START_FRAME = 32; 
	const int   EXPLOSION_END_FRAME = 39;   
	const float EXPLOSION_ANIMATION_DELAY = 0.2f;   
	const int   ENGINE_START_FRAME = 16;    
	const int   ENGINE_END_FRAME = 19;      
	const float ENGINE_ANIMATION_DELAY = 0.1f;  
	const int   SHIELD_START_FRAME = 24;    
	const int   SHIELD_END_FRAME = 27;      
	const float SHIELD_ANIMATION_DELAY = 0.1f; 
	const float TORPEDO_DAMAGE = 46;        
	const float SHIP_DAMAGE = 10;           
}

class Ship : public Entity
{
private:
	float   oldX, oldY, oldAngle;
	float   rotation;               
	shipNS::DIRECTION direction;   
	float   explosionTimer;
	bool    explosionOn;
	bool    engineOn;               
	bool    shieldOn;
	Image   engine;
	Image   shield;
	Image   explosion;
public:
    
    Ship();
	virtual void draw();
	virtual bool initialize(Game *gamePtr,int width,int height,int ncols,TextureManager *textureM);
    
    void update(float frameTime);
	void damage(WEAPON);
	void toOldPosition()
	{
		spriteData.x = oldX;
		spriteData.y = oldY,
			spriteData.angle = oldAngle;
		rotation = 0.0f;
	}
	float getRotation() { return rotation; }
	bool getEngineOn() { return engineOn; }
	bool getShieldOn() { return shieldOn; }
	void setEngineOn(bool eng) { engineOn = eng; }
	void setShieldOn(bool sh) { shieldOn = sh; }
	void setMass(float m) { mass = m; }
	void setRotation(float r) { rotation = r; }
	void rotate(shipNS::DIRECTION dir) { direction = dir; }
	void explode();
	void repair();
};
#endif

