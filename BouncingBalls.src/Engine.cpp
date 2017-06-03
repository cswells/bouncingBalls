#include "Engine.h"


Engine::Engine(void)
{
	balls = NULL;
	balls_size = 0;

	room = QuadRectangle(-5.0,-5.0,-5.0,5.0,5.0,5.0);
	setSpawnPoint(room.getCenterX(), room.getCenterY(), room.getCenterZ());
}

void Engine::addBallRand()
{
	float x = room.getCenterX();
	float y = room.getCenterY();
	float z = room.getCenterZ();
	ball b = ball(.5, x, y, z);
	b.setSpeedMax(100,100,100);
	float speedx = rand()%100;
	float speedy = rand()%100;
	float speedz = rand()%100;
	b.setSpeed(speedx, speedy, speedz);
	float dx, dy, dz;

	if(rand()%2 == 1)
		dx = 1;
	else
		dx = -1;

	if(rand()%2 == 1)
		dy = 1;
	else
		dy = -1;

	if(rand()%2 == 1)
		dz = 1;
	else
		dz = -1;

	b.setDirection(dx, dy, dz);

	addBall(b);
}

void Engine::addBall(ball b)
{
	if(checkAreaClear(b))
	{
		if(balls_size == 0)
		{
			balls = new ball[1];
			balls[0] = b;
		}
		else
		{
			ball *temp = new ball[balls_size+1];

			for(int cnt=0; cnt < balls_size; cnt++)
			{
				temp[cnt] = balls[cnt];
			}
			temp[balls_size] = b;

			delete [] balls;
			balls = temp;
		}
		balls_size++;
	}
}

bool Engine::checkAreaClear(ball b)
{
	for(int i = 0; i < balls_size; i++)
	{
		if(distanceBetweenBalls(b, balls[i]) <= 0)
			return false;
	}
	return true;
}

float Engine::distanceBetweenBalls(ball b1, ball b2)
{
	float deltaX = b2.getNextPositionX() - b1.getNextPositionX();
	float deltaY = b2.getNextPositionY() - b1.getNextPositionY();
	float deltaZ = b2.getNextPositionZ() - b1.getNextPositionZ();
	
	return sqrt(pow(deltaX, 2) + pow(deltaY, 2) + pow(deltaZ, 2));
}

void Engine::setSpawnPoint(float x, float y, float z)
{
	if(x > room.x && x < room.ox)
		spawnX = x;
	else
		spawnX = room.getCenterX();

	if(y > room.y && y < room.oy)
		spawnY = y;
	else
		spawnY = room.getCenterY();

	if(z > room.z && z < room.oz)
		spawnZ= z;
	else
		spawnZ = room.getCenterZ();
}

void Engine::nextTick()
{
	checkCollisions();
	for(int i = 0; i < balls_size; i++)
	{
		balls[i].nextMove(room);
	}
}

void Engine::checkCollisions()
{
	for(int i = 0; i < balls_size; i++)
	{
		for(int j = i; j < balls_size; j++)
		{
			if(distanceBetweenBalls(balls[i], balls[j]) <= balls[i].radius + balls[j].radius)
			{
				resolveCollision(balls[i], balls[j]);
			}
		}
	}
}
void Engine::resolveCollision(ball &b1, ball &b2)
{
	float tb2_sx, tb2_sy, tb2_sz;
	float tb2_dx, tb2_dy, tb2_dz;

	tb2_sx = b2.sx;
	tb2_sy = b2.sy;
	tb2_sz = b2.sz;

	tb2_dx = b2.dx;
	tb2_dy = b2.dy;
	tb2_dz = b2.dz;


	b2.dx = b1.dx;
	b2.dy = b1.dy;
	b2.dz = b1.dz;

	b2.sx = b1.sx;
	b2.sy = b1.sy;
	b2.sz = b1.sz;

	b1.dx = tb2_dx;
	b1.dy = tb2_dy;
	b1.dz = tb2_dz;

	b1.sx = tb2_sx;
	b1.sy = tb2_sy;
	b1.sz = tb2_sz;
}

Engine::~Engine(void)
{
}
