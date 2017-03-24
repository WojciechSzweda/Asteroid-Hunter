#pragma once
#include "Lib.h"
#include "Vector2.h"
class EngineEffect
{
private:
	void DestroyedStatus();
public:
	float x;
	float y;
	float decayScale;
	float size;
	bool destroyed = false;

	EngineEffect();
	EngineEffect(float x, float y);
	~EngineEffect();

	void Render();
	void Update();
	void Decay();
};

