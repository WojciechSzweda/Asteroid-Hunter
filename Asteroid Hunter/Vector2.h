#pragma once
#include <math.h>

class Vector2
{
public:
	float x;
	float y;
	Vector2();
	Vector2(float x, float y);
	~Vector2();

	static Vector2 Normalize(Vector2 value);
	static float Distance(Vector2 value1, Vector2 value2);
	static Vector2 Add(Vector2 value1, Vector2 value2);
	float Magnitude();
	Vector2 operator+(const Vector2& value);
	Vector2& operator+=(const Vector2& value);
	Vector2 operator*(const int& value);
	Vector2 operator*(const float& value);
	Vector2& operator*=(const float& value);
};


