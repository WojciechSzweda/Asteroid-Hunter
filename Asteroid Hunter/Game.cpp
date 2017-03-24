#include "Game.h"
#include <iostream>

int asteroidsDensity = 10;
int environmentDensity = 30;
Game::Game() : player(0, 0, 20)
{
}


Game::~Game()
{
}

Asteroid Game::NewAsteroid() {
	return Asteroid(rand() % 12 + 10);
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

}

void Game::Render() {
	player.Render();
	for (auto & env : environment) env.Render();
	for (auto & asteroid : asteroids) asteroid.Render();
	for (auto & particle : particles) particle.Render();
	Scoreboard::Render();
}

void Game::Update() {
	player.Update();
	for (auto & asteroid : asteroids) asteroid.Update();
	for (auto & env : environment) env.Update();
	for (auto & particle : particles) particle.Update();
	PlayerCollision();
	BulletCollision();
	ManageAsteroids();
	ManageParticles();
	CheckForWin();
}

void Game::KeyDown(int key) {

}

void Game::PlayerCollision() {
	for (auto& asteroid : asteroids) {
		for (int i = 0; i < 3; i++)
		{
			float dis = Vector2::Distance(player.vertices[i], Vector2(asteroid.x, asteroid.y));
			if (dis <= asteroid.r)
			{
				player.PlayerHit();
			}
		}
		float dis = Vector2::Distance(Vector2(player.x, player.y), Vector2(asteroid.x, asteroid.y));
		dis += player.r * 2 / 3;
		if (dis <= asteroid.r)
		{
			player.PlayerHit();
		}

	}
}

void Game::BulletCollision() {
	for (auto& asteroid : asteroids) {
		for (auto& bullet : player.bullets) {
			float dis = Vector2::Distance(Vector2(bullet.x, bullet.y), Vector2(asteroid.x, asteroid.y));
			if (dis <= asteroid.r) {
				asteroid.AsteroidHit();
				bullet.hit = true;
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
	//for (std::vector<Asteroid>::iterator it = asteroids.begin(); it != asteroids.end(); ) {
	//	if (it->destroyed)
	//	{
	//		it = asteroids.erase(it);
	//	}
	//	else if (it->broken)
	//	{
	//		/*asteroids.emplace_back(Asteroid(it->x, it->y, (it->r - asteroidScalar)));
	//		asteroids.emplace_back(Asteroid(it->x, it->y, (it->r - asteroidScalar)));*/
	//		it = asteroids.erase(it);
	//		return;
	//	}
	//	else
	//	{
	//		++it;
	//	}
	//}


	for (std::vector<Asteroid>::size_type n = 0; n < asteroids.size();)
	{
		if (asteroids[n].destroyed)
		{
			SpawnParticles(asteroids[n].x, asteroids[n].y, asteroids[n].r / 5);
			asteroids[n].DeleteArrays();
			asteroids.erase(asteroids.begin() + n);
		}
		else if (asteroids[n].broken)
		{
			SpawnParticles(asteroids[n].x, asteroids[n].y, asteroids[n].r/5);
			asteroids.emplace_back(Asteroid(asteroids[n].x, asteroids[n].y, (asteroids[n].r - asteroidScalar)));
			asteroids.emplace_back(Asteroid(asteroids[n].x, asteroids[n].y, (asteroids[n].r - asteroidScalar)));
			asteroids[n].DeleteArrays();
			asteroids.erase(asteroids.begin() + n);
		}
		else
			n++;
	}
}

void Game::SpawnParticles(float x, float y, float size) {
	int quantity = (rand() % 4 + 6) * size;
	for (int i = 0; i < quantity; i++)
	{
		float decayScale = 0.12 *((float)rand() / RAND_MAX) + 0.85;
		particles.emplace_back(Environment(x, y, size, decayScale));
	}
}

void Game::CheckForWin() {
	if (asteroids.size() == 0) {
		GameWon();
	}
}

void Game::GameWon() {

}
