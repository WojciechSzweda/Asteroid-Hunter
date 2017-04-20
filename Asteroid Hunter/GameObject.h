#pragma once
#include "Lib.h"
#include "GlobalVariables.h"
class GameObject
{
public:

	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void Move();
	Vector2 GetPosition();
	float GetRadius();
	bool isOffScreen = false;
	
protected:

	Vector2 Position;
	Vector2 Direction;
	Vector2 Acceleration;
	float Speed;
	float Radius;
	virtual void OffScreenControl(bool StayInWindow);
	virtual void AccelerationHandler();
	void SetDirection(float x, float y);
	void SetRandomDirection();
};

