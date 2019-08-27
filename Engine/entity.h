#ifndef _ENTITY_H
#define _ENTITY_H

#include "image.h"
#include "input.h"
#include "game.h"

namespace entityNS
{
	enum COLLISION_TYPE{NONE,CIRCLE,BOX,ROTATED_BOX, PIXEL_PERFECT};
	const float GRAVITY = 6.67428e-11f;
}
enum WEAPON { TORPEDO, SHIP, PLANET };

class Entity : public Image
{
protected:
	entityNS::COLLISION_TYPE collisionType;
	VECTOR2 center;
	VECTOR2 collisionCenter;
	float radius;
	VECTOR2 distSquared;    
	float   sumRadiiSquared;
	RECT    edge;           
	VECTOR2 corners[4];     
	VECTOR2 edge01, edge03;  
	float   edge01Min, edge01Max, edge03Min, edge03Max; 
	VECTOR2 velocity;      
	VECTOR2 deltaV;         
	float   mass;         
	float   health;         
	float   rr;             
	float   force;         
	float   gravity;      
	Input   *input;        
	HRESULT hr;           
	bool    active;         
	bool    rotatedBoxReady;  
	DWORD   pixelsColliding;
	virtual bool collideCircle(Entity &ent, VECTOR2 &collisionVector);
	virtual bool collideBox(Entity &ent, VECTOR2 &collisionVector);
	virtual bool collideRotateBox(Entity &ent, VECTOR2 &collisionVector);
	virtual bool collideRotatedBoxCircle(Entity &ent, VECTOR2 &collisionVector);
	void computeRotatedBox();
	bool projectionsOverlap(Entity &ent);
	bool projectionsOverlap(Entity &ent, VECTOR2 &collisionVector);
	bool collideCornerCircle(VECTOR2 corner, Entity &ent, VECTOR2 &collisionVector);
	bool collidePixelPerfect(Entity &ent, VECTOR2 &collisionVector);
public:
	Entity();
	virtual ~Entity() {}
	virtual const VECTOR2* getCenter()
	{
		center = VECTOR2(getCenterX(), getCenterY());
		return &center;
	}
	virtual const VECTOR2* getCollisionCenter()
	{
		return &collisionCenter;
	}
	// Return radius of collision circle.
	virtual float getRadius() const { return radius; }

	// Return RECT structure used for BOX and ROTATED_BOX collision detection.
	virtual const RECT& getEdge() const { return edge; }

	// Return corner c of ROTATED_BOX
	virtual const VECTOR2* getCorner(UINT c) const
	{
		if (c >= 4)
			c = 0;
		return &corners[c];
	}

	// Return velocity vector.
	virtual const VECTOR2 getVelocity() const { return velocity; }

	// Return active.
	virtual bool  getActive()         const { return active; }

	// Return mass.
	virtual float getMass()           const { return mass; }

	// Return gravitational constant.
	virtual float getGravity()        const { return gravity; }

	// Return health;
	virtual float getHealth()         const { return health; }

	// Return collision type (NONE, CIRCLE, BOX, ROTATED_BOX)
	virtual entityNS::COLLISION_TYPE getCollisionType() { return collisionType; }
	virtual DWORD getpixelsColliding() const { return pixelsColliding; }

	virtual void setCollisionCenter(VECTOR2 cc) { collisionCenter = cc; }
	virtual void  setVelocity(VECTOR2 v) { velocity = v; }
	virtual void  setDeltaV(VECTOR2 dv) { deltaV = dv; }
	virtual void  setActive(bool a) { active = a; }
	virtual void  setHealth(float h) { health = h; }
	virtual void  setMass(float m) { mass = m; }
	virtual void  setGravity(float g) { gravity = g; }
	virtual void  setCollisionRadius(float r) { radius = r; }
	virtual void setCollisionType(entityNS::COLLISION_TYPE ctype)
	{
		collisionType = ctype;
	}
	virtual void setEdge(RECT e) { edge = e; }
	virtual void setRotatedBoxReady(bool r) { rotatedBoxReady = r; }

	virtual void update(float frameTime);
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	virtual void activate();
	virtual void ai(float frameTime, Entity &ent);
	virtual bool outsideRect(RECT rect);
	virtual bool collidesWith(Entity &ent, VECTOR2 &collisionVector);
	virtual void damage(int weapon);
	void bounce(VECTOR2 &collisionVector, Entity &ent);
	void gravityForce(Entity *other, float frameTime);


};
#endif // !_ENTITY_H
