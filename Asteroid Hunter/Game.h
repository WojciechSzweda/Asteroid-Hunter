#pragma once
#include "Lib.h"
#include "Asteroid.h"
#include "Player.h"
#include "Environment.h"
#include "Scoreboard.h"

class Game
{
public:
	Player player;
	
	std::vector<Asteroid> asteroids;
	std::vector<Environment> environment;
	std::vector<Environment> particles;

	Game();
	~Game();
	void Setup();
	void Render();
	void Update();
	Asteroid NewAsteroid();
	void KeyDown(int key);
	void PlayerCollision();
	void BulletCollision();
	void ManageAsteroids();
	void ManageParticles();
	void SpawnParticles(float x, float y, float size);
	void CheckForWin();
	void GameWon();
};

