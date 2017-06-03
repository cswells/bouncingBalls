#pragma once
#include <math.h>

class QuadRectangle
{
public:
	float x, y ,z;
	float ox, oy, oz;
	QuadRectangle(){};
	QuadRectangle(float x, float y, float z, float ox, float oy, float oz);
	float getCenterX();
	float getCenterY();
	float getCenterZ();
	~QuadRectangle(void);
};