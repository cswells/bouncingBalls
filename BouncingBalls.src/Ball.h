#pragma once
#include <math.h>
#include "QuadRectangle.h"
class ball
{
public:
	float x, y, z;
	float radius;
	float sx, sy, sz;
	float dx, dy, dz;
	float msx, msy, msz;
	ball();
	ball(float r, float x, float y, float z);
	~ball(void);
	

	void nextMove(QuadRectangle rect);

	void setPosition(float x, float y, float z);
	void setSpeed(float xps, float yps, float zps);
	void setDirection(int dx, int dy, int dz);
	void setSpeedMax(float mx_ups, float my_ups, float mz_ups);

	float getPositionX();
	float getPositionY();
	float getPositionZ();

	float getNextPositionX();
	float getNextPositionY();
	float getNextPositionZ();
};