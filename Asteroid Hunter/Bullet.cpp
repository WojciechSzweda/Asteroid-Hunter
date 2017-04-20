#include "Bullet.h"


Bullet::Bullet(Vector2 position, Vector2 dir)
{
	Position = position;
	Direction = dir;

	Speed = 12.0f;
	Radius = 5;
}


Bullet::~Bullet()
{
}

void Bullet::Render() {
	glPushMatrix();
	glPointSize(Radius);
	glColor3fv(Colors::White);
	glBegin(GL_POINTS);
	glVertex3f(Position.x, Position.y, 0);
	glEnd();
	glPopMatrix();
}



void Bullet::Update() {
	Move();
	OffScreenControl(false);
	
}
