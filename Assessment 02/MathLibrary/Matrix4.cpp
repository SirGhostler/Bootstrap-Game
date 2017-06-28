#include "Matrix4.h"
#include <iostream>
#include <cmath>

Matrix4::Matrix4()
{
	m00 = 1;
	m01 = 0;
	m02 = 0;
	m03 = 0;
	m10 = 0;
	m11 = 1;
	m12 = 0;
	m13 = 0;
	m20 = 0;
	m21 = 0;
	m22 = 1;
	m23 = 0;
	m30 = 0;
	m31 = 0;
	m32 = 0;
	m33 = 1;
}

Matrix4::Matrix4
   (const float a_m00, const float a_m01, const float a_m02, const float a_m03,
	const float a_m10, const float a_m11, const float a_m12, const float a_m13,
	const float a_m20, const float a_m21, const float a_m22, const float a_m23,
	const float a_m30, const float a_m31, const float a_m32, const float a_m33)
{
	m00 = a_m00;
	m01 = a_m01;
	m02 = a_m02;
	m03 = a_m03;
	m10 = a_m10;
	m11 = a_m11;
	m12 = a_m12;
	m13 = a_m13;
	m20 = a_m20;
	m21 = a_m21;
	m22 = a_m22;
	m23 = a_m23;
	m30 = a_m30;
	m31 = a_m31;
	m32 = a_m32;
	m33 = a_m33;
}

Vector4 Matrix4::operator*(const Vector4& other)
{
	// [ m00, m10, m20, m30] * [ x ] = [ x.m00 + y.m10 + z.m20 + w.m03 ]
	// [ m01, m11, m21, m31]   [ y ]   [ x.m01 + y.m11 + z.m21 + w.m13 ]
	// [ m02, m12, m22, m32]   [ z ]   [ x.m02 + y.m12 + z.m22 + w.m23 ]
	// [ m03, m13, m23, m33]   [ w ]   [ x.m03 + y.m13 + z.m23 + w.m33 ]

	return Vector4
	   (m00 * other.v4x + m10 * other.v4y + m20 * other.v4z + m30 * other.v4w,
		m01 * other.v4x + m11 * other.v4y + m21 * other.v4z + m31 * other.v4w,
		m02 * other.v4x + m12 * other.v4y + m22 * other.v4z + m32 * other.v4w,
		m03 * other.v4x + m13 * other.v4y + m23 * other.v4z + m33 * other.v4w);
}

Matrix4 Matrix4::operator*(const Matrix4& other)
{

	return Matrix4
	   (m00 * other.m00 + m10 * other.m01 + m20 * other.m02 + m30 * other.m03,
		m01 * other.m00 + m11 * other.m01 + m21 * other.m02 + m31 * other.m03,
		m02 * other.m00 + m12 * other.m01 + m22 * other.m02 + m32 * other.m03,
		m03 * other.m00 + m13 * other.m01 + m23 * other.m02 + m33 * other.m03,
		
		m00 * other.m10 + m10 * other.m11 + m20 * other.m12 + m30 * other.m13,
		m01 * other.m10 + m11 * other.m11 + m21 * other.m12 + m31 * other.m13,
		m02 * other.m10 + m12 * other.m11 + m22 * other.m12 + m32 * other.m13,
		m03 * other.m10 + m13 * other.m11 + m23 * other.m12 + m33 * other.m13, 

		m00 * other.m20 + m10 * other.m21 + m20 * other.m22 + m30 * other.m23,
		m01 * other.m20 + m11 * other.m21 + m21 * other.m22 + m31 * other.m23,
		m02 * other.m20 + m12 * other.m21 + m22 * other.m22 + m32 * other.m23,
		m03 * other.m20 + m13 * other.m21 + m23 * other.m22 + m33 * other.m23,

		m00 * other.m30 + m10 * other.m31 + m20 * other.m32 + m30 * other.m33,
		m01 * other.m30 + m11 * other.m31 + m21 * other.m32 + m31 * other.m33,
		m02 * other.m30 + m12 * other.m31 + m22 * other.m32 + m32 * other.m33,
		m03 * other.m30 * m13 * other.m31 + m23 * other.m32 + m33 * other.m33);
} 

Vector4& Matrix4::operator[](int a_i)
{
	return m_v4Data[a_i];
}

Matrix4::operator float*()
{
	return data;
}

void Matrix4::setRotateX(const float a_fRotateX)
{
	m11 = cos(a_fRotateX);
	m12 = sin(a_fRotateX);
	m21 = -sin(a_fRotateX);
	m22 = cos(a_fRotateX);

}
void Matrix4::setRotateY(const float a_fRotateY)
{
	m00 = cos(a_fRotateY);
	m02 = -sin(a_fRotateY);
	m20 = sin(a_fRotateY);
	m22 = cos(a_fRotateY);
}
void Matrix4::setRotateZ(const float a_fRotateZ)
{
	m00 = cos(a_fRotateZ);
	m01 = sin(a_fRotateZ);
	m10 = -sin(a_fRotateZ);
	m11 = cos(a_fRotateZ);
}