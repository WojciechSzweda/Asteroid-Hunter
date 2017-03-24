#pragma once
#include "GlobalVariables.h"
#include "Vector2.h"
#include "Lib.h"
class Environment
{
private:
	Vector2 dir;
	float size;
	float moveSpeed;
	bool isParticle = false;
	float decayScale;
	void SpawnPosition();
	void StayInWindow();
	void Move();
	void Decay();
	void DestroyStatus();
public:

	float x;
	float y;
	bool destroyed = false;
	Environment();
	Environment(float x, float y, float size, float decayScale);
	~Environment();
	void SetVelocity();
	void Render();
	void Update();
};

