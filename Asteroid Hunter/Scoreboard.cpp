#include "Scoreboard.h"

std::string Scoreboard::scoreText = "'s Score: ";
int Scoreboard::Score = 0;


void Scoreboard::AddScore(int value) {
	Scoreboard::Score += value;
}

void Scoreboard::Render() {
	/*glRasterPos2f(10, windowHeight-25);
	for (int i = 0; i < scoreText.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoreText[i]);
	}*/
	std::string text = std::to_string(Scoreboard::Score);
	TextManager::ShowText(10, windowHeight - 25, scoreText + text);
	/*for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}*/

}

void Scoreboard::RenderPlayerScore(std::string playerName) {
	std::string text = std::to_string(Scoreboard::Score);
	TextManager::ShowText(10, windowHeight - 25, playerName + scoreText + text);
}

void Scoreboard::Update() {

}