#pragma once

class Vector3
{
public:

	// Data Union and Data Struct
	union
	{
		struct
		{
			float v3x;
			float v3y;
			float v3z;
		};
		float data[3];
	};

	Vector3();
	Vector3(float v3x, float v3y, float v3z);

	Vector3(const Vector3& other) = default;
	~Vector3() = default;

	// Equals Operator
	Vector3& operator=(const Vector3& other) = default;
	// Addition Operator
	Vector3 operator+(const Vector3& other) const;
	// Subtraction Operator
	Vector3 operator-(const Vector3& other) const;
	// Multiplication Operator [V = V x f (Vector Scale)]
	Vector3 operator*(const float& other) const;
	// Division Operator
	Vector3 operator/(const float& other) const;

	// Sub Script Operator f = V[n]
	// Sub Script Operator Returning Reference V[n] = f
	float& operator[](int a_other);

	// Dot Product [f = V.dot(V)]
	float dot(const Vector3& other);
	// Cross Product [f = V.cross( V )]
	Vector3 cross(const Vector3& other);
	// Magnitude [f = V.magnitude()]
	float magnitude() const;
	// Normalize [f = V.nomalize()]
	void normalise();
	// Cast Operator [float* fp = (float*)V]
	explicit operator float*();
};

static Vector3 operator*(const float a_fScale, const Vector3 & other)
{
	return other * a_fScale;
}