// animation4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <glut.h>

void Display(void);
void CreateEnvironment(void);
void MakeGeometry(void);
void MakeLighting(void);
void MakeCamera(int, int, int);
void HandleKeyboard(unsigned char key, int x, int y);
void HandleSpecialKeyboard(int key, int x, int y);
void HandleMouse(int, int, int, int);
void HandleMainMenu(int);
void HandleSpeedMenu(int);
void HandleVisibility(int vis);
void HandleIdle(void);
void DrawTextXY(double, double, double, double, char *);
void GiveUsage(char *);

#define TRUE 1
#define FALSE 0
#define PI 3.141592653589793238462643

#define DRAFT 0
#define MEDIUM 1
#define BEST 2

int drawquality = DRAFT;
int spincamera = TRUE;
int cameradirection = 1;
double updownrotate = 60;
int ballbounce = TRUE;
double ballspeed = 2;

#define OVALID 1 
#define SPHEREID 2
#define BOXID 3
#define PLANEID 4
#define TEXTID 5

int main(int argc, char **argv)
{
	int i,j,depth;
	int mainmenu, speedmenu;

	for (i = 1; i < argc; i++)
	{
		if(strstr(argv[i], "-h") != NULL)
			GiveUsage(argv[0]);
		if(strstr(argv[i], "-q") != NULL)
		{
			if (i + 1 >= argc)
				GiveUsage(argv[0]);
			drawquality = atoi(argv[i+1]);
			if(drawquality < DRAFT)
				drawquality = DRAFT;
			if(drawquality > BEST)
				drawquality = BEST;
			i++;
		}
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("OPENGL DEMO");
	glutDisplayFunc(Display);
	glutVisibilityFunc(HandleVisibility); 
	glutKeyboardFunc(HandleKeyboard);
	glutSpecialFunc(HandleSpecialKeyboard);
	glutMouseFunc(HandleMouse);
	CreateEnvironment();

	speedmenu = glutCreateMenu(HandleSpeedMenu);
	glutAddMenuEntry("Slow", 1);
	glutAddMenuEntry("Medium", 2);
	glutAddMenuEntry("Fast", 3);
	mainmenu = glutCreateMenu(HandleMainMenu);
	glutAddMenuEntry("Toggle camera spin", 1);
	glutAddMenuEntry("Toggle ball bounce", 2);
	glutAddSubMenu("Ball speed", speedmenu);
	glutAddMenuEntry("quit", 100);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return(0);
}

void CreateEnvironment(void)
{
		glEnable(GL_DEPTH_TEST);
		if(drawquality == DRAFT)
		{
			glShadeModel(GL_FLAT);
		}
		
		if(drawquality == MEDIUM)
		{
			glShadeModel(GL_SMOOTH);
		}

		if(drawquality == BEST)
		{
			glEnable(GL_LINE_SMOOTH);
			glEnable(GL_POINT_SMOOTH);
			glEnable(GL_POLYGON_SMOOTH);
			glShadeModel(GL_SMOOTH);
			glDisable(GL_DITHER);
		}

		glLineWidth(1.0);
		glPointSize(1.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glFrontFace(GL_CW);
		glDisable(GL_CULL_FACE);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glEnable(GL_COLOR_MATERIAL);
	}

	void Display(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPushMatrix();
		MakeCamera(FALSE, 0, 0);
		MakeLighting();
		MakeGeometry();
		glPopMatrix();

		glutSwapBuffers();

	}

void MakeGeometry(void)
{
		int i;
		double radius = 0.5;
		static double theta = 0;
		GLfloat mshin1[] = {5.0};
		GLfloat mspec1[] = {0.5, 0.5, 0.5, 1.0};
		GLfloat mdiff1[] = {0.6, 0.0, 0.6, 1.0};
		GLfloat mamb1[] = {0.1, 0.0, 0.1, 1.0};
		GLfloat mdiff2[] = {0.0, 1.0, 0.0, 1.0};
		GLfloat mamb2[] = {0.0, 0.2, 0.0, 1.0};
		GLfloat mdiff3[] = {0.5, 0.5, 0.5, 1.0};
		GLfloat mamb3[] = {0.2, 0.2, 0.2, 1.0};

		glLoadName(PLANEID);
		if(drawquality > DRAFT)
			glBegin(GL_POLYGON);
		else
				glBegin(GL_LINE_LOOP);
		glColor3f(0.0, 1.0, 0.0);
		if(drawquality > DRAFT)
		{
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mdiff2);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mamb2);
		}
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(2.0, 0.0, 2.0);
		glVertex3f(2.0, 0.0, -2.0);
		glVertex3f(-2.0, 0.0, -2.0);
		glVertex3f(-2.0, 0.0, 2.0);
		glEnd();

		glLoadName(BOXID);
		glColor3f(0.5, 0.5, 0.5);
		if(drawquality > DRAFT)
		{
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mdiff3);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mamb3);
		}

		glPushMatrix();
		glTranslatef(1.8, 0.2, 1.8);
		if(drawquality > DRAFT)
			glutSolidCube(0.4);
		else
			glutWireCube(0.4);
	
		glTranslatef(-3.6, 0.0, 0.0);
		if(drawquality > DRAFT)
			glutSolidCube(0.4);
		else
			glutWireCube(0.4);
		glPopMatrix();

		glLoadName(SPHEREID);
		glColor3f(0.6,0.0, 0.6);
		if(drawquality > DRAFT)
		{
			glMaterialfv (GL_FRONT, GL_SHININESS, mshin1);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mspec1);
		}

		glPushMatrix();
		glTranslatef(0.0, radius+0.5*(1+sin(PI*theta / 180)), 0.0);
		glScalef(radius, radius, radius);
		if(ballbounce)
			theta += ballspeed;
		if(drawquality > DRAFT)
			glutSolidSphere(1.0, 16, 16);
		else
			glutWireSphere(1.0, 32, 32);
		glPopMatrix();

		glLoadName(OVALID);
		glBegin(GL_LINE_STRIP);
		glColor3f(1.0, 1.0, 1.0);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		for(i =0; i<=180; i++)
			glVertex3f(2*cos(i*PI/180), 1.5*sin(i*PI/180), -2.0);
		glEnd();
		glLoadName(TEXTID);
		DrawTextXY(-2.0, -0.25, 2.0, 0.002, "OpenGL Demo");
	}

