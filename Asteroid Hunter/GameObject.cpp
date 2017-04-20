#include "GameObject.h"

void GameObject::Move()
{
	AccelerationHandler();
	Position += Acceleration;
}

Vector2 GameObject::GetPosition()
{
	return Position;
}

float GameObject::GetRadius()
{
	return Radius;
}

void GameObject::OffScreenControl(bool StayInWindow)
{

	if (StayInWindow)
	{
		if (Position.x > windowWidth)
		{
			Position.x = 0;
		}
		else if (Position.x < 0)
		{
			Position.x = (float)windowWidth;
		}
		else if (Position.y > windowHeight)
		{
			Position.y = 0;
		}
		else if (Position.y < 0)
		{
			Position.y = (float)windowHeight;
		}
	}
	else
	{
		if (Position.x > windowWidth || Position.x < 0 || Position.y < 0 || Position.y > windowHeight)
		{
			isOffScreen = true;
		}
	}
}

void GameObject::AccelerationHandler()
{
	Acceleration = Direction * Speed;
}

void GameObject::SetDirection(float x, float y)
{
	Direction.x = x;
	Direction.y = y;
}

void GameObject::SetRandomDirection()
{
	Direction.x = 2 * (float)rand() / RAND_MAX - 1;
	Direction.y = 2 * (float)rand() / RAND_MAX - 1;
}
