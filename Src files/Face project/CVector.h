#ifndef __CVECTOR_H__
#define __CVECTOR_H__

#include <math.h>

/*CVECTOR.C
Programmer:Eric Wright
EDIT:10_04_07:Changed CVertex class to CVector
*/

class CVector
{
public:
	CVector()
	{
		//initialize points to zero
		m_x = m_y = m_z = 0;
	}

	CVector(float x, float y, float z) 
		: m_x(x), m_y(y), m_z(z)
	{}

	CVector operator+(CVector tempVec) const;
	CVector operator-(CVector tempVec) const;
	CVector operator*(CVector tempVec) const;
	//overload the multiplication operator for the speed
	CVector operator*(float tempSpeed) const;

	//the x,y,z coords
	float m_x, m_y, m_z;

};


class CFace
{
public:
	CFace()
	{
		//initialize the faces to zero
		m_a = m_b = m_c = 0;
	}
	//the a,b,c faces used to link points
	int m_a, m_b, m_c;
};



#endif
