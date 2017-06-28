#pragma once

class Vector4
{
public:

	// Data Union and Data Struct
	union
	{
		struct
		{
			float v4x;
			float v4y;
			float v4z;
			float v4w;
		};
		float data[3];
	};

	Vector4();
	Vector4(float v4x, float v4y, float v4z, float v4w);

	Vector4(const Vector4& other) = default;
	~Vector4() = default;

	// Equals Operator
	Vector4& operator=(const Vector4& other) = default;
	// Addition Operator
	Vector4 operator+(const Vector4& other) const;
	// Subtraction Operator
	Vector4 operator-(const Vector4& other) const;
	// Multiplication Operator [V = V x f (Vector Scale)]
	Vector4 operator*(const float& other) const;
	// Division Operator
	Vector4 operator/(const float& other) const;

	// Sub Script Operator f = V[n]
	// Sub Script Operator Returning Reference V[n] = f
	float& operator[](int a_other);

	// Dot Product [f = V.dot(V)]
	float dot(const Vector4& other);
	// Cross Product [f = V.cross( V )]
	Vector4 cross(const Vector4& other);
	// Magnitude [f = V.magnitude()]
	float magnitude() const;
	// Normalize [f = V.nomalize()]
	void normalise();
	// Cast Operator [float* fp = (float*)V]
	explicit operator float*();
};

static Vector4 operator*(const float a_fScale, const Vector4 & other)
{
	return other * a_fScale;
}