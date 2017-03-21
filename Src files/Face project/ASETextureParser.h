#ifndef __ASETEXTUREPARSER_H__
#define __ASETEXTUREPARSER_H__

/****
ASETEXTUREPARSER
Programmer: Eric Wright 
****/
#include "CVector.h"
#include <fstream>

using namespace std;

class ASETextureParser
{
public:
	ASETextureParser() : m_texVertices(0), m_texFace(0), buffer(0),
						 m_numTexVerticesCount(-1), m_numTexFacesCount(-1)
	{}
	~ASETextureParser();

	//load the texture file
	void loadFile(char *fileName);

	//get a pointer to the texture vertices
	CVector* getTexVertices() { return m_texVertices; }

	//get a pointer to the face information
	CFace* getFaceDetails() { return m_texFace; }

	int getTexVerticesCount() { return m_numTexVerticesCount; } 

	int getTexFaceCount() { return m_numTexFacesCount; }
	
private:
	//texture vector info
	CVector *m_texVertices;
	//texture face details
	CFace *m_texFace;
	//the number of texture vertices
	int m_numTexVerticesCount;
	//number of texture faces
	int m_numTexFacesCount;

	//input file
	ifstream input;
	//buffer for holding input from the file
	char *buffer;
};

#endif
