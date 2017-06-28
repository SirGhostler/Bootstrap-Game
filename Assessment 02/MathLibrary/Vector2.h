#pragma once

class Vector2
{
public:

	// Data Union and Data Struct
	union
	{
		struct
		{
			float v2x;
			float v2y;
		};
		float data[2];

	};

	Vector2();
	Vector2(float v2x, float v2y);

	Vector2(const Vector2& other) = default;
	~Vector2() = default;

	// Equals Operator
	Vector2& operator=(const Vector2& other) = default;
	// Addition Operator
	Vector2 operator+(const Vector2& other) const;
	// Subtraction Operator
	Vector2 operator-(const Vector2& other) const;
	// Multiplication Operator [V = V x f (Vector Scale)]
	Vector2 operator*(const float& other) const;
	// Division Operator
	Vector2 operator/(const float& other) const;

	// Linear Interpolation
	float linearInterpolation(float i2a, float i2b, float i2t);
	
	// Sub Script Operator f = V[n]
	// Sub Script Operator Returning Reference V[n] = f
	float& operator[](int a_other);

	// Dot Product [f = V.dot(V)]
	float dot(const Vector2& other);
	// Magnitude [f = V.magnitude()]
	float magnitude() const;
	// Normalize [f = V.nomalize()]
	void normalise();
	// Cast Operator [float* fp = (float*)V]
	explicit operator float*();
};

static Vector2 operator*(const float a_fScale, const Vector2 & other)
{
	return other * a_fScale;
}