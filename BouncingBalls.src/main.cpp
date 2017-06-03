#include "Ball.h"
#include "QuadRectangle.h"
#include "Engine.h"

#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <windows.h>
#include <stdio.h>
using namespace std;


/*
#include <iostream>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <cmath>
#include <windows.h>
#include "Ball.h"
#include "QuadRectangle.h"
#include <GL/glut.h>
//#include <GL\gl.h>
//#include <GL\glu.h>
*/
void drawBall(ball b);
GLfloat* randomColor();
void DrawMyCubeTexture(float x, float y, float z, float s, float h, float d, GLuint texture);
void DrawMyCubeTextureTiled(float x, float y, float z, float s, float h, float d, GLuint texture);
GLuint LoadTexture(const char* filename, int width, int height);
void FreeTexture(GLuint texture);
void drawRoom();
void camera();
void keyboard(unsigned char key, int x, int y);
void reshape(int w, int h);
void init(void);
int main(int argc, char *argv[]);
void drawBallMulti();

//angle of rotaion
	static GLfloat xpos = 0, ypos=0, zpos = 0;
	static GLfloat xrot = 0, yrot = 0, angle=0.0;

//MyTextures
	GLuint Pebbles;
	GLuint Bricks;
	GLuint StoneWall;
	GLuint Sky;
//MyColors
	static GLfloat cyan[]=	{	0.0,	0.8,	0.8	};
	static GLfloat aqua[]=	{	0.0,	1.0,	1.0	};
	static GLfloat black[]=	{	0.0,	0.0,	0.0	};
	static GLfloat blue[]=	{	0.0,	0.0,	1.0	};
	static GLfloat fuchsia[]={	1.0,	0.0,	1.0	};
	static GLfloat gray[]=	{	0.5,	0.5,	0.5	};
	static GLfloat green[]=	{	0.0,	0.5,	0.0	};
	static GLfloat lime[]=	{	0.0,	1.0,	0.0	};
	static GLfloat maroon[]={	0.5,	0.0,	0.0	};
	static GLfloat navyBlue[]={	0.0,	0.0,	0.5	};
	static GLfloat olive[]=	{	0.5,	0.5,	0.0	};
	static GLfloat purple[]={	0.5,	0.0,	0.5	};
	static GLfloat red[]=	{	1.0,	0.0,	0.0	};
	static GLfloat silver[]={	0.75,	0.75,	0.75};
	static GLfloat teal[]=	{	0.0,	0.5,	0.5	};
	static GLfloat white[]=	{	1.0,	1.0,	1.0	};
	static GLfloat yellow[]={	1.0,	1.0,	0.0	};


ball b1;
ball b2;
QuadRectangle room;
Engine engi;

//Code From Swiftless
//modified by Bruno Alevato to read bitmaps file
GLuint LoadTexture(const char* filename, int width, int height)
{
	GLuint texture;
	unsigned char* data;
	FILE* file;

	file = fopen(filename, "rb");
	if(file == NULL) return 0;

	data = (unsigned char* )malloc(width * height * 3);
	unsigned long size = width * height * 3;
	fseek(file, 51, SEEK_CUR);
	fread(data, size, 1, file);
	fclose(file);

	char aux;

	for(int bit_pixel = 0; bit_pixel < size; bit_pixel += 3)
	{
		aux = data[bit_pixel];
		data[bit_pixel] = data[bit_pixel + 2];
		data[bit_pixel + 2] = aux;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	free( data ); //free the texture
	return texture; //return the texture data
}

void FreeTexture(GLuint texture)
{
	glDeleteTextures(1, &texture);
}

void init(void)
{
	Bricks = LoadTexture("textures/1024_bricks.bmp", 1024, 1024);
	Pebbles = LoadTexture("textures/1024_pebbles.bmp", 1024, 1024);
	StoneWall = LoadTexture("textures/256_stone_wall.bmp", 256, 256);
	Sky = LoadTexture("textures/1024_680_sky01.bmp", 1024, 680);

	engi = Engine();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10,10,-10,10,-10,10);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	float silverLight[] = {silver[0],silver[1],silver[2],1};
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT1, GL_SPECULAR, silverLight);
	glLightfv(GL_LIGHT2, GL_AMBIENT, silverLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, silverLight);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
}

