#include "CollisionRaw.h"


CollisionRaw::CollisionRaw(void)
{
	void* mem = operator new(sizeof(ball)*m_size);
	grp_b[m_size] = new(mem) ball;
	index_b = 0;
	rect = new QuadRectangle(0.0,0.0,0.0,4.0,4.0,4.0);
	setSpawnPoint(rect->getCenterX(), rect->getCenterY(), rect->getCenterZ());
}

CollisionRaw::CollisionRaw(float x, float y, float z, float ox, float oy, float oz)
{
	void* mem = operator new(sizeof(ball)*m_size);
	grp_b[m_size] = new(mem) ball;
	index_b = 0;
	rect = new QuadRectangle(x,y,z,ox,oy,oz);
	setSpawnPoint(rect->getCenterX(), rect->getCenterY(), rect->getCenterZ());
	
}

void CollisionRaw::addBall(ball *add)
{
	if(index_b < m_size)
	{
		grp_b[index_b] = add;
		index_b++;
	}
}

float CollisionRaw::getBall_X(int index)
{
	if(index >= 0 && index < m_size)
	{
		return grp_b[index]->getPositionX();
	}
}
float CollisionRaw::getBall_Y(int index)
{
	if(index >= 0 && index < m_size)
	{
		return grp_b[index]->getPositionY();
	}

}
float CollisionRaw::getBall_Z(int index)
{
	if(index >= 0 && index < m_size)
	{
		return grp_b[index]->getPositionZ();
	}

}

void CollisionRaw::setSpawnPoint(float x, float y, float z)
{
	if(x > rect->x && x < rect->ox)
		spawnX = x;
	else
		spawnX = rect->getCenterX();

	if(y > rect->y && y < rect->oy)
		spawnY = y;
	else
		spawnY = rect->getCenterY();

	if(z > rect->z && z < rect->oz)
		spawnZ= z;
	else
		spawnZ = rect->getCenterZ();
}

void CollisionRaw::testAndResolveCollisions()
{
	if(index_b == 1)
	{
		resolveWallCollisions(grp_b[0]);
	}
	if(index_b > 1)
	{
		for(int i = 0; i < m_size; ++i)
		{
			resolveWallCollisions(grp_b[i]);
			resolveBallCollisions(grp_b[i], i+1);
		}
	}
}

void CollisionRaw::resolveWallCollisions(ball *cball)
{
	if(cball->getNextPositionX() < rect->x || cball->getNextPositionX() > rect->ox)
		cball->dx *= -1;
	if(cball->getNextPositionY() < rect->y || cball->getNextPositionY() > rect->oy)
		cball->dy *= -1;
	if(cball->getNextPositionZ() < rect->z || cball->getNextPositionZ() > rect->oz)
		cball->dz *= -1;
}

void CollisionRaw::resolveBallCollisions(ball *cball, int index)
{
	for(int i = 0; i < m_size; ++i)
	{
		if(distanceBetweenBalls(cball, grp_b[i]) < (cball->radius + grp_b[i]->radius) && i != index)
		{
			cball->dx *= -1;
			cball->dy *= -1;
			cball->dz *= -1;
		}
	}
}

float CollisionRaw::distanceBetweenBalls(ball *b1, ball *b2)
{
	float deltaX = b2->getNextPositionX() - b1->getNextPositionX();
	float deltaY = b2->getNextPositionY() - b1->getNextPositionY();
	float deltaZ = b2->getNextPositionZ() - b1->getNextPositionZ();
	
	return sqrt(pow(deltaX, 2) + pow(deltaY, 2) + pow(deltaZ, 2));
}

CollisionRaw::~CollisionRaw(void)
{

}
