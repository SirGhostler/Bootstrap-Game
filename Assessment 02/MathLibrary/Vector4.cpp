#include "Vector4.h"
#include <iostream>
#include <cmath>

//============================
// CONSTURCTOR
//============================
Vector4::Vector4()
{
	v4x = 0;
	v4y = 0;
	v4z = 0;
	v4w = 0;
}

Vector4::Vector4(float a_v4x, float a_v4y, float a_v4z, float a_v4w)
{
	v4x = a_v4x;
	v4y = a_v4y;
	v4z = a_v4z;
	v4w = a_v4w;
}

//============================
// FUNCTIONS - OVERLOADED OPERATORS
//============================

Vector4 Vector4::operator+(const Vector4 & other) const
{
	return Vector4(v4x + other.v4x, v4y + other.v4y, v4z + other.v4z, v4w + other.v4w);
}

Vector4 Vector4::operator-(const Vector4 & other) const
{
	return Vector4(v4x - other.v4x, v4y - other.v4y, v4z - other.v4z, v4w - other.v4w);
}

Vector4 Vector4::operator*(const float& other) const
{
	return Vector4(v4x * other, v4y * other, v4z * other, v4w * other);
}

Vector4 Vector4::operator/(const float& other) const
{
	return Vector4(v4x / other, v4y / other, v4z / other, v4w / other);
}

float& Vector4::operator[](int a_other)
{
	return data[a_other];
}

//============================
// FUNCTIONS - NORMAL FUNCTIONS
//============================

// Formula (Get the Dot Product)
// Current value of x * new value of x +, and so forth
float Vector4::dot(const Vector4 & dot_other)
{
	return v4x * dot_other.v4x + v4y * dot_other.v4y + v4z * dot_other.v4z + v4w * dot_other.v4w;
}

// Formula (Get the Cross Product)
// 
Vector4 Vector4::cross(const Vector4 & cross_other)
{
	return Vector4((v4y * cross_other.v4z) - (v4z * cross_other.v4y),
		((v4z * cross_other.v4x) - (v4x * cross_other.v4z)),
		(v4x * cross_other.v4y) - (v4y * cross_other.v4x), v4w);
}

// Formula (Get the Magnitude)
// 
float Vector4::magnitude() const
{
	return sqrt((v4x * v4x) + (v4y * v4y) + (v4z * v4z) + (v4w * v4w));
}

// Formula (Normalise)
// 
void Vector4::normalise()
{
	float mag = magnitude();
	if (mag != 0)
	{
		v4x /= mag;
		v4y /= mag;
		v4z /= mag;
		v4w /= mag;
	}
}

// Formula (Casting)
// 
Vector4::operator float*()
{
	return data;
}