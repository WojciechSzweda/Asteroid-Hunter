#include "ShipWreck.h"



ShipWreck::ShipWreck()
{
}

ShipWreck::ShipWreck(Vector2 position, float r)
{
	Radius = r;
	Speed = rand() % 5 + 0.5f;
	this->rotationSpeed = rand() % 2 + 0.2f;
	Position = position;
	SetRandomDirection();
}


ShipWreck::~ShipWreck()
{
}


void ShipWreck::Render()
{
	glPushMatrix();
	glTranslatef(Position.x, Position.y, 0);
	glRotatef(Angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-Position.x, -Position.y, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor3fv(Colors::White);

	glEnable(GL_TEXTURE_2D);

	glBegin(GL_TRIANGLES);
	GLdouble degree = 2 * M_PI / 3;
	for (int i = 0; i < 3; i++)
	{
		float offset = 0;
		if (i == 0)
			offset = Radius / 2.5f;

		glVertex2f(Position.x + offset + Radius*(float)cos(i*degree), Position.y + Radius*(float)sin(i*degree));
		switch (i)
		{
		case 0:
			glTexCoord2f(1, 0.5f);
			break;
		case 1:
			glTexCoord2f(0, 1);
			break;
		case 2:
			glTexCoord2f(0, 0);
			break;
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void ShipWreck::Update()
{
	Angle += rotationSpeed;
	Move();
}
