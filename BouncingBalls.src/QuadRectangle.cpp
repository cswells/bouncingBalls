#include "QuadRectangle.h"


QuadRectangle::QuadRectangle(float x, float y, float z, float ox, float oy, float oz)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->ox = ox;
	this->oy = oy;
	this->oz = oz;
}

float QuadRectangle::getCenterX()
{
	return x + abs((x - ox)/2);
}
float QuadRectangle::getCenterY()
{
	return y+ abs((y - oy)/2);
}
float QuadRectangle::getCenterZ()
{
	return z + abs((z - oz)/2);
}

QuadRectangle::~QuadRectangle(void)
{

}
