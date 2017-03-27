#pragma once
#include "Vector2.h"
#include "Lib.h"
#include "GlobalVariables.h"
#include "Scoreboard.h"


class Asteroid : public IMovable
{
private:
	int vertices;
	//std::vector<float> offsets;
	float Rot = 0;
	float* offsets;
	GLuint texture;
	int x1, y1;
	//GLdouble degree = 2 * M_PI / vertices;;

	void FillOffsets();
	void SpawnPosition();
	void SetVelocity(float multi = 1);
	void OffScreenControl();
	void StayInWindow();
	void Texturing();
	void DrawOutline(float degree);
	void Move();
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
	~Asteroid();
	void Render();
	void Update();
	void AsteroidHit();
	void DeleteArrays();
	
};

