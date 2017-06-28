#include "Vector2.h"
#include <iostream>
#include <cmath>

//============================
// CONSTURCTOR
//============================
Vector2::Vector2()
{
	v2x = 0;
	v2y = 0;
}

Vector2::Vector2(float a_v2x, float a_v2y)
{
	v2x = a_v2x;
	v2y = a_v2y;
}

//============================
// FUNCTIONS - OVERLOADED OPERATORS
//============================

Vector2 Vector2::operator+(const Vector2 & other) const
{
	return Vector2(v2x + other.v2x, v2y + other.v2y);
}

Vector2 Vector2::operator-(const Vector2 & other) const
{
	return Vector2(v2x - other.v2x, v2y - other.v2y);
}

Vector2 Vector2::operator*(const float& other) const
{
	return Vector2(v2x * other, v2y * other);
}

Vector2 Vector2::operator/(const float& other) const
{
	return Vector2(v2x / other, v2y / other);
}

float& Vector2::operator[](int a_other)
{
	return data[a_other];
}

//============================
// FUNCTIONS - NORMAL FUNCTIONS
//============================

// Formula (Get the Dot Product)
// Current value of x * new value of x +, and so forth
float Vector2::dot(const Vector2 & dot_other)
{
	return v2x * dot_other.v2x + v2y * dot_other.v2y;
}

// Formula (Get the Magnitude)
// 
float Vector2::magnitude() const
{
	return sqrt((v2x * v2x) + (v2y * v2y));
}

// Formula (Normalise)
// 
void Vector2::normalise()
{
	float mag = magnitude();
	if (mag != 0)
	{
		v2x /= mag;
		v2y /= mag;
	}
}

// Formula (Casting)
// 
Vector2::operator float*()
{
	return data;
}

// Linear Interpolation
// 
float Vector2::linearInterpolation(float i2a, float i2b, float i2t)
{
	float result = i2a + (i2b - i2a)*i2t;

	return result;
}