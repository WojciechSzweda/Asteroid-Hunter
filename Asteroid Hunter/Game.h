#pragma once
#include "Lib.h"
#include "Asteroid.h"
#include "Player.h"
#include "Environment.h"
#include "Scoreboard.h"

class Game
{
	float screenShakeScaleX = 1.0f;
	float screenShakeScalyY = 1.0f;
	float screenShakeTimer = 0.0f;
	float screenShakeMulti = 1.0f;
	bool isScreenShaking = false;
	
	std::vector<Asteroid> asteroids;
	std::vector<Environment> environment;
	std::vector<Environment> particles;

	void KeyDown(int key);
	void PlayerCollision();
	void BulletCollision();
	void ManageAsteroids();
	void ManageParticles();
	void SpawnParticles(float x, float y, float size);
	void CheckForWin();
	void GameWon();
	void ScreenShakeTrigger(float multi);
	void ScreenShake();
	Asteroid NewAsteroid();
public:
	Player player;

	Game();
	~Game();
	void Setup();
	void Render();
	void Update();



};