void DrawMyCubeTexture(float x, float y, float z, float s, float h, float d, GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	
	//FRONT
		glNormal3d(0,0,1);
		glTexCoord2d(0.0, 0.0);
		glVertex3f(x, y, z); //front-bottom-left
		glTexCoord2d(0.0, 1.0);
		glVertex3f(x, y+h, z); //front-top-left
		glTexCoord2d(1.0, 1.0);
		glVertex3f(x+s, y+h, z); //front-top-right
		glTexCoord2d(1.0, 0.0);
		glVertex3f(x+s, y, z); //front-bottom-right
		//BACK
		glNormal3d(0,0,-1);
		glTexCoord2d(0.0, 0.0);
		glVertex3f(	x, y, z-d);//back-bottom-left
		glTexCoord2d(0.0, 1.0);
		glVertex3f(	x, y+h, z-d);//back-top-left
		glTexCoord2d(1.0, 1.0);
		glVertex3f(	x+s, y+h, z-d); //back-top-right
		glTexCoord2d(1.0, 0.0);
		glVertex3f(	x+s, y, z-d);//back-bottom-right
		//LEFT
		glNormal3d(-1,0,0);
		glTexCoord2d(1.0, 0.0);
		glVertex3f(x, y, z); //front-bottom-left
		glTexCoord2d(0.0, 0.0);
		glVertex3f(x, y, z-d);//back-bottom-left
		glTexCoord2d(0.0, 1.0);
		glVertex3f(x, y+h, z-d);//back-top-left
		glTexCoord2d(1.0, 1.0);
		glVertex3f(x, y+h, z); //front-top-left
		//RIGHT
		glNormal3d(1,0,0);
		glTexCoord2d(0.0, 1.0);
		glVertex3f(x+s, y+h, z); //front-top-right
		glTexCoord2d(1.0, 1.0);
		glVertex3f(x+s, y+h, z-d); //back-top-right
		glTexCoord2d(1.0, 0.0);
		glVertex3f(x+s, y, z-d);//back-bottom-right
		glTexCoord2d(0.0, 0.0);
		glVertex3f(x+s, y, z); //front-bottom-right
		
		//BOTTOM
		glNormal3d(0,-1,0);
		glTexCoord2d(0.0, 0.0);
		glVertex3f(x, y, z); //front-bottom-left
		glTexCoord2d(0.0, 1.0);
		glVertex3f(x, y, z-d);//back-bottom-left
		glTexCoord2d(1.0, 1.0);
		glVertex3f(x+s, y, z-d);//back-bottom-right
		glTexCoord2d(1.0, 0.0);
		glVertex3f(x+s, y, z); //front-bottom-right
		//TOP
		glNormal3d(0,1,0);
		glTexCoord2d(0.0, 0.0);
		glVertex3f(x, y+h, z); //front-top-left
		glTexCoord2d(0.0, 1.0);
		glVertex3f(x, y+h, z-d);//back-top-left
		glTexCoord2d(1.0, 1.0);
		glVertex3f(x+s, y+h, z-d); //back-top-right
		glTexCoord2d(1.0, 0.0);
		glVertex3f(x+s, y+h, z); //front-top-right
	glEnd();
}

void DrawMyCubeTextureTiled(float x, float y, float z, float s, float h, float d, GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	
	//FRONT
		glNormal3d(0,0,1);
		glTexCoord2d(0.0, 0.0);
		glVertex3f(x, y, z); //front-bottom-left
		glTexCoord2d(0.0, 1.0*h);
		glVertex3f(x, y+h, z); //front-top-left
		glTexCoord2d(1.0*s, 1.0*h);
		glVertex3f(x+s, y+h, z); //front-top-right
		glTexCoord2d(1.0*s, 0.0);
		glVertex3f(x+s, y, z); //front-bottom-right
		//BACK
		glNormal3d(0,0,-1);
		glTexCoord2d(0.0, 0.0);
		glVertex3f(	x, y, z-d);//back-bottom-left
		glTexCoord2d(0.0, 1.0*h);
		glVertex3f(	x, y+h, z-d);//back-top-left
		glTexCoord2d(1.0*s, 1.0*h);
		glVertex3f(	x+s, y+h, z-d); //back-top-right
		glTexCoord2d(1.0*s, 0.0);
		glVertex3f(	x+s, y, z-d);//back-bottom-right
		//LEFT
		glNormal3d(-1,0,0);
		glTexCoord2d(1.0*d, 0.0);
		glVertex3f(x, y, z); //front-bottom-left
		glTexCoord2d(0.0, 0.0);
		glVertex3f(x, y, z-d);//back-bottom-left
		glTexCoord2d(0.0, 1.0*h);
		glVertex3f(x, y+h, z-d);//back-top-left
		glTexCoord2d(1.0*d, 1.0*h);
		glVertex3f(x, y+h, z); //front-top-left
		//RIGHT
		glNormal3d(1,0,0);
		glTexCoord2d(0.0, 1.0*h);
		glVertex3f(x+s, y+h, z); //front-top-right
		glTexCoord2d(1.0*d, 1.0*h);
		glVertex3f(x+s, y+h, z-d); //back-top-right
		glTexCoord2d(1.0*d, 0.0);
		glVertex3f(x+s, y, z-d);//back-bottom-right
		glTexCoord2d(0.0, 0.0);
		glVertex3f(x+s, y, z); //front-bottom-right
		
		//BOTTOM
		glNormal3d(0,-1,0);
		glTexCoord2d(0.0, 0.0);
		glVertex3f(x, y, z); //front-bottom-left
		glTexCoord2d(0.0, 1.0*d);
		glVertex3f(x, y, z-d);//back-bottom-left
		glTexCoord2d(1.0*s, 1.0*d);
		glVertex3f(x+s, y, z-d);//back-bottom-right
		glTexCoord2d(1.0*s, 0.0);
		glVertex3f(x+s, y, z); //front-bottom-right
		//TOP
		glNormal3d(0,1,0);
		glTexCoord2d(0.0, 0.0);
		glVertex3f(x, y+h, z); //front-top-left
		glTexCoord2d(0.0, 1.0*d);
		glVertex3f(x, y+h, z-d);//back-top-left
		glTexCoord2d(1.0*s, 1.0*d);
		glVertex3f(x+s, y+h, z-d); //back-top-right
		glTexCoord2d(1.0*s, 0.0);
		glVertex3f(x+s, y+h, z); //front-top-right
	glEnd();
}

