/*
ASEPARSER.H
Programmer:Eric Wright
Purpose:Loads a broke down ASE 3d model format file that we created
EDIT:10_4_07 Trying to convert over to dynamic memory since last nights attempt failed
EDIT:11_19_07 Added closeFile() to check if input is null otherwise it closes the file
**TODO**Modify the load code to allow for only vertex info to be loaded or face info with a bool
*/
#ifndef __ASEPARSER_H__
#define __ASEPARSER_H__
#include "CVector.h"
#include <fstream>


using namespace std;



class ASEParser
{
public:
	ASEParser() : m_vertexCount(-1), m_faceCount(-1), m_facePoints(0), m_faceLines(0)
	{}
	~ASEParser();
	
	
	//load ASE file and find the CENTER of the model
	void loadFile(char *file);
	//close the file
	void closeFile();

	//get a pointer to the vertex Points
	CVector* getFacePoints() { return m_facePoints; }

	//get a pointer to the vertex face lines
	CFace* getFaceLines() { return m_faceLines; }

	int getFaceCount() { return m_faceCount; }

	int getVertexCount() { return m_vertexCount; }
		//center of the model
	float m_modelCenter[3];


private:
	//holds all of the points for the face dynamically
	CVector *m_facePoints;

	//holds all of the lines for the face dynamically
	CFace *m_faceLines;
	//number of vertex points in the mesh
	int m_vertexCount;

	//number of faces in the mesh
	int m_faceCount;



	//ifstream object for loading the file
	ifstream input;
	//buffer for holding input from the file
	char *buffer;
};


#endif