void MakeLighting(void)
{
	GLfloat globalambient[] = {0.3, 0.3, 0.3, 1.0};

	GLfloat pos0[] = {1.0, 1.0, 0.0, 0.0};
	GLfloat dif0[] = {0.8, 0.8, 0.8, 1.0};

	GLfloat pos1[] = {5.0, -5.0, 0.0, 0.0};
	GLfloat dif1[] = {0.4, 0.4, 0.4, 1.0};

	if(drawquality > DRAFT)
	{
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalambient);
		glLightfv(GL_LIGHT0, GL_POSITION, pos0);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, dif0);

		glLightfv(GL_LIGHT1, GL_POSITION, pos1);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, dif1);

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHTING);
	}
}

void MakeCamera(int pickmode, int x, int y)
{
	static double theta = 0;
	GLint viewport[4];

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(pickmode == TRUE);
	{
		glGetIntegerv(GL_VIEWPORT, viewport);
		gluPickMatrix(x, viewport[3]-y, 3.0, 3.0, viewport);
	}
	gluPerspective(70.0, 1.0, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5*cos(theta*PI/180)*sin(updownrotate*PI/180), 5*cos(updownrotate*PI/180),
		5*sin(theta*PI/180)*sin(updownrotate*PI/180), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	if(spincamera)
		theta += (cameradirection * 0.2);
}
void HandleKeyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27: 
	case 'Q':
	case 'q': exit(0); break;
	case 's':
	case 'S': spincamera = !spincamera; break;
	case 'b':
	case 'B': ballbounce = !ballbounce; break;
	}
}

void HandleSpecialKeyboard(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_LEFT: cameradirection = -1; break;
	case GLUT_KEY_RIGHT: cameradirection = 1; break;
	case GLUT_KEY_UP: updownrotate -= 2; break;
	case GLUT_KEY_DOWN: updownrotate += 2; break;
	}
}

void HandleMouse(int button, int state, int x, int y)
{
	int i, maxselect = 100, nhits = 0;
	GLuint selectlist[100];
	if(state == GLUT_DOWN)
	{
		glSelectBuffer(maxselect, selectlist);
		glRenderMode(GL_SELECT);
		glInitNames();
		glPushName(-1);

		glPushMatrix();
		MakeCamera(TRUE, x, y);
		MakeGeometry();
		glPopMatrix();
		nhits = glRenderMode(GL_RENDER);

		if(button == GLUT_LEFT_BUTTON) 
		{
		}
		else if(button == GLUT_MIDDLE_BUTTON) 
		{
		}

		if (nhits == -1)
			fprintf(stderr, "select buffer overflow\n");

		if(nhits > 0)
		{
			fprintf(stderr, "\tPicked %d objects: ", nhits);
			for (i = 0; i < nhits; i++)
				fprintf(stderr, "%d " , selectlist[4*i+3]);
			fprintf(stderr, "\n");
		}
	}
}
void HandleMainMenu(int whichone)
{
	switch(whichone)
	{
	case 1: spincamera = !spincamera; break;
	case 2: ballbounce = !ballbounce; break;
	case 100: exit(0); break;
	}
}

void HandleSpeedMenu(int whichone)
{
	switch(whichone)
	{
	case 1: ballspeed = 0.5; break;
	case 2: ballspeed = 2; break;
	case 3: ballspeed = 10; break;
	}
}

void HandleVisibility(int visible)
{
	if(visible == GLUT_VISIBLE)
		glutIdleFunc(HandleIdle);
	else
		glutIdleFunc(NULL);
}

void HandleIdle(void)
{
	glutPostRedisplay();
}

void DrawTextXY(double x, double y, double z, double scale, char *s)
{
	int i;

	glPushMatrix();
	glTranslatef(x,y,z);
	glScalef(scale, scale, scale);
	for(i=0; i<strlen(s); i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
	glPopMatrix();
}

void GiveUsage(char *cmd)
{
	fprintf(stderr, "Usage:	%s [-h] [-q n] \n", cmd); 
	fprintf(stderr, " -h this text\n");
	fprintf(stderr, " -q n quality, 0, 1, 2\n");
	fprintf(stderr, "Key STrokes and Menus:\n");
	fprintf(stderr, " q - quit\n");
	fprintf(stderr, " s - toggle camera spin\n");
	fprintf(stderr, " b - toggle ball bounce \n");
	fprintf(stderr, " left arrow - change rotation direction \n");
	fprintf(stderr, " right arrow - change rotation direction\n");
	fprintf(stderr, " down arrow - rotate camera down\n");
	fprintf(stderr, " up arrow - rotate camera up\n");
	exit(-1);
}