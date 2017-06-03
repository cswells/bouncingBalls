#pragma once
#include "ball.h"
#include "QuadRectangle.h"
#include <math.h>
#include <iostream>
#include <new>
using namespace std;

class CollisionRaw
{
	static const int m_size = 10;
public:
	CollisionRaw(void);
	CollisionRaw(float x, float y, float z, float ox, float oy, float oz);
	void setSpawnPoint(float x, float y, float z);
	void testAndResolveCollisions();
	void addBall(ball *add);
	float getBall_X(int index);
	float getBall_Y(int index);
	float getBall_Z(int index);
	~CollisionRaw(void);
private:
	ball *grp_b[m_size];
	int index_b;
	QuadRectangle *rect;
	float spawnX, spawnY, spawnZ;
	void resolveWallCollisions(ball *cball);
	float distanceBetweenBalls(ball *b1, ball *b2);
	void resolveBallCollisions(ball *cball, int index);

};

