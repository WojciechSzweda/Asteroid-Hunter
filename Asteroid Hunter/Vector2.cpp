#include "Vector2.h"


Vector2::Vector2() {

}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}


Vector2::~Vector2()
{
}


Vector2 Vector2::Normalize(Vector2 value)
{
	double val = 1.0f / (double)sqrt((value.x * value.x) + (value.y * value.y));
	value.x *= val;
	value.y *= val;
	return value;
}

float Vector2::Distance(Vector2 value1, Vector2 value2)
{
	return (float)sqrt(pow(value1.x - value2.x, 2) + pow(value1.y - value2.y, 2));
}