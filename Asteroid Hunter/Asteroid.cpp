#include "Asteroid.h"
#include "GlobalVariables.h"


int asteroidScalar = 5;

Asteroid::Asteroid(float radius) : dir(0, 0)
{
	this->r = radius;
	this->moveSpeed = 2;
	this->vertices = 20;
	this->HP = (int)(radius - asteroidScalar) / asteroidScalar;
	offsets = new float[vertices];
	FillOffsets();
	SpawnPosition();
	SetVelocity();


	Texturing();
}

Asteroid::Asteroid(float x, float y, float radius) : dir(0, 0)
{
	this->x = x;
	this->y = y;
	this->r = radius;
	this->moveSpeed = 2;
	this->vertices = 20;
	this->HP = (int)(radius - asteroidScalar) / asteroidScalar;
	offsets = new float[vertices];
	FillOffsets();
	SetVelocity(2);
}


Asteroid::~Asteroid()
{
	//std::cout << "wtf?" << std::endl;
	//delete[] this->offsets;
}

void Asteroid::FillOffsets() {
	for (int i = 0; i < vertices; i++)
	{
		offsets[i] = 2 *(((float)rand() / RAND_MAX) * r /6) - r/6;
		//offsets.emplace_back(((float)rand() / RAND_MAX) * 5);
	}
}

void Asteroid::SpawnPosition() {
	float border = 100;
	do {
		this->x = rand() % (int)windowWidth;
		this->y = rand() % (int)windowHeight;
	} while (x > windowWidth / 2 - border && x < windowWidth / 2 + border && y > windowHeight/2 - border && y < windowHeight/2 + border);
}

void Asteroid::SetVelocity(float multi) {
	this->dir.x = multi * 2 * (float)rand() / RAND_MAX -1;
	this->dir.y = multi * 2 * (float)rand() / RAND_MAX -1;
}

void Asteroid::Render() {
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glTranslatef(x, y, 0);
	glRotatef(Rot, 0.0f, 0.0f, 1.0f);
	glTranslatef(-x, -y, 0);

	glColor3f(1.0f, 1.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	
	GLdouble degree = 2 * M_PI / vertices;
	for (int i = 0; i < vertices; i++)
	{
		//glTexCoord2f(i, i);
		glVertex2f(x + (r + offsets[i])*cos(i*degree), y + (r + offsets[i])*sin(i*degree));
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void Asteroid::Move() {
	this->x += dir.x * moveSpeed;
	this->y += dir.y * moveSpeed;
}

void Asteroid::StayInWindow() {
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

void Asteroid::Update() {
	Move();
	StayInWindow();
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

void Asteroid::Texturing() {

	// £adowanie tekstury
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Generate a name for the texture
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);


	for (y1 = 0; y1 < 256; y1++)
	{
		for (x1 = 0; x1 < 256; x1++)
			pixels[y1 * 256 + x1] = rand() % 256;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 256, 256, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glEnable(GL_TEXTURE_2D);
}