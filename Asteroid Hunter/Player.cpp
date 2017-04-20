#include "Player.h"
#include "GlobalVariables.h"

int windowWidth = 800;
int windowHeight = 800;

Player::Player(float x, float y, float r)
{
	this->Radius = r;
	this->turningSpeed = 5.0f;
	this->Speed = 0.5f;
	this->Position = Vector2(x, y);
	SetPosition(windowWidth / 2.0f, windowHeight / 2.0f);
	this->Direction = Vector2(0, 0);
	this->Acceleration = Vector2(0, 0);
	SpeedLimit = 40.0f;
	Rot = 90;

}

Player::Player()
{
}


Player::~Player()
{
}

void Player::PlayerHit() {

	ShipWrecking();
	Destroyed = true;
	//TODO: Player disapear
	Position = Vector2(-100, -1000);
	std::cout << "GAME OVER" << std::endl;
	SoundManager::PlayPlayerHitSound();
	//system("pause");

	// TODO: ENDGAME
}

void Player::SetPosition(float x, float y) {
	Position.x = x;
	Position.y = y;
}

template <typename T> int sign(T val) {
	if (val < 0)
	{
		return -1;
	}
	else if (val > 0)
	{
		return 1;
	}
	return 0;
}

void Player::Render() {
	glBindTexture(GL_TEXTURE_2D, Texture);

	glPushMatrix();
	glTranslatef(Position.x, Position.y, 0);
	glRotatef(Rot, 0.0f, 0.0f, 1.0f);
	glTranslatef(-Position.x, -Position.y, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor3fv(Colors::White);

	float modelView[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelView);
	glEnable(GL_TEXTURE_2D);

	//glBindTexture(GL_TEXTURE_2D, Texture);
	glBegin(GL_TRIANGLES);
	GLdouble degree = 2 * M_PI / 3;
	for (int i = 0; i < 3; i++)
	{
		float offset = 0;
		if (i == 0)
			offset = Radius / 2.5f;

		vertices[i].x = Position.x + offset + Radius*(float)cos(i*degree);
		vertices[i].y = Position.y + Radius*(float)sin(i*degree);
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
		//glTexCoord2f(sign(cos(i*degree)), sign(sin(i*degree)));
		glVertex2f(vertices[i].x, vertices[i].y);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);

	RenderEngines();
	glPopMatrix();


	SetVerticesArray(modelView);
	SetEngineEffectSpawnPoints(modelView);

	for (auto & effect : engineEffects) effect.Render();
	for (auto & bullet : bullets) bullet.Render();
	/*for (int i = 0; i < ShipWrecksCount; i++)
	{
		glBindTexture(GL_TEXTURE_2D, shipWreckTextures[i]);
		shipWrecks[i].Render();
	}*/
	int index = 0;
	for (auto & wreck : shipWrecks) {
		glBindTexture(GL_TEXTURE_2D, shipWreckTextures[index]);
		index++;
		wreck.Render();
	}
}

void Player::ShipWrecking()
{
	for (int i = 0; i < ShipWrecksCount; i++)
		shipWrecks.emplace_back(ShipWreck(Position, Radius));
}

#pragma region EnginesStuff
void Player::RenderEngines() {
	EnginePosition();
	glPointSize(3);
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

void Player::EnginePosition() {
	for (int i = 0; i < 2; i++)
	{
		enginesPos[i].x = vertices[1].x - (vertices[1].x - vertices[2].x) / 3 * (i + 1);
		enginesPos[i].y = vertices[1].y - (vertices[1].y - vertices[2].y) / 3 * (i + 1);
	}
}

void Player::AddEngineEffects() {
	for (int i = 0; i < 2; i++)
	{
		engineEffects.emplace_back(EngineEffect(engineEffectsSpawnPos[i]));
	}
}

#pragma endregion

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
		Accelerating = true;

		/*accBreak = false;
		accDir = 1;
		accBreakControl++;*/
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
	else if (key == GLUT_KEY_UP) {
		Accelerating = false;

		/*if (accBreakControl < 2)
		{
			accBreak = true;
		}
		accBreakControl--;*/
	}
}

void Player::Shoot() {
	SoundManager::PlayGunShotSound();
	bullets.emplace_back(Bullet(Position, Direction));
}

Vector2 Player::CalculateDirection() {
	Direction.x = (float)cos((Rot * M_PI) / 180.0f);
	Direction.y = (float)sin((Rot * M_PI) / 180.0f);
	return Direction;
}

void Player::Accelerate()
{
	Acceleration += Direction * Speed;
}

void Player::AccelerationHandler() {
	if (Accelerating && Acceleration.Magnitude() < SpeedLimit)
	{
		Accelerate();
	}
	else
	{
		Acceleration *= 0.99f;
	}

	if (Accelerating)
		AddEngineEffects();
}


void Player::Turn(float angle) {
	this->Rot += angle;
	//this->Rot = Rot % 360;
	this->Rot = (float)fmod(Rot, 360);
}

void Player::Break() {
	if (turnBreak)
	{
		turnDir *= 0.6f;
	}
}


void Player::Update() {
	if (!Destroyed) {


	Turn(turningSpeed * turnDir);
	Break();
	CalculateDirection();
	Move();
	OffScreenControl(true);
	ManageBullets();
	ManageEngineEffects();
	for (auto & bullet : bullets) bullet.Update();
	for (auto & effect : engineEffects) effect.Update();
	}
	for (auto & wreck : shipWrecks) wreck.Update();
}

void Player::ManageBullets() {
	for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ) {
		if (it->isOffScreen)
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


void Player::SetShipWrecksTexture(GLuint textureBuffer[])
{
	for (int i = 0; i < ShipWrecksCount; i++)
	{
		shipWreckTextures[i] = textureBuffer[i];
	}
}

void Player::SetShipWrecksTexture(GLuint tex1, GLuint tex2, GLuint tex3, GLuint tex4)
{
	shipWreckTextures[0] = tex1;
	shipWreckTextures[1] = tex2;
	shipWreckTextures[2] = tex3;
	shipWreckTextures[3] = tex4;
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

