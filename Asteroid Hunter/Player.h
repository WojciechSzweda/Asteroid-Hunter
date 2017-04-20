#pragma once
//#include "Lib.h"
//#include "Vector2.h"
#include "Bullet.h"
#include "EngineEffect.h"
#include "ShipWreck.h"

class Player : public GameObject, public Sprite
{
private:
	float turnDir = 0;
	bool turnBreak = false;
	bool accBreak = false;
	bool Accelerating = false;
	int turnBreakControl = 0;
	float SpeedLimit;
	float Rot;
	float turningSpeed;
	bool Destroyed = false;
	const static int ShipWrecksCount = 4;
	Vector2 enginesPos[2];
	Vector2 engineEffectsSpawnPos[2];
	Vector2 CalculateDirection();

	GLuint shipWreckTextures[ShipWrecksCount];

	std::vector<ShipWreck> shipWrecks;

	void Break();
	void EnginePosition();
	void RenderEngines();
	void SetEngineEffectSpawnPoints(float modelView[16]);
	void SetVerticesArray(float modelView[16]);
	void AddEngineEffects();
	void ManageEngineEffects();
	void Accelerate();
	void ShipWrecking();
	void AccelerationHandler();
	void Turn(float angle);
	void Shoot();
	void ManageBullets();
public:
	Vector2 vertices[3];
	std::vector<Bullet> bullets;
	std::vector<EngineEffect> engineEffects;


	Player(float r, float x, float y);
	Player();
	~Player();

	void Render();
	void Update();
	void InputDOWN(int key);
	void InputUP(int key);
	void Input(unsigned char key);
	void SetPosition(float x, float y);
	void PlayerHit();
	void SetShipWrecksTexture(GLuint textureBuffer[]);
	void SetShipWrecksTexture(GLuint tex1, GLuint tex2, GLuint tex3, GLuint tex4);
};

