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

	Texturing();
}


Asteroid::~Asteroid()
{
}

void Asteroid::FillOffsets() {
	for (int i = 0; i < vertices; i++)
	{
		offsets[i] = 2 *(((float)rand() / RAND_MAX) * r /6) - r/6;
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

void Asteroid::OffScreenControl()
{
	StayInWindow();
}

void Asteroid::Render() {
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glTranslatef(x, y, 0);
	glRotatef(Rot, 0.0f, 0.0f, 1.0f);
	glTranslatef(-x, -y, 0);

	glColor3fv(Colors::White);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);

	GLdouble degree = 2 * M_PI / vertices;;
	for (int i = 0; i < vertices; i++)
	{
		glVertex2f(x + (r + offsets[i])*cos(i*degree), y + (r + offsets[i])*sin(i*degree));
		glTexCoord2f(((r + offsets[i])*cos(i*degree))/(r+offsets[i]),((r + offsets[i])*sin(i*degree)) /(r + offsets[i]));
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);

	DrawOutline(degree);

	glPopMatrix();
}

void Asteroid::DrawOutline(float degree)
{
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < vertices; i++)
	{
		//glVertex2f(x + (r + offsets[i])*cos(i*degree), y + (r + offsets[i])*sin(i*degree));
	}

	glEnd();
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
	OffScreenControl();
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
	GLsizei width, height;
	GLenum format, type;
	GLvoid *pixels;

	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//TODO: texture namespace or texture loader

	const char* path = "Textures\\asteroid_small.tga";
	GLboolean error = TextureLoader::LoadTexture(path, width, height, type, format, pixels);

	if (error == GL_FALSE)
	{
		printf("Nieodnaleziono %s", path);
		//TODO: error handler
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, type, pixels);
	delete[](unsigned char*)pixels;

}

