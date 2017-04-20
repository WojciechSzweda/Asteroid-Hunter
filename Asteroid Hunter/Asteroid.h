#pragma once
//#include "Vector2.h"
#include "GameObject.h"
#include "GlobalVariables.h"
#include "Scoreboard.h"

class Asteroid : public GameObject, public Sprite
{
private:
	int vertices;
	float Rot = 0;
	float* offsets;

	void GenerateOffsets();
	void SpawnPosition();
	void DrawOutline(double degree);
public:
	int HP;
	bool destroyed = false;
	bool broken = false;
	Asteroid(Vector2 position, float radius);
	Asteroid(float radius);
	~Asteroid();
	void Render();
	void Update();
	void AsteroidHit();
	void DeleteArrays();
};