void drawRoom()
{
	//Floor
	DrawMyCubeTextureTiled(-5.0, -5.0, 5.0, 10.0 , -.2, 10.0, Pebbles);
	//Ceiling
	DrawMyCubeTexture(-5.0, 5.0, 5.0, 10.0 , .2, 10.0, Sky);
	//LeftWall
	//DrawMyCubeTextureTiled(-5.0, -5.0, 5.0, 10.0 , 10.0, -.2, Bricks);
	//RightWall
	DrawMyCubeTextureTiled(-5.0, -5.0, -5.0, 10 , 10.0, .2, Bricks);
	//BackWall
	DrawMyCubeTextureTiled(-5.0, -5.0, 5.0, -.2 , 10.0, 10, Bricks);
	//FrontWall
	DrawMyCubeTextureTiled(5.0, -5.0, 5.0, .2 , 10.0, 10, Bricks);
}





GLfloat* randomColor(){
	int cl = abs(rand() % 17);

	switch( cl ) {
		case 0: return cyan;
		case 1: return aqua;
		case 2: return black;
		case 3: return blue;
		case 4: return fuchsia;
		case 5: return gray;
		case 6: return green;
		case 7: return lime;
		case 8: return maroon;
		case 9: return navyBlue;
		case 10: return olive;
		case 11: return purple;
		case 12: return red;
		case 13: return silver;
		case 14: return teal;
		case 15: return white;
		case 16: return yellow;
	}
}

void drawBallMulti()
{
	for(int i = 0; i < engi.balls_size; i++)
	{
		drawBall(engi.balls[i]);
	}
}

void drawBall(ball b){
	//
	glPushMatrix();
		glTranslatef(b.x,b.y,b.z);
		//glColor3fv(randomColor());
		glColor3f(0.0,0.8,0.8);  //makes the balls cyan instead of crazy
		glutSolidSphere(b.radius, 28,48);
	glPopMatrix();
}

void display()
{
	glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	camera();
	drawRoom();
	drawBallMulti();
	engi.nextTick();
	glutPostRedisplay();
	glFlush();
	glutSwapBuffers(); //swap the buffers

	angle++;
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specs
	glMatrixMode(GL_PROJECTION); //set the matrix to projection

	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0); //set the perspective (angle of sight, width, height, ,depth)
	glMatrixMode(GL_MODELVIEW); //set the matrix back to model
}

void keyboard(unsigned char key, int x, int y)
{
	if(key=='q')
	{
		xrot += 1;
		if(xrot > 360)
		{
			xrot -= 360;
		}
	}
	if(key=='z')
	{
		xrot -= 1;
		if(xrot < -360)
		{
			xrot += 360;
		}
	}

	if (key=='w')
	{
	float xrotrad, yrotrad;
	yrotrad = (yrot / 180 * 3.141592654f);
	xrotrad = (xrot / 180 * 3.141592654f);
	xpos += float(sin(yrotrad)) ;
	zpos -= float(cos(yrotrad)) ;
	ypos -= float(sin(xrotrad)) ;
	}

	if (key=='s')
	{
	float xrotrad, yrotrad;
	yrotrad = (yrot / 180 * 3.141592654f);
	xrotrad = (xrot / 180 * 3.141592654f);
	xpos -= float(sin(yrotrad));
	zpos += float(cos(yrotrad)) ;
	ypos += float(sin(xrotrad));
	}

	if (key=='d')
	{
	yrot += 1;
	if (yrot >360) yrot -= 360;
	}

	if (key=='a')
	{
	yrot -= 1;
	if (yrot < -360)yrot += 360;
	}

	if (key=='r')
	{
		engi.addBallRand();
	}

	if (key==27)
	{
	exit(0);
	}
}

void camera()
{
	glRotatef(xrot, 1.0,0.0,0.0); //rotate our camera on the x-axis (left and right)
	glRotatef(yrot,0.0,1.0,0.0); //rotate our camera on the y-axis (up and down)
	glTranslated(-xpos,-ypos,-zpos); //translate the screen to the position of our camera.
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Room Of Balls - Amy Brennan, Chris Wells");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();


	glutMainLoop();



	//Free our Textures
	FreeTexture(Bricks);
	FreeTexture(Pebbles);
	FreeTexture(StoneWall);
	FreeTexture(Sky);
	return 0;
}
