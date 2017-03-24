#include "EngineEffect.h"



EngineEffect::EngineEffect()
{
}

EngineEffect::EngineEffect(float x, float y) {
	this->x = x;
	this->y = y;
	this->decayScale = 0.7f;
	this->size = 5.0f;
}


EngineEffect::~EngineEffect()
{
}

void EngineEffect::Render() {
	glPushMatrix();
	/*glTranslatef(x, y, 0);
	glRotatef(rot, 0.0f, 0.0f, 1.0f);
	glTranslatef(-x, -y, 0);*/
	glPointSize(size);
	glColor3fv(Colors::White);
	glBegin(GL_POINTS);
	glVertex3f(this->x, this->y, 0);
	glEnd();
	glPopMatrix();
}

void EngineEffect::Update() {
	Decay();
	DestroyedStatus();
}

void EngineEffect::Decay() {
	this->size *= decayScale;
}


void EngineEffect::DestroyedStatus() {
	if (size < 0.5)
		destroyed = true;
}