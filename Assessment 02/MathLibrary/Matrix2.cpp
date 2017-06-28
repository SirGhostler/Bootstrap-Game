#include "Matrix2.h"
#include <iostream>
#include <cmath>

Matrix2::Matrix2()
{
	m00 = 1;
	m01 = 0; 
	m10 = 0; 
	m11 = 1;
}

Matrix2::Matrix2(const float a_m00, const float a_m01,
				 const float a_m10, const float a_m11)
{
	m00 = a_m00;
	m01 = a_m01;
	m10 = a_m10;
	m11 = a_m11;
}


Vector2 Matrix2::operator*(const Vector2& other)
{
	return Vector2
		(m00 * other.v2x + m10 * other.v2y,
		 m01 * other.v2x + m11 * other.v2y);
}

Matrix2 Matrix2::operator*(const Matrix2& other)
{
	return Matrix2
		(m00 * other.m00 + m10 * other.m01,
		 m01 * other.m00 + m11 * other.m01,
		 m00 * other.m10 + m10 * other.m11,	
		 m01 * other.m10 + m11 * other.m11);
}

Vector2& Matrix2::operator[](int a_i)
{
	return m_v2Data[a_i];
}

Matrix2::operator float*()
{
	return data;
}

void Matrix2::setRotate(const float a_fRotate)
{
	// cos sin
	// -sin cos

	m00 = cos(a_fRotate);
	m01 = sin(a_fRotate);
	m10 = -sin(a_fRotate);
	m11 = cos(a_fRotate);
}