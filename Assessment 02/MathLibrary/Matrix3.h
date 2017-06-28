#pragma once
#include "Vector3.h"

class Matrix3
{
public:
	// m00 m10 m20
	// m01 m11 m21
	// m02 m12 m22
	union
	{
		float data[9];
		Vector3 m_v3Data[3];
		struct
		{
			float m00, m01, m02, m10, m11, m12, m20, m21, m22;
		};
		struct
		{
			Vector3 right;
			Vector3 forward;
			Vector3 position;
		};
	};

	Matrix3();
	Matrix3
		(const float a_m00, const float a_m01, const float a_m02,
		const float a_m10, const float a_m11, const float a_m12,
		const float a_m20, const float a_m21, const float a_m22);

	Vector3 operator*(const Vector3& other);

	Matrix3 operator*(const Matrix3& other);

	Vector3& operator[](int a_i);

	explicit operator float*();

	void setRotateX(const float a_fRotateX);
	void setRotateY(const float a_fRotateY);
	void setRotateZ(const float a_fRotateZ);
};

