#include "ball.h"

ball::ball()
{
	this->radius = 1.0;

	this->x = 0;
	this->y = 0;
	this->z = 0;

	this->sx = 0;
	this->sy = 0;
	this->sz = 0;

	this->dx = 0;
	this->dy = 0;
	this->dz = 0;

	this->msx = 0;
	this->msy = 0;
	this->msz = 0;
}

ball::ball(float r, float x, float y, float z)
{
	this->radius = r;
	this->x = x;
	this->y = y;
	this->z = z;
}

void ball::nextMove(QuadRectangle rect)
{
	this->x += dx*sx;
	this->y += dy*sy;
	this->z += dz*sz;
	//bounce off of the Xvalues 
	if(this->x <= rect.x+radius || this->x >= rect.ox-radius)
	{
		dx *= -1;
	}

	if(this->y <= rect.y+radius || this->y >= rect.oy-radius)
	{
		dy *= -1;
	}

	if(this->z <= rect.z+radius || this->z >= rect.oz-radius)
	{
		dz *= -1;
	}
}

void ball::setPosition(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void ball::setSpeed(float x_ups, float y_ups, float z_ups)
{
	//Set speed sets the x, per sec, y per sec, z per sec
	this->sx = abs(x_ups/1000);
	this->sy = abs(y_ups/1000);
	this->sz = abs(z_ups/1000);

}

void ball::setDirection(int dx, int dy, int dz)
{
	//ensures that the change in x is -1.0, 0, 1.0
	if(dx < 0)
		this->dx = -1.0f;
	else if(dx = 0)
		this->dx = 0.0f;
	else
		this->dx = 1.0f;
	//ensures that the change in y is -1.0, 0, 1.0
	if(dy < 0)
		this->dy = -1.0f;
	else if(dy = 0)
		this->dy = 0.0f;
	else
		this->dy = 1.0f;
	//ensures that the change in z is -1.0, 0, 1.0
	if(dz < 0)
		this->dz = -1.0f;
	else if(dz = 0)
		this->dz = 0.0f;
	else
		this->dz = 1.0f;
}

void ball::setSpeedMax(float mx_ups, float my_ups, float mz_ups)
{
	//Set speed sets the x, per sec, y per sec, z per sec
	msx = abs(mx_ups/1000);
	msy = abs(my_ups/1000);
	msz = abs(mz_ups/1000);
}


float ball::getPositionX()
{
	return this->x;
}
float ball::getPositionY()
{
	return this->y;
}
float ball::getPositionZ()
{
	return this->z;
}

float ball::getNextPositionX()
{
	return x + dx*sx;
	
}
float ball::getNextPositionY()
{
	return y + dy*sy;
	
}
float ball::getNextPositionZ()
{
	return z + dz*sz;
}

ball::~ball(void)
{
}
