#include "Asteroid.h"
#include "GlobalVariables.h"


int asteroidScalar = 5;

Asteroid::Asteroid(float radius)
{
	this->Radius = radius;
	this->Speed = 10/radius * 4;
	this->vertices = 20;
	this->HP = (int)(radius - asteroidScalar) / asteroidScalar;
	offsets = new float[vertices];
	GenerateOffsets();
	SpawnPosition();
	SetRandomDirection();
}

Asteroid::Asteroid(Vector2 position, float radius) : Asteroid(radius)
{
	this->Position = position;
}


Asteroid::~Asteroid()
{
}

void Asteroid::GenerateOffsets() {
	for (int i = 0; i < vertices; i++)
	{
		offsets[i] = 2 *(((float)rand() / RAND_MAX) * Radius /6) - Radius/6;
	}
}

void Asteroid::SpawnPosition() {
	float border = 100;
	do {
		this->Position.x = (float)fmod(rand(), windowWidth);
		this->Position.y = (float)fmod(rand(), windowHeight);
	} while (Position.x > windowWidth / 2 - border && Position.x < windowWidth / 2 + border && Position.y > windowHeight/2 - border && Position.y < windowHeight/2 + border);
}


void Asteroid::Render() {
	glBindTexture(GL_TEXTURE_2D, Texture);
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glTranslatef(Position.x, Position.y, 0);
	glRotatef(Rot, 0.0f, 0.0f, 1.0f);
	glTranslatef(-Position.x, -Position.y, 0);

	glColor3fv(Colors::White);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);

	double degree = 2 * M_PI / vertices;;
	for (int i = 0; i < vertices; i++)
	{
		glVertex2f(Position.x + (Radius + offsets[i])*(GLfloat)cos(i*degree), Position.y + (Radius + offsets[i])*(GLfloat)sin(i*degree));
		glTexCoord2f(((Radius + offsets[i])*(GLfloat)cos(i*degree))/(Radius+offsets[i]),((Radius + offsets[i])*(GLfloat)sin(i*degree)) /(Radius + offsets[i]));
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);

	//DrawOutline(degree);

	glPopMatrix();
}

void Asteroid::DrawOutline(double degree)
{
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < vertices; i++)
	{
		glVertex2f(Position.x + (Radius + offsets[i])*(GLfloat)cos(i*degree), Position.y + (Radius + offsets[i])*(GLfloat)sin(i*degree));
	}

	glEnd();
}
void Asteroid::Update() {
	Move();
	OffScreenControl(true);
}

void Asteroid::AsteroidHit() {
	this->HP--;
	SoundManager::PlayHitSound();
	if (HP <= 0)
	{
		this->destroyed = true;
		Scoreboard::AddScore(300);
		return;
	}
	Scoreboard::AddScore(100);
	broken = true;
}

void Asteroid::DeleteArrays() {
	delete offsets;
}
