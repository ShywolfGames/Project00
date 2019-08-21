#ifndef _ENTITY_H
#define _ENTITY_H

#include "image.h"
#include "input.h"
#include "game.h"

namespace entityNS
{
	enum COLLISION_TYPE{NONE,CIRCLE,BOX,ROTATED_BOX};
	const float GRAVITY = 6.67428e-11f;
}

class entity:public Image
{
protected:
	entityNS::COLLISION_TYPE collisionType;
	VECTOR2 center;
	float radius;

};
#endif // !_ENTITY_H
