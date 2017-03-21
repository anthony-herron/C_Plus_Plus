#include "CVector.h"


CVector CVector::operator +(CVector tempVec) const
{
	return CVector(m_x + tempVec.m_x, m_y + tempVec.m_y, m_z + tempVec.m_z);
}

CVector CVector::operator-(CVector tempVec) const
{
	return CVector(tempVec.m_x - m_x , tempVec.m_y - m_y, tempVec.m_z - m_z);
}

CVector CVector::operator*(CVector tempVec) const
{
	return CVector(tempVec.m_x * m_x, tempVec.m_y * m_y, tempVec.m_z * m_z);
}

CVector CVector::operator*(float tempSpeed) const
{
	return CVector(m_x * tempSpeed, m_y * tempSpeed, m_z * tempSpeed);
}


//scale a vector
inline void Scale(CVector& a, float scalar)
{
	a.m_x *= scalar;
	a.m_y *= scalar;
	a.m_z *= scalar;
}

//dot product
inline float Dot(CVector& a, CVector& b)
{
	return (a.m_x * b.m_x + a.m_y * b.m_y + a.m_z * b.m_z);
}
//cross product
inline CVector Cross(CVector& a, CVector& b)
{
	return CVector(	a.m_y*b.m_z - a.m_z*b.m_y,
					a.m_z*b.m_x - a.m_x*b.m_z,
					a.m_x*b.m_y - a.m_y*b.m_x);
}

//normalize a vector
inline void Normalize(CVector& a)
{
	float invMag = 1.f / float(sqrt(a.m_x*a.m_x + a.m_y*a.m_y + a.m_z*a.m_z));
	a.m_x *= invMag;
	a.m_y *= invMag;
	a.m_z *= invMag;
}
//subtract 2 vectors
inline CVector Subtract(CVector& a, CVector& b)
{
	CVector result;
	result.m_x = a.m_x - b.m_x;
	result.m_y = a.m_y - b.m_y;
	result.m_z = a.m_z - b.m_z;
	
	return result;
}
