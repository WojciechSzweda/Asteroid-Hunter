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

Vector2 Vector2::Add(Vector2 value1, Vector2 value2)
{
	return Vector2(value1.x + value2.x, value1.y + value2.y);
}

float Vector2::Magnitude()
{
	return sqrt(this->x * this->x + this->y * this->y);
}

Vector2 Vector2::operator+(const Vector2 & value)
{
	return Vector2(this->x + value.x, this->y + value.y);
}

Vector2 & Vector2::operator+=(const Vector2 & value)
{
	this->x += value.x;
	this->y += value.y;
	return *this;
}

Vector2 Vector2::operator*(const int & value)
{
	return Vector2(this->x * value, this->y * value);
}

Vector2 Vector2::operator*(const float & value)
{
	return Vector2(this->x * value, this->y * value);
}

Vector2 & Vector2::operator*=(const float & value)
{
	this->x *= value;
	this->y *= value;
	return *this;
}


