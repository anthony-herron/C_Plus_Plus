/*
ASEPARSER.CPP
Programmer: Eric Wright
REmade this to load the entire ASE file and process the parts we need for this class
10-15-07 - Eric Wright - Added in code to make the parser properly release its memory
*/

#include "ASEParser.h"

ASEParser::~ASEParser()
{
	if(buffer)
	{
		delete [] buffer;
		buffer = NULL;
	}

	if(m_facePoints)
	{
		delete [] m_facePoints;
		m_facePoints = NULL;
	}

	if(m_faceLines)
	{
		delete [] m_faceLines;
		m_faceLines = NULL;
	}
}

void ASEParser::loadFile(char *file)
{
	//make sure any previous file inputs are already closed
	//closeFile();

	//open up a new file
	input.open(file);
		
	//buffer to hold data from the file
	buffer = new char[256];

	//maintains the index position given from the file
	int pointIndex = 0;
	
	
	//use this variable to retrieve floating point vertex values for individual points
	float vertexValue = 0.0f;

	//variable used to hold the search string to insert inside of if statements for speed opt.
	char *searchNumVertex = NULL;
	char *searchNumFaces = NULL;
	char *searchMeshVertex = NULL;

	char *searchFaceVertices = NULL;
	//hold specific search string values for A:, B:, and C: for MESH_FACE_LIST
	char *searchFaceA = NULL;
	char *searchFaceB = NULL;
	char *searchFaceC = NULL;
	
	//keep moving through the file until you reach the end of file
	while(!input.eof())
	{
		input >> buffer;
		
		if(m_vertexCount == -1)
		{
			//search for the string MESH_NUMVERTEX to retrieve number of vertices
			searchNumVertex = strstr(buffer, "*MESH_NUMVERTEX");
			
			//if searchNumVertex is null then it didn't find the string
			if(searchNumVertex)
			{
				//recieve what should be the vertex number
				input >> buffer;

				//store the number of vertices
				m_vertexCount = strtol(static_cast<const char*>(buffer),NULL,0);

				//create the space to hold all the verts
				m_facePoints = new CVector[m_vertexCount];
			}
		}
				
		if(m_faceCount == -1)
		{
			//search for the total number of faces
			searchNumFaces = strstr(buffer, "*MESH_NUMFACES");

			//is searchNumFaces is null then it didn't find the string
			if(searchNumFaces)
			{
				//recieve what should be the number of faces
				input >> buffer;
				//store the number of faces
				m_faceCount = strtol(static_cast<const char*>(buffer),NULL,0);

				//create the space to hold all the faces
				m_faceLines = new CFace[m_faceCount];
			}
		}
		//this block can be optimized to just use *MESH_VERTEX, but for clarity i'll split it

		//now load the vertices
		//find the string *MESH_VERTEX_LIST that tells us were ready to begin storing vertices
		searchMeshVertex = strstr(buffer, "*MESH_VERTEX_LIST");
		if(searchMeshVertex)
		{
			//skip paste the lingering {
			input >> buffer;
			//now skip towards the string which should be MESH_VERTEX
			input >> buffer;
			//we know the vertex count so run a loop to grab values from the file
			for(int i = 0; i < m_vertexCount; i++)
			{
				//start each vertex selection validating the MESH_VERTEX
				//string as a starting point
				searchMeshVertex = strstr(buffer, "*MESH_VERTEX");
				//make sure that the string was found
				if(searchMeshVertex)
				{
					//first load the index value for the point
					input >> pointIndex;
					//next load the vertex value and place it in the vertices
					//corresponding to vertex index
					input >> vertexValue;
					m_facePoints[pointIndex].m_x = vertexValue;
					//find the center of the model
					m_modelCenter[0] += m_facePoints[pointIndex].m_x;

					input >> vertexValue;
					m_facePoints[pointIndex].m_y = vertexValue;
					//find center of model
					m_modelCenter[1] += m_facePoints[pointIndex].m_y;

					input >> vertexValue;
					m_facePoints[pointIndex].m_z = vertexValue;
					//find center of the model
					m_modelCenter[2] += m_facePoints[pointIndex].m_z;

					//reload the buffer so it starts off on *MESH_VERTEX
					input >> buffer;
					//yes I know this can be optimized but its late!
				}
			}

			/*******Calculate Center of Model****************/
			m_modelCenter[0] /= m_vertexCount;
			m_modelCenter[1] /= m_vertexCount;
			m_modelCenter[2] /= m_vertexCount;

			//center model
			for(int i = 0; i < m_vertexCount; i++)
			{
				m_facePoints[i].m_x -= m_modelCenter[0];
				m_facePoints[i].m_y -= m_modelCenter[1];
				m_facePoints[i].m_z -= m_modelCenter[2];
			}

			/*************END OF CALCULATE CENTER OF MODEL**********/

		}

		//find the string's *MESH_FACE_LIST to validate the face list is there
		//then start grabbing the faces with *MESH_FACE
		
		searchFaceVertices = strstr(buffer, "*MESH_FACE_LIST");
		if(searchFaceVertices)
		{
			//we will only grab the values A,B,C for our purposes in this project
			
			//if it isn't null we have a fit!
			//face index
			int faceIndex = 0;
			//buffer for recieving integer input from file(stuff that precedes A,B,C)
			int faceValues = 0;

			if(searchFaceVertices)
			{
				//set search for face vertices to NULL so I can keep checking
				//where to update my MESH_FACE Counter
				searchFaceVertices = NULL;

				while(faceIndex < m_faceCount)
				{
					//recieve input from the file
					//this should either be A:, B:, or C: so we can know when to recieve 
					//the integer variable that we want
					input >> buffer;

					//this part automatically skips opening brace
					searchFaceVertices = strstr(buffer, "*MESH_FACE");

					if(searchFaceVertices)
					{
						//skip the "MESH_FACE" part
						input >> buffer;
						//skip the face index since we alreayd keep track of that
						input >> buffer;

						searchFaceA = strstr(buffer,"A:");
						//if A: is found capture face A; the int is the next spot in buffer
						if(searchFaceA)
						{
							input >> faceValues;
							m_faceLines[faceIndex].m_a = faceValues;
						}

						input >> buffer;
						searchFaceB = strstr(buffer,"B:");
						//if B: is found capture face B
						if(searchFaceB)
						{
							input >> faceValues;
							m_faceLines[faceIndex].m_b = faceValues;
						}

						input >> buffer;
						searchFaceC = strstr(buffer,"C:");
						//if C: is found capture face C
						if(searchFaceC)
						{
							input >> faceValues;
							m_faceLines[faceIndex].m_c = faceValues;

							//increment the faceIndex since we have reached a new face value
							faceIndex++;

							//reset searchFaceVertices to NULL so that the next
							//occurance of *MESH_FACE can be found
							searchFaceVertices = NULL;
							
						}
						/*for any other parts inside of MESH_FACE LIST just do
						a search for the string and repeat the process as done above*/

						
					}
				}
			}
		}//end of mesh face list if
	}
	input.close();
}

void ASEParser::closeFile()
{
	//if(input)
	//{
		input.close();
	//}
}


