#pragma once
#include "GameObject.h"

class EngineEffect : public GameObject
{
private:
	Vector2 Direction;
	float DecayScale;

	void DestroyedStatus();
	void Decay();
public:
	bool destroyed = false;

	EngineEffect();
	EngineEffect(Vector2 position);
	~EngineEffect();

	void Render();
	void Update();
};

