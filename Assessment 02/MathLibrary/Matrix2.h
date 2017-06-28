#pragma once
#include "Vector2.h"

class Matrix2
{
public:
	// m00 m10
	// m01 m11
	union
	{
		struct
		{
			float m00, m01, m10, m11;
		};
		float data[4];
		struct
		{
			Vector2 m_v2Data[2];
		};
	};

	Matrix2();
	Matrix2
			(const float a_m00, const float a_m01, 
		     const float a_m10, const float a_m11);

	Vector2 operator*(const Vector2& other);

	Matrix2 operator*(const Matrix2& other);

	Vector2& operator[](int a_i);

	explicit operator float*();

	void setRotate(const float a_fRotate);
};