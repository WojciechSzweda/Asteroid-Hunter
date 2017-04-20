#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
private:

public:
	Bullet(Vector2 position, Vector2 dir);
	~Bullet();

	void Update();
	void Render();

	bool hit = false;
	
};

