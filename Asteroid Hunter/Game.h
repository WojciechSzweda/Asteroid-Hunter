#pragma once
#include "Lib.h"
#include "Asteroid.h"
#include "Player.h"
#include "Environment.h"
#include "Scoreboard.h"

class Game
{
	enum GameState
	{
		MainMenu,
		TypeName,
		Playing,
		GameOver
	};
	GameState currentState = Playing;
	float screenShakeScaleX = 1.0f;
	float screenShakeScalyY = 1.0f;
	float screenShakeTimer = 0.0f;
	float screenShakeMulti = 1.0f;
	bool isScreenShaking = false;
	std::string inputText = "";
	std::vector<Asteroid> asteroids;
	std::vector<Environment> environment;
	std::vector<Environment> particles;
	TextManager centreText;
	GLuint *textures;
	GLuint AsteroidTexture;
	int AsteroidBreakOutCount;
	void KeyDown(int key);
	void PlayerCollision();
	void BulletCollision();
	void ManageAsteroids();
	void ManageParticles();
	void SpawnParticles(Vector2 pos, float size);
	void CheckForWin();
	void GameWon();
	void ScreenShakeTrigger(float multi);
	void ScreenShake();
	void GenerateTextures();
	Asteroid NewAsteroid();
public:
	Player player;

	Game();
	~Game();
	void Setup();
	void Render();
	void Update();

	void Input(unsigned char key);


};

