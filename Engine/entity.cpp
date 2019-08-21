#include "entity.h"
Entity::Entity()
{
	radius = 1.0;
	edge.left = -1;
	edge.top = -1;
	edge.right = 1;
	edge.bottom = 1;
	mass = 1.0;
	velocity.x = 0.0;
	velocity.y = 0.0;
	deltaV.x = 0.0;
	deltaV.y = 0.0;
	active = true;               
	rotatedBoxReady = false;
	collisionType = entityNS::CIRCLE;
	health = 100;
	gravity = entityNS::GRAVITY;
}
void Entity::update(float frameTime)
{
	velocity += deltaV;
	deltaV.x = 0;
	deltaV.y = 0;
	Image::update(frameTime);
	rotatedBoxReady = false;
}

bool Entity::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM)
{
	input = gamePtr->getInput();
	return (Image::initialize(gamePtr->getGraphics(), width, height, ncols, textureM));
}

void Entity::activate()
{
	active = true;
}

void Entity::ai(float frameTime, Entity & ent)
{
}
bool Entity::collidesWith(Entity & ent, VECTOR2 & collisionVector)
{
	if(!active || !ent.getActive())
	return false;
	if (collisionType == entityNS::CIRCLE && ent.getCollisionType() == entityNS::CIRCLE)
		return collideCircle(ent, collisionVector);
	if (collisionType == entityNS::BOX && ent.getCollisionType() == entityNS::BOX)
		return collideBox(ent, collisionVector);
	if (collisionType != entityNS::CIRCLE && ent.getCollisionType() != entityNS::CIRCLE)
		return collideRotateBox(ent, collisionVector);
	else
		if (collisionType == entityNS::CIRCLE)
		{
			bool collide = ent.collideRotatedBoxCircle(*this, collisionVector);
			collisionVector *= -1;
			return collide;
		}
		else
			return collideRotatedBoxCircle(ent, collisionVector);
	return false;
}

bool Entity::collideCircle(Entity & ent, VECTOR2 & collisionVector)
{
	distSquared = *getCenter() - *ent.getCenter();
	distSquared.x = distSquared.x*distSquared.x;
	distSquared.y = distSquared.y*distSquared.y;
	sumRadiiSquared = (radius*getScale()) + (ent.radius*ent.getScale());
	sumRadiiSquared *= sumRadiiSquared;
	if (distSquared.x+ distSquared.y <= sumRadiiSquared)
	{
		collisionVector = *ent.getCenter() - *getCenter();
	}
	return false;
}

bool Entity::collideBox(Entity & ent, VECTOR2 & collisionVector)
{
	if (!active || !ent.getActive())
		return false;
	if ((getCenterX() + edge.right*getScale() >= ent.getCenterX() + ent.getEdge().left*ent.getScale()) &&
		(getCenterX() + edge.left*getScale() <= ent.getCenterX() + ent.getEdge().right*ent.getScale()) &&
		(getCenterY() + edge.bottom*getScale() >= ent.getCenterY() + ent.getEdge().top*ent.getScale()) &&
		(getCenterY() + edge.top*getScale() <= ent.getCenterY() + ent.getEdge().bottom*ent.getScale()) )
	{
		collisionVector = *ent.getCenter() - *getCenter();
		return true;
	}
	return false;
}

bool Entity::collideRotateBox(Entity & ent, VECTOR2 & collisionVector)
{
	computeRotatedBox();
	ent.computeRotatedBox();
	if (projectionsOverlap(ent) && ent.projectionsOverlap(*this))
	{
		collisionVector = *ent.getCenter() - *getCenter();
	}
	return false;
}

bool Entity::collideRotatedBoxCircle(Entity & ent, VECTOR2 & collisionVector)
{
	return false;
}

void Entity::computeRotatedBox()
{
}

bool Entity::projectionsOverlap(Entity & ent)
{
	return false;
}

bool Entity::collideCornerCircle(VECTOR2 corner, Entity & ent, VECTOR2 & collisionVector)
{
	return false;
}

bool Entity::collidePixelPerfect(Entity & ent, VECTOR2 & collisionVector)
{
	return false;
}

bool Entity::outsideRect(RECT rect)
{
	return false;
}

void Entity::damage(int weapon)
{
}

void Entity::bounce(VECTOR2 & collisionVector, Entity & ent)
{
}

void Entity::gravityForce(Entity * other, float frameTime)
{
}

