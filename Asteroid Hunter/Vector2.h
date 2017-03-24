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
};

