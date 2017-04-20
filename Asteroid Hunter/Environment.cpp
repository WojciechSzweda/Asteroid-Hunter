#include "Environment.h"


Environment::Environment()
{
	this->size = rand() % 2 + 0.5f;
	Speed = size;
	SpawnPosition();
	SetRandomDirection();
}

Environment::Environment(Vector2 position, float size, float decayScale)
{
	this->size = size;
	Speed = size;
	Position = position;
	this->isParticle = true;
	this->decayScale = decayScale;
	SetRandomDirection();
}


Environment::~Environment()
{
}


void Environment::SpawnPosition() {
	this->Position.x = fmod(rand(), windowWidth);
	this->Position.y = fmod(rand(), windowHeight);
}


void Environment::Render() {
	glPushMatrix();
	glPointSize(this->size);
	glColor3fv(Colors::White);
	glBegin(GL_POINTS);
	glVertex3f(Position.x, Position.y, 1);
	glEnd();
	glPopMatrix();
}


void Environment::Decay() {
	this->size *= decayScale;
}

void Environment::DestroyStatus() {
	if (size < 0.5)
		destroyed = true;
}

void Environment::Update() {
	AccelerationHandler();
	Move();
	OffScreenControl(true);
	DestroyStatus();

	if (isParticle)
		Decay();



}