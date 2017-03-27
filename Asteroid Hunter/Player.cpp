#include "Player.h"
#include "GlobalVariables.h"

int windowWidth = 800;
int windowHeight = 800;

Player::Player(float x, float y, float r) : dir(0, 0)
{
	SetPosition(windowWidth / 2, windowHeight / 2);
	this->r = r;
	this->turningSpeed = 5.0f;
	this->moveSpeed = 7.0f;
}


Player::~Player()
{
}

void Player::PlayerHit() {
	std::cout << "GAME OVER" << std::endl;
	SoundManager::PlayPlayerHitSound();
	system("pause");

	// TODO: ENDGAME
}

void Player::SetPosition(float x, float y) {
	this->x = x;
	this->y = y;
}
void Player::Render() {
	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(Rot, 0.0f, 0.0f, 1.0f);
	glTranslatef(-x, -y, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glColor3fv(Colors::White);

	float modelView[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelView);

	glBegin(GL_TRIANGLES);
	GLdouble degree = 2 * M_PI / 3;
	for (int i = 0; i < 3; i++)
	{
		float offset = 0;
		if (i == 0)
			offset = r / 2.5;

		vertices[i].x = x + offset + r*cos(i*degree);
		vertices[i].y = y + r*sin(i*degree);
		glVertex2f(vertices[i].x, vertices[i].y);
	}
	glEnd();

	RenderEngines();
	glPopMatrix();


	SetVerticesArray(modelView);
	SetEngineEffectSpawnPoints(modelView);

	for (auto & effect : engineEffects) effect.Render();
	for (auto & bullet : bullets) bullet.Render();
}

void Player::RenderEngines() {
	EnginePosition();
	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3fv(Colors::White);

	glVertex2f(enginesPos[0].x, enginesPos[0].y);
	glVertex2f(enginesPos[1].x, enginesPos[1].y);

	glEnd();
}

void Player::SetEngineEffectSpawnPoints(float modelView[16])
{
	float pointX = 0, pointY = 0, pointZ = 0, pointW = 0;

	for (int i = 0; i < 2; i++)
	{
		pointX = (enginesPos[i].x * modelView[0]) + (enginesPos[i].y * modelView[4]) + modelView[12];
		pointY = (enginesPos[i].x * modelView[1]) + (enginesPos[i].y * modelView[5]) + modelView[13];
		pointW = (enginesPos[i].x * modelView[3]) + (enginesPos[i].y * modelView[7]) + modelView[15];

		pointX /= pointW;
		pointY /= pointW;

		engineEffectsSpawnPos[i].x = pointX;
		engineEffectsSpawnPos[i].y = pointY;
	}
}

void Player::SetVerticesArray(float modelView[16])
{
	float pointX = 0, pointY = 0, pointZ = 0, pointW = 0;

	for (int i = 0; i < 3; i++)
	{

		pointX = (vertices[i].x * modelView[0]) + (vertices[i].y * modelView[4]) + (modelView[12]);
		pointY = (vertices[i].x * modelView[1]) + (vertices[i].y * modelView[5]) + (modelView[13]);
		pointW = (vertices[i].x * modelView[3]) + (vertices[i].y * modelView[7]) + (modelView[15]);

		pointX /= pointW;
		pointY /= pointW;

		vertices[i].x = pointX;
		vertices[i].y = pointY;

	}
}

void Player::EnginePosition() {
	for (int i = 0; i < 2; i++)
	{
		enginesPos[i].x = vertices[1].x - (vertices[1].x - vertices[2].x) / 3 * (i + 1);
		enginesPos[i].y = vertices[1].y - (vertices[1].y - vertices[2].y) / 3 * (i + 1);
	}
}

void Player::StayInWindow() {
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

void Player::Input(unsigned char key) {
	if (key == 46) // .
	{
		Shoot();
	}
}

void Player::InputDOWN(int key) {

	if (key == GLUT_KEY_RIGHT) {
		turnBreak = false;
		turnDir = -1;
		turnBreakControl++;
	}
	else if (key == GLUT_KEY_LEFT) {
	turnBreak = false;
	turnDir = 1;
	turnBreakControl++;
	}
	else if (key == GLUT_KEY_UP) {
		accBreak = false;
		accDir = 1;
		accBreakControl++;
	}
	else if (key == GLUT_KEY_DOWN) {
		accBreak = false;
		accDir = -0.5;
		accBreakControl++;
	}
}

void Player::InputUP(int key) {
	if (key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT) {
		if (turnBreakControl < 2)
		{
			turnBreak = true;
		}
		turnBreakControl--;
	}
	else if (key == GLUT_KEY_DOWN || key == GLUT_KEY_UP) {
		if (accBreakControl < 2)
		{
			accBreak = true;
		}
		accBreakControl--;
	}
}

void Player::Shoot() {
	SoundManager::PlayGunShotSound();
	bullets.emplace_back(Bullet(this->x, this->y, this->dir));
}

void Player::CalculateDirection() {
	dir.x = cos((Rot * M_PI) / 180);
	dir.y = sin((Rot * M_PI) / 180);
}

void Player::AddEngineEffects() {
	for (int i = 0; i < 2; i++)
	{
		engineEffects.emplace_back(EngineEffect(engineEffectsSpawnPos[i].x, engineEffectsSpawnPos[i].y));
	}
}

void Player::Move()
{
	CalculateDirection();
	this->x += dir.x * moveSpeed * accDir;
	this->y += dir.y * moveSpeed * accDir;

	if(accDir > 0)
	AddEngineEffects();

}

void Player::Turn(float angle) {
	this->Rot += angle;
	this->Rot = Rot % 360;
}

void Player::Break() {
	if (turnBreak)
	{
		turnDir *= 0.6;
	}
	if (accBreak)
	{
		accDir *= 0.9;
	}
}

void Player::OffScreenControl()
{
	StayInWindow();
}

void Player::Update() {
	Turn(turningSpeed * turnDir);
	Break();
	Move();
	OffScreenControl();
	for (auto & bullet : bullets) bullet.Update();
	for (auto & effect : engineEffects) effect.Update();
	ManageBullets();
	ManageEngineEffects();
	//AddEngineEffects();


}

void Player::ManageBullets() {
	for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ) {
		if (it->isOffscreen)
		{
			it = bullets.erase(it);
		}
		else if (it->hit)
		{
			it = bullets.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Player::ManageEngineEffects() {
	for (std::vector<EngineEffect>::size_type n = 0; n < engineEffects.size();)
	{
		if (engineEffects[n].destroyed)
		{
			engineEffects.erase(engineEffects.begin() + n);
		}
		else
			n++;
	}
}