#include "Vector3.h"
#include <iostream>
#include <cmath>

//============================
// CONSTURCTOR
//============================
Vector3::Vector3()
{
	v3x = 0;
	v3y = 0;
	v3z = 0;
}

Vector3::Vector3(float a_v3x, float a_v3y, float a_v3z)
{
	v3x = a_v3x;
	v3y = a_v3y;
	v3z = a_v3z;
}

//============================
// FUNCTIONS - OVERLOADED OPERATORS
//============================

Vector3 Vector3::operator+(const Vector3 & other) const
{
	return Vector3(v3x + other.v3x, v3y + other.v3y, v3z + other.v3z);
}

Vector3 Vector3::operator-(const Vector3 & other) const
{
	return Vector3(v3x - other.v3x, v3y - other.v3y, v3z - other.v3z);
}

Vector3 Vector3::operator*(const float& other) const
{
	return Vector3(v3x * other, v3y * other, v3z * other);
}

Vector3 Vector3::operator/(const float& other) const
{
	return Vector3(v3x / other, v3y / other, v3z / other);
}

float& Vector3::operator[](int a_other)
{
	return data[a_other];
}

//============================
// FUNCTIONS - NORMAL FUNCTIONS
//============================

// Formula (Get the Dot Product)
// Current value of x * new value of x +, and so forth
float Vector3::dot(const Vector3 & dot_other)
{
	return v3x * dot_other.v3x + v3y * dot_other.v3y + v3z * dot_other.v3z;
}

// Formula (Get the Cross Product)
// 
Vector3 Vector3::cross(const Vector3 & cross_other)
{
	return Vector3((v3y * cross_other.v3z) - (v3z * cross_other.v3y),
				  ((v3z * cross_other.v3x) - (v3x * cross_other.v3z)),
				   (v3x * cross_other.v3y) - (v3y * cross_other.v3x));
}

// Formula (Get the Magnitude)
// 
float Vector3::magnitude() const
{
	return sqrt((v3x * v3x) + (v3y * v3y) + (v3z * v3z));
}

// Formula (Normalise)
// 
void Vector3::normalise()
{
	float mag = magnitude();
	if (mag != 0)
	{
		v3x /= mag;
		v3y /= mag;
		v3z /= mag;
	}
}

// Formula (Casting)
// 
Vector3::operator float*()
{
	return data;
}