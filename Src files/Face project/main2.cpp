/*
mainfile template
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "glut.h"
#include "ASEParser.h"
#include "ASETextureParser.h"
#include "Image.h"
using namespace std;
ASEParser parser[8];
ASETextureParser texParser;

//default state
CVector *defaultStatePoints = NULL;
CFace *defaultStateLines = NULL;

//current state
CVector *currentStatePoints = NULL;
CFace *currentStateLines = NULL;

//targetState
CVector *targetStatePoints = NULL;
CFace *targetStateLines = NULL;

//target State == smile
CVector *smileTargetStatePoints = NULL;
CFace *smileTargetStateLines = NULL;
//targetState == surprise
CVector *surpriseTargetStatePoints = NULL;
CFace *surpriseTargetStateLines = NULL;
//targetState == anger
CVector *angerTargetStatePoints = NULL;
CFace *angerTargetStateLines = NULL;

//targetState == sad
CVector *sadTargetStatePoints = NULL;
CFace *sadTargetStateLines = NULL;

//targetState == disgust
CVector *disgustTargetStatePoints = NULL;
CFace *disgustTargetStateLines = NULL;

//targetState == fear
CVector *fearTargetStatePoints = NULL;
CFace *fearTargetStateLines = NULL;

CVector *texFaceVerts = NULL;
CFace *texFace = NULL;

//Load the texture
CImage textureImage;

//rotation angle variable
float GAngle = 0.0f;

// Default to the point rendering mode.
int	renderingMode = 1;
//a variable to be a light switch for lights
bool bLighting = false;

static CVector *tempBuffer;
static int numPoints;
//how fast the animation occurs
float blendSpeed = 0.005;
//holds the value of the number of frames it takes to complete the animation
const float animationFrameSequenceLength = 1/blendSpeed;
//used to tell when to skip to the next target state
const float animationLifetime = animationFrameSequenceLength + 1;
//amount of frames it takes to run the blending animation
int animationFrameCounter = 0;


//Change the Target State that the animation transitions to
//we only need to exchange point info but we'll do both(points,lines) for consistancy
void changeTargetState(CVector *newStatePoints,CFace *newStateLines)
{
	//reset animationFrameCounter to 0
	animationFrameCounter = 0;
	//copy current points into the buffer
	memcpy(tempBuffer,currentStatePoints,sizeof(CVector)*numPoints);
	//transfer the location of the new state points to the new target
	targetStatePoints = newStatePoints;
	targetStateLines = newStateLines;
}

//function to automatically loop through all animations
void chooseAutoRandomTarget()
{
	//light values to associate with different mood switches
	float diffuseGoodMood[] = { 5.0f, 5.0f, 0.0, 1.0f};
	float diffuseBadMood[] = { 2.0f, 0.0f, 0.0f, 1.0f};
	int random;
	
	random = rand() % 9 + 3;
	//keep track of the last used Random number
	static int lastRandomGenerated;
	//if the new random numeber is the same as the last; find another!
	if(random == lastRandomGenerated)
	{
		random = rand() % 9 + 3;
	}
	//store the current of random to ensure it doesn't repeat
	lastRandomGenerated = random;
	//change the target states to update to a new/differnet animation sequence
	switch(random)
	{
		case 1:
		case 2: break;
		case 3:
			{

				changeTargetState(defaultStatePoints, defaultStateLines);
				break;
			}
		case 4:
			{
				glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseBadMood);
				changeTargetState(fearTargetStatePoints, fearTargetStateLines);
				break;
			}
		case 5:
			{
				glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseGoodMood);
				changeTargetState(smileTargetStatePoints, smileTargetStateLines);
				break;
			}
		case 6: 
			{
				glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseGoodMood);
				changeTargetState(surpriseTargetStatePoints, surpriseTargetStateLines);
				break;
			}
		case 7 :
			{
				glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseBadMood);
				changeTargetState(angerTargetStatePoints, angerTargetStateLines);
				break;
			}
		case 8:
			{
				glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseBadMood);
				changeTargetState(sadTargetStatePoints, sadTargetStateLines);
				break;
			}
		case 9:
			{
				glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseBadMood);
				changeTargetState(disgustTargetStatePoints, disgustTargetStateLines);
				break;
			}
		default:
			{
				//could run an animation state here
				break;
			}
	}
	
}

//Interpolation Algorithm

void updateState(float blendSpeed, int pA, int pB, int pC)
{
     // Instruction 11: generate in-between frames here:
                     
}

void enableLights()
{
     
	
		float ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
        float diffuse[] = {1.0f, 1.0f, 0.0f, 1.0f};
		float specular[] = {1.0f, 0.0f, 1.0f, 1.0f};
        float position[] = {-20.0f, 20.0f, 20.0f, 0.0f};
		
		glLightfv(GL_LIGHT0, GL_POSITION, position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);       

        glFrontFace(GL_CW);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_AUTO_NORMAL);
        glEnable(GL_NORMALIZE);
        glEnable(GL_DEPTH_TEST); 
        

}

void initTexture()
{
	GLuint texture;
glGenTextures( 1, &texture );
	//Instruction 3: read the texture image data into memory


	//pass the address from ASETextureParser to the global texture variables
	texFaceVerts = texParser.getTexVertices();
	texFace = texParser.getFaceDetails();

	//Instruction 4: enable 2d textures

	glEnable( GL_TEXTURE_2D );

	//Instruction 5: specify a texture for the texture object

	//Instruction 6: bind the texture object
	glBindTexture( GL_TEXTURE_2D, texture);
	//Instruction 7: set min and mag texture filters parameters here:

	//Instruction 8: apply some environmental effects like lighting to the texture


				
}

void keyPress(unsigned char key, int x, int y) 
{
	switch(key)
	{
		case '1':
			{
				renderingMode = 1;
				
				
				
				break;
			}

		case '2':
			{
				renderingMode = 2;
				break;
			}

		case '3':
			{
				renderingMode = 3;
				changeTargetState(defaultStatePoints, defaultStateLines);
				break;
			}
		case '4':
			{	
				//fear
				renderingMode = 4;
				changeTargetState(fearTargetStatePoints, fearTargetStateLines);
				break;
			}
		case '5':
			{
				//smile
				renderingMode = 5;
				changeTargetState(smileTargetStatePoints, smileTargetStateLines);
				break;
			}
		case '6':
			{
				//surpise
				renderingMode = 6;
				changeTargetState(surpriseTargetStatePoints, surpriseTargetStateLines);
				break;
			}
		case '7':
			{
				//anger
				renderingMode = 7;
				changeTargetState(angerTargetStatePoints, angerTargetStateLines);
				break;
			}
		case '8':
			{
				//sad
				renderingMode = 8;
				changeTargetState(sadTargetStatePoints, sadTargetStateLines);
				break;
			}
		case '9':
			{
				//disgust
				renderingMode = 9;
				changeTargetState(disgustTargetStatePoints, disgustTargetStateLines);
				break;
			}
		case '0':
			{
				
				renderingMode = 0;
				changeTargetState(defaultStatePoints, defaultStateLines);
				break;
			}
		case 'l':
			{
				//if lighting is off turn it on, if its on turn it off
				if(!bLighting)
				{
					bLighting = true;
					glEnable(GL_LIGHTING);
					
				}else
				{
					glDisable(GL_LIGHTING);
					bLighting = false;
				}
				break;
			}
		//escape key exit
		case 27:
			{
				exit(0);
				break;
			}
	}
   
}

void drawPoints()
{
	//Instruction 1: draw just the points
	glColor3f(1.0,0.0,1.0);
	glBegin(GL_POINTS);
	
	for(int i = 0; i < parser[0].getVertexCount(); i++)
	{
          CVector a = currentStatePoints[i];
          
          glVertex3f(a.m_x, a.m_z, a.m_y);
    }
		glEnd();
}

void drawWireFrame()
{

	//Instruction 2: draw the lines to create the wireframe mesh
	glColor3f(1.0,0.0,1.0);
	glBegin(GL_LINES);
	
	for(int i = 0; i < parser[0].getFaceCount(); i++)
	{
          CVector a = currentStatePoints[ currentStateLines[i].m_a];
          CVector b = currentStatePoints[ currentStateLines[i].m_b];
          CVector c = currentStatePoints[ currentStateLines[i].m_c];
          
          glVertex3f(a.m_x, a.m_z, a.m_y);
          glVertex3f(b.m_x, b.m_z, b.m_y);
          
          glVertex3f(b.m_x, b.m_z, b.m_y);
          glVertex3f(c.m_x, c.m_z, c.m_y);
          
          glVertex3f(c.m_x, c.m_z, c.m_y);
          glVertex3f(a.m_x, a.m_z, a.m_y);
          
    }


	glEnd();
	


}

void drawFlatShaded()
{ 
	CVector up(0.0f, 0.0f, 1.0f);
	
	glBegin(GL_TRIANGLES);

	//iterate through the total number of faces to display them
	for (int i = 0; i < parser[0].getFaceCount(); i++){
		//save off the three vertices so we can do some math on them
		CVector a = currentStatePoints[ currentStateLines[i].m_a ];
		CVector b = currentStatePoints[ currentStateLines[i].m_b ];
		CVector c = currentStatePoints[ currentStateLines[i].m_c ];
		
		glVertex3f( c.m_x, c.m_z, c.m_y );
		glVertex3f( b.m_x, b.m_z, b.m_y );
		glVertex3f( a.m_x, a.m_z, a.m_y );
		
	}

	glEnd();
}
void drawTextured()
{ 
//	CVector up(0.0f, 0.0f, 1.0f);
	
	// Instruction 9: bind the texture to the id so it can be placed on the model




	//Instruction 10: iterate through the total number of faces to display them


	glBegin(GL_TRIANGLES);

	
	for (int i = 0; i < parser[0].getFaceCount(); i++)
	{

		
	}

	glEnd();
}

void drawTexturedAnimation()
{ 


	//bind the texture to the id so it can be placed on the model
	glBindTexture(GL_TEXTURE_2D, 0);


	glBegin(GL_TRIANGLES);
	
		//Instruction 12: iterate through the total number of faces to display them
		
		glEnd();
	
}

//callback function to draw the model in either wireframe or full model
void drawModel( void(*drawFunction)() )
{
	drawFunction();

}

void Display(void)
{
	// Clear Depth Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	//Goodies -> Rotation
	//glRotated(GAngle,0,1,0);
	
	//scale the points so they can be seen
	//glScalef(0.005f, 0.005f, 0.005f);
	glScalef(0.007f, 0.007f, 0.007f);
	//default color of all rendered objects is white
	glColor3f(1.0,1.0,1.0);

	

	switch (renderingMode)
	{
		
		case 1:
			{
				drawModel(drawPoints);
				break;
			}
		case 2:
			{
				drawModel(drawWireFrame);
				break;
			}
		
		case 3:
			{
				drawModel(drawTextured);
				break;
			}

		case 4:
			{
				//default
				//changeTargetState(defaultStatePoints,defaultStateLines);
				//changed 4 to 3
							
			}

		case 5:
			{
				//smile
				//changeTargetState(smileTargetStatePoints, smileTargetStateLines);
				//drawModel(drawTexturedAnimation);
				//break;
			}
		case 6:
			{
				//surprise
				//changeTargetState(surpriseTargetStatePoints, surpriseTargetStatePoints);
				//drawModel(drawTexturedAnimation);
				//break;
			}
		case 7:
			{
				//anger
				//changeTargetState(angerTargetStatePoints, angerTargetStatePoints);
				
			}
		case 8:
			{
			}
		case 9:
			{
				drawModel(drawTexturedAnimation);
				break;
			}
		case 0:
			{
				//this has to appear so that updateScene can be called
				drawModel(drawTexturedAnimation);
				//ensure that the animation has run and has some pause time at the end
				//on startup animation counter will be zero so it needs to choose a random target
				//or this could've been implemented with an ifStatement
				if(animationFrameCounter > animationLifetime || !animationFrameCounter)
				{
					//choose random target here
					chooseAutoRandomTarget();
				}
				
				break;
			}

	}
	
	//reset the angle to 0 when 360 hits
	if(GAngle > 360)
	{
		GAngle -= 360;
	}
	else
	{
		GAngle = GAngle + 1;
	}
	

	glFlush();

	glutSwapBuffers();
}

void Timer(int extra)
{
	glutPostRedisplay();
	glutTimerFunc(15,Timer,0);
}

int main(void)
{
	//initialize GLUT
	// Init to double buffering
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowPosition (100, 100);
	glutInitWindowSize (640, 480);
	//enableLights();
	glutCreateWindow("FaceProject");
	glutKeyboardFunc(keyPress);



	//make sure model loading occurs before dispalyFunc or suffer longer load times
	parser[0].loadFile("faceverts.txt");
	defaultStatePoints = parser[0].getFacePoints();
	defaultStateLines = parser[0].getFaceLines();
	numPoints = parser[0].getFaceCount();
	//fill our temp buffer
	tempBuffer = new CVector[numPoints];

	//load the model into memory
	parser[1].loadFile("faceverts.txt");
	//pass the addresses from the ASEPaser to our global variables
	//store our default face vertex positions, and the current state positions
	currentStatePoints = parser[1].getFacePoints();
	currentStateLines = parser[1].getFaceLines();

	//Load the animation states
	//first load the vertex information for the face that smiles
	parser[2].loadFile("smile1.txt");
	smileTargetStatePoints = parser[2].getFacePoints();
	smileTargetStateLines = parser[2].getFaceLines();
	
	//load the surprised state
	parser[3].loadFile("surprise1.txt");
	surpriseTargetStatePoints = parser[3].getFacePoints();
	surpriseTargetStateLines = parser[3].getFaceLines();

	//load the anger face state
	parser[4].loadFile("angry1.txt");
	angerTargetStatePoints = parser[4].getFacePoints();
	angerTargetStateLines = parser[4].getFaceLines();
	
	//load the sad face state
	parser[5].loadFile("sad1.txt");
	sadTargetStatePoints = parser[5].getFacePoints();
	sadTargetStateLines = parser[5].getFaceLines();

	//load disgust state
	parser[6].loadFile("disgust1.txt");
	disgustTargetStatePoints = parser[6].getFacePoints();
	disgustTargetStateLines = parser[6].getFaceLines();

	//load fear state
	parser[7].loadFile("fear1.txt");
	fearTargetStatePoints = parser[7].getFacePoints();
	fearTargetStateLines = parser[7].getFaceLines();
	

	//load the texture parser into memory if it fails say something
	texParser.loadFile("texturedatafile.txt");
	
	//initialize the texture routine
	initTexture();

	

	
	glutDisplayFunc(Display);
	glutTimerFunc(0,Timer,0);
	
	glShadeModel(GL_SMOOTH);		// Default

	// Uncomment this to hide back-facing polygons.
	//glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);	

	glutMainLoop();
	
	//clean up the memory by freeing the mem for the texture
	textureImage.Cleanup();
	return 0;
}