#include "EngineEffect.h"



EngineEffect::EngineEffect()
{
}

EngineEffect::EngineEffect(Vector2 position) {
	Position = position;
	DecayScale = 0.7f;
	Radius = 5.0f;
}


EngineEffect::~EngineEffect()
{
}

void EngineEffect::Render() {
	glPushMatrix();
	glPointSize(Radius);
	glColor3fv(Colors::White);
	glBegin(GL_POINTS);
	glVertex3f(Position.x, Position.y, 0);
	glEnd();
	glPopMatrix();
}

void EngineEffect::Update() {
	Decay();
	DestroyedStatus();
}

void EngineEffect::Decay() {
	this->Radius *= DecayScale;
}


void EngineEffect::DestroyedStatus() {
	if (Radius < 0.5)
		destroyed = true;
}