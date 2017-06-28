#include "Matrix3.h"
#include <iostream>
#include <cmath>

Matrix3::Matrix3()
{
	m00 = 1;
	m01 = 0;
	m02 = 0;
	m10 = 0;
	m11 = 1;
	m12 = 0;
	m20 = 0;
	m21 = 0;
	m22 = 1;
}

Matrix3::Matrix3(const float a_m00, const float a_m01, const float a_m02,
				 const float a_m10, const float a_m11, const float a_m12,
				 const float a_m20, const float a_m21, const float a_m22)
{
	m00 = a_m00;
	m01 = a_m01;
	m02 = a_m02;
	m10 = a_m10;
	m11 = a_m11;
	m12 = a_m12;
	m20 = a_m20;
	m21 = a_m21;
	m22 = a_m22;
}

Vector3 Matrix3::operator*(const Vector3& other)
{
	// [ m00, m10, m20] * [ x ] = [ x.m00 + y.m10 + z.m20 ]
	// [ m01, m11, m21]   [ y ]   [ x.m01 + y.m11 + z.m21 ]
	// [ m02, m12, m22]   [ z ]   [ x.m02 + y.m12 + z.m22 ]

	return Vector3
	(m00 * other.v3x + m10 * other.v3y + m20 * other.v3z,
	 m01 * other.v3x + m11 * other.v3y + m21 * other.v3z,
	 m02 * other.v3x + m12 * other.v3y + m22 * other.v3z);
}

Matrix3 Matrix3::operator*(const Matrix3& other)
{
	// [ m00, m10, m20] * [ n00, n10, n20 ] = [ m00.n00 + m10.n01 + m20.n02, m00.n10 + m10.n11 + m20.n12, m00.n20 + m10.n21 + m20.n22 ]
	// [ m01, m11, m21]   [ n01, n11, n21 ]   [ m01.n00 + m11.n01 + m21.n02, m01.n10 + m11.n11 + m21.n12, m01.n20 + m11.n21 + m21.n22 ]
	// [ m02, m12, m22]   [ n02, n12, n22 ]   [ m02.n00 + m12.n01 + m22.n02, m02.n10 + m12.n11 + m22.n12, m02.n20 + m12.n21 + m22.n22 ]

	return Matrix3
		(m00 * other.m00 + m10 * other.m01 + m20 * other.m02,
		 m01 * other.m00 + m11 * other.m01 + m21 * other.m02,
		 m02 * other.m00 + m12 * other.m01 + m22 * other.m02,
		 m00 * other.m10 + m10 * other.m11 + m20 * other.m12,
		 m01 * other.m10 + m11 * other.m11 + m21 * other.m12,
		 m02 * other.m10 + m12 * other.m11 + m22 * other.m12,
		 m00 * other.m20 + m10 * other.m21 + m20 * other.m22,
		 m01 * other.m20 + m11 * other.m21 + m21 * other.m22,
		 m02 * other.m20 + m12 * other.m21 + m22 * other.m22);
}

Vector3& Matrix3::operator[](int a_i)
{
	return m_v3Data[a_i];
}

Matrix3::operator float*()
{
	return data;
}

void Matrix3::setRotateX(const float a_fRotateX)
{
	m11 = cos(a_fRotateX);
	m12 = sin(a_fRotateX);
	m21 = -sin(a_fRotateX);
	m22 = cos(a_fRotateX);

}
void Matrix3::setRotateY(const float a_fRotateY)
{
	m00 = cos(a_fRotateY);
	m02 = -sin(a_fRotateY);
	m20 = sin(a_fRotateY);
	m22 = cos(a_fRotateY);
}
void Matrix3::setRotateZ(const float a_fRotateZ)
{
	m00 = cos(a_fRotateZ);
	m01 = sin(a_fRotateZ);
	m10 = -sin(a_fRotateZ);
	m11 = cos(a_fRotateZ);
}