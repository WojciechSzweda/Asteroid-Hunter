#include "Bullet.h"



Bullet::Bullet(float x, float y, Vector2 dir) :dir(0,0)
{
	this->x = x;
	this->y = y;
	this->dir = dir;
	speed = 15.0f;
}


Bullet::~Bullet()
{
}

void Bullet::Render() {
	glPushMatrix();
	glPointSize(5);
	glColor3fv(Colors::White);
	glBegin(GL_POINTS);
	glVertex3f(this->x, this->y, 0);
	glEnd();
	glPopMatrix();
}

void Bullet::OffScreenControl(){
	if (x > windowWidth || x < 0 || y < 0 || y > windowHeight)
	{
		isOffscreen = true;
	}
}

void Bullet::Move() {
	this->x += dir.x * speed;
	this->y += dir.y * speed;
 }

void Bullet::Update() {
	Move();
	OffScreenControl();
	
}
