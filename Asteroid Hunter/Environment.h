#pragma once
#include "GameObject.h"

class Environment : public GameObject
{
private:
	//Vector2 Direction;
	float size;
	bool isParticle = false;
	float decayScale;
	void SpawnPosition();
	void Decay();
	void DestroyStatus();
public:
	bool destroyed = false;
	Environment();
	Environment(Vector2 position, float size, float decayScale);
	~Environment();
	void Render();
	void Update();
};

