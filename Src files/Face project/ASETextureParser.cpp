#include "ASETextureParser.h"


ASETextureParser::~ASETextureParser()
{
	if(buffer)
	{
		delete [] buffer;
		buffer = NULL;
	}	

	if(m_texVertices)
	{
		delete [] m_texVertices;
		m_texVertices = NULL;
	}

	if(m_texFace)
	{
		delete [] m_texFace;
		m_texFace = NULL;
	}
}

void ASETextureParser::loadFile(char *fileName)
{
	input.open(fileName);

	//buffer to hold input data from the file
	buffer = new char[256];

	//maintain the index position from the given file
	int pointIndex = 0;

	//holds the floating point vertice information for the texture from the file
	float texVertex[3];
	//holds the face points for the texture from the file inpoout
	int texFace[3];

	//variables used to hold search string information
	char *searchNumTexVertex = NULL;
	char *searchNumTexFace = NULL;
	char *searchTexVert = NULL;
	char *searchTexFace = NULL;

	while(!input.eof())
	{
		input >> buffer;

		if(m_numTexVerticesCount == -1)
		{
			// search for string *NUMVERTEX to find total Verts
			searchNumTexVertex = strstr(buffer, "*MESH_NUMTVERTEX");

			if(searchNumTexVertex)
			{
				//recieve input which should be the total of verts
				input >> buffer;

				//store the number of vertices
				m_numTexVerticesCount = strtol(static_cast<const char*>(buffer),NULL,0);

				//create the memory to hold all the verts
				m_texVertices = new CVector[m_numTexVerticesCount];

			}
		}
		//now find out the total number of faces
		if(m_numTexFacesCount == -1)
		{
			//search for the total number of faces
			searchNumTexFace = strstr(buffer, "*MESH_NUMTVFACES");

			//if searchNumFaces is null then it didn't find the string
			if(searchNumTexFace)
			{
				//retrieve the number of faces
				input >> buffer;
				//store the number of faces
				m_numTexFacesCount = strtol(static_cast<const char*>(buffer), NULL, 0);

				//create the space to hold all faces
				m_texFace = new CFace[m_numTexFacesCount];
			}
		}

		//now load the texture vertices
		//find the string *MESH_TVERTEXLIST that initiates the loading process for us
		searchTexFace = strstr(buffer, "*MESH_TVERTLIST");
		if(searchTexFace)
		{
			//skip past the {
			input >> buffer;
			

			//run a loop to grab the necessary amount of texture Verts from the file
			for(int i = 0; i < m_numTexVerticesCount; i++)
			{
				searchTexVert = strstr(buffer, "*MESH_TVERT");
				//make sure that the string is found
				if(searchTexVert)
				{
					//first load the index value for the tex vertex
					input >> pointIndex;
					//load the texture vertex (x, y, z)
					input >> texVertex[0] >> texVertex [1] >> texVertex[2];

					//store the texture Vertex information with the correct vertex index
					m_texVertices[pointIndex].m_x = texVertex[0];
					m_texVertices[pointIndex].m_y = texVertex[1];
					m_texVertices[pointIndex].m_z = texVertex[2];

				}
				//now load the first string which should be *MESH_TVERT
				input >> buffer;
			}
		}



		//reset the point index to zero so we can use it for the texture faces
		pointIndex = 0;
		//now start grabbing the texture faces
		//search for string *MESH_TFACELIST to find the neccessary position in the file
		searchTexFace = strstr(buffer, "*MESH_TFACELIST");
		if(searchTexFace)
		{
			//get rid of the tailing {
			input >> buffer;

			for(int i = 0; i < m_numTexFacesCount; i++)
			{
				//load the texture face values that correspond to vertex points
				//search for *MESH_TFACE to begin loading sequence
				input >> buffer;

				searchTexFace = strstr(buffer, "*MESH_TFACE");

				if(searchTexFace)
				{
					//grab the face index from the file; dont need to use it
					input >> buffer;
									
					input >> texFace[0] >> texFace[1] >> texFace[2];
					
					//assign the face values to our huge list of values
					m_texFace[i].m_a = texFace[0];
					m_texFace[i].m_b = texFace[1];
					m_texFace[i].m_c = texFace[2];
				}//end of if
			}//end of for
		}//end of if
	}
	
}
