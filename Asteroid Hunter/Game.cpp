#include "Game.h"
#include <iostream>

int asteroidsDensity = 10;
int environmentDensity = 100;
Game::Game() : centreText()
{
	player = Player(0, 0, 20);
	AsteroidBreakOutCount = 2;
}


Game::~Game()
{
}

Asteroid Game::NewAsteroid() {
	return Asteroid(rand() % 12 + 10.0f);
}


void Game::Setup() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	for (int i = 0; i < asteroidsDensity; i++)
	{
		asteroids.emplace_back(NewAsteroid());

	}
	for (int i = 0; i < environmentDensity; i++)
	{
		environment.emplace_back(Environment());
	}

	
	centreText.SetPosition(windowWidth / 2.0f, windowHeight / 2.0f);

	GenerateTextures();
}

void Game::GenerateTextures() {
	textures = new GLuint[2];
	glGenTextures(2, textures);

	textures[0] = loadTGA("Textures\\ship.tga");
	textures[1] = loadTGA("Textures\\asteroid_small.tga");
	AsteroidTexture = textures[1];
	GLuint* shipWreckTextures = new GLuint[4];
	glGenTextures(4, shipWreckTextures);

	shipWreckTextures[0] = loadTGA("Textures\\shipwreck\\shipwreck1.tga");
	shipWreckTextures[1] = loadTGA("Textures\\shipwreck\\shipwreck2.tga");
	shipWreckTextures[2] = loadTGA("Textures\\shipwreck\\shipwreck3.tga");
	shipWreckTextures[3] = loadTGA("Textures\\shipwreck\\shipwreck4.tga");


	player.SetTexture(textures[0]);
	//player.SetShipWrecksTexture(shipWreckTextures);
	player.SetShipWrecksTexture(shipWreckTextures[0], shipWreckTextures[1], shipWreckTextures[2], shipWreckTextures[3]);
	delete shipWreckTextures;

	for (auto & asteroid : asteroids) asteroid.SetTexture(AsteroidTexture);
	delete textures;
}

void Game::Render() {
	if (currentState == Playing)
	{
		glPushMatrix();
		glTranslatef(screenShakeScaleX, screenShakeScalyY, 0);

		player.Render();

		for (auto & env : environment) env.Render();

		for (auto & asteroid : asteroids) asteroid.Render();
		for (auto & particle : particles) particle.Render();
		Scoreboard::RenderPlayerScore(inputText);
		glPopMatrix();
	}
	else if (currentState == TypeName)
	{
		TextManager::Show8BitText(windowWidth / 2.0f, windowHeight / 2.0f + 30, "Type your nickname:", true);
		centreText.ShowCentre8BitText(inputText);

	}
	//TextManager::ShowText(windowWidth / 3, windowHeight / 2, inputText);
}

void Game::Update() {
	if (currentState == Playing)
	{
		player.Update();
		for (auto & asteroid : asteroids) asteroid.Update();
		for (auto & env : environment) env.Update();
		for (auto & particle : particles) particle.Update();
		PlayerCollision();
		BulletCollision();
		ManageAsteroids();
		ManageParticles();
		CheckForWin();
		ScreenShake();
	}

}

void Game::Input(unsigned char key)
{
	if (currentState == TypeName)
	{
		if (key == 8 && inputText.size() > 0)
		{
			inputText.pop_back();
		}
		else if (key == 13)
		{
			currentState = Playing;
		}
		else
			inputText.push_back(key);
	}
}

void Game::ScreenShake() {
	if (isScreenShaking)
	{
		screenShakeScaleX = screenShakeMulti * sin(screenShakeTimer);
		screenShakeScalyY = screenShakeMulti * cos(screenShakeTimer);
		screenShakeTimer += 1.0f;
		//std::cout << screenShakeTimer << " " << screenShakeScaleX << std::endl;
		if (screenShakeTimer >= 20.0f)
		{
			isScreenShaking = false;
			screenShakeTimer = 0.0f;
		}
	}
}

void Game::KeyDown(int key) {

}

void Game::ScreenShakeTrigger(float multi) {
	isScreenShaking = true;
	screenShakeMulti = multi / 10;
}

void Game::PlayerCollision() {
	for (auto& asteroid : asteroids) {
		for (int i = 0; i < 3; i++)
		{
			float dis = Vector2::Distance(player.vertices[i], asteroid.GetPosition());
			if (dis <= asteroid.GetRadius())
			{
				player.PlayerHit();
			}
		}
		float dis = Vector2::Distance(player.GetPosition(), asteroid.GetPosition());
		dis += player.GetRadius() * 2 / 3;
		if (dis <= asteroid.GetRadius())
		{
			player.PlayerHit();
		}

	}
}

void Game::BulletCollision() {
	for (auto& asteroid : asteroids) {
		for (auto& bullet : player.bullets) {
			float dis = Vector2::Distance(bullet.GetPosition(), asteroid.GetPosition());
			if (dis <= asteroid.GetRadius()) {
				asteroid.AsteroidHit();
				bullet.hit = true;
				ScreenShakeTrigger(asteroid.GetRadius());
			}
		}
	}
}

void Game::ManageParticles() {
	for (std::vector<Environment>::size_type n = 0; n < particles.size();)
	{
		if (particles[n].destroyed)
		{
			particles.erase(particles.begin() + n);
		}
		else
			n++;
	}
}

void Game::ManageAsteroids() {


	for (std::vector<Asteroid>::size_type n = 0; n < asteroids.size();)
	{
		if (asteroids[n].destroyed)
		{
			SpawnParticles(asteroids[n].GetPosition(), asteroids[n].GetRadius() / 5);
			asteroids[n].DeleteArrays();
			asteroids.erase(asteroids.begin() + n);
		}
		else if (asteroids[n].broken)
		{
			SpawnParticles(asteroids[n].GetPosition(), asteroids[n].GetRadius() / 5);
			for (int i = 0; i < AsteroidBreakOutCount; i++)
			{
				auto newAsteroid = Asteroid(asteroids[n].GetPosition(), (asteroids[n].GetRadius() - asteroidScalar));
				newAsteroid.SetTexture(AsteroidTexture);
				asteroids.emplace_back(newAsteroid);
			}
			asteroids[n].DeleteArrays();
			asteroids.erase(asteroids.begin() + n);
		}
		else
			n++;
	}
}

void Game::SpawnParticles(Vector2 position, float size) {
	int quantity = (int)((rand() % 4 + 6) * size);
	for (int i = 0; i < quantity; i++)
	{
		float decayScale = 0.12f *((float)rand() / RAND_MAX) + 0.85f;
		particles.emplace_back(Environment(position, size, decayScale));
	}
}

void Game::CheckForWin() {
	if (asteroids.size() == 0) {
		GameWon();
	}
}

void Game::GameWon() {
	std::cout << "YOU WIN" << std::endl;
}
