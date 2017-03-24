#include "Environment.h"
#include <iostream>


Environment::Environment()
{
	//this->moveSpeed = (float)rand() / RAND_MAX * 1.5;
	this->size = rand() % 2 + 0.5;
	this->moveSpeed = size;
	//this->size = (float)rand() / RAND_MAX * 2 + 1;
	SpawnPosition();
	SetVelocity();
}

Environment::Environment(float x, float y, float size, float decayScale)
{
	this->size = size;
	this->moveSpeed = size;

	this->x = x;
	this->y = y;
	this->isParticle = true;
	this->decayScale = decayScale;
	SetVelocity();
}


Environment::~Environment()
{
}


void Environment::SpawnPosition() {
	this->x = rand() % (int)windowWidth;
	this->y = rand() % (int)windowHeight;
}

void Environment::SetVelocity() {
	this->dir.x = 2 * (float)rand() / RAND_MAX - 1;
	this->dir.y = 2 * (float)rand() / RAND_MAX - 1;
}

void Environment::Render() {
	glPushMatrix();
	glPointSize(this->size);
	glColor3fv(Colors::White);
	glBegin(GL_POINTS);
	glVertex3f(this->x, this->y, 1);
	glEnd();
	glPopMatrix();
}

void Environment::Move() {
	this->x += dir.x * moveSpeed;
	this->y += dir.y * moveSpeed;
}

void Environment::StayInWindow() {
	if (x > windowWidth)
	{
		x = 0;
	}
	else if (x < 0)
	{
		x = windowWidth;
	}
	else if (y > windowHeight)
	{
		y = 0;
	}
	else if (y < 0)
	{
		y = windowHeight;
	}
}

void Environment::Decay() {
	this->size *= decayScale;
}

void Environment::DestroyStatus() {
	if (size < 0.5)
		destroyed = true;
}

void Environment::Update() {
	Move();
	StayInWindow();
	DestroyStatus();

	if (isParticle)
		Decay();



}