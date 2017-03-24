#pragma once
#include "Vector2.h"
#include "Lib.h"
#include "GlobalVariables.h"
#include "Scoreboard.h"
class Asteroid
{
private:
	int vertices;
	//std::vector<float> offsets;
	float Rot = 0;
	float* offsets;
	void FillOffsets();
	void SpawnPosition();
	void SetVelocity(float multi = 1);
	void StayInWindow();
	char pixels[256 * 256];
	GLuint texture;
	int x1, y1;
	void Texturing();
public:
	int HP;
	float x;
	float y;
	float r;
	Vector2 dir;
	float moveSpeed;
	bool destroyed = false;
	bool broken = false;
	Asteroid(float x, float y, float radius);
	Asteroid(float radius);
	//TODO: Copy constructor
	~Asteroid();
	void Render();
	void Move();
	void Update();
	void AsteroidHit();
	void DeleteArrays();
};

