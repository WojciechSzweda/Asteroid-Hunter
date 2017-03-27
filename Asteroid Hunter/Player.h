#pragma once
#include "Lib.h"
#include "Vector2.h"
#include "Bullet.h"
#include "EngineEffect.h"
class Player : public IMovable
{
private:
	float turnDir = 0;
	bool turnBreak = false;
	float accDir = 0;
	bool accBreak = false;
	int turnBreakControl = 0;
	int accBreakControl = 0;

	Vector2 enginesPos[2];
	Vector2 engineEffectsSpawnPos[2];
	void CalculateDirection();
	void Break();
	void OffScreenControl();
	void StayInWindow();
	void EnginePosition();
	void RenderEngines();
	void SetEngineEffectSpawnPoints(float modelView[16]);
	void SetVerticesArray(float modelView[16]);
	void AddEngineEffects();
	void ManageEngineEffects();
public:
	//const float * color2 = new float[4]{ 0.0f, 1.0f, 0.0f, 0.0f };
	float color2[3] = { 1.0f,1.0f,1.0f };
	//GLfloat vertices[3][2];
	Vector2 vertices[3];
	float r;
	float x;
	float y;
	float xRot;
	float yRot;
	int Rot;
	float turningSpeed;
	float moveSpeed;
	Vector2 dir;
	std::vector<Bullet> bullets;
	std::vector<EngineEffect> engineEffects;

	Player(float r, float x, float y);
	~Player();

	void Render();
	void Update();
	void InputDOWN(int key);
	void InputUP(int key);
	void Input(unsigned char key);
	void Move();
	void Turn(float angle);
	void SetPosition(float x, float y);
	void Shoot();
	void PlayerHit();
	void ManageBullets();
};

