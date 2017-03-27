#include "Scoreboard.h"

std::string Scoreboard::scoreText = "Score: ";
int Scoreboard::Score = 0;


void Scoreboard::AddScore(int value) {
	Scoreboard::Score += value;
}

void Scoreboard::Render() {
	glRasterPos2f(10, windowHeight-25);
	for (int i = 0; i < scoreText.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoreText[i]);
	}
	std::string text = std::to_string(Scoreboard::Score);
	for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
}

void Scoreboard::Update() {

}