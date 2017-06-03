#pragma once
#include "QuadRectangle.h"
#include "Ball.h"
#include <stdio.h>
#include <iostream>
#include <time.h>

using namespace std;

class Engine
{
public:
	QuadRectangle room;
	ball *balls;
	void addBallRand();
	void addBall(ball b);
	void setSpawnPoint(float x, float y, float z);
	bool checkAreaClear(ball b);
	int balls_size;
	void nextTick();
	Engine(void);
	~Engine(void);
private:
	float spawnX, spawnY, spawnZ;
	clock_t lastTime;
	clock_t currTime;
	float distanceBetweenBalls(ball b1, ball b2);
	void checkCollisions();
	void resolveCollision(ball &b1, ball &b2);
};

