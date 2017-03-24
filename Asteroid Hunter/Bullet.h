#pragma once
#include "Vector2.h"
#include "GlobalVariables.h"
#include "Lib.h"
class Bullet
{
public:
	float x;
	float y;
	float speed;
	Vector2 dir;
	Bullet(float x, float y, Vector2 dir);
	~Bullet();
	void Move();
	void Update();
	void OffScreenControl();
	bool isOffscreen();
	void Render();

	bool hit = false;
	
};
