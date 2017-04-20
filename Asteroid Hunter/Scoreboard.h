#pragma once
#include "Lib.h"
#include <string>
#include "GlobalVariables.h"

class Scoreboard
{
public:
	static std::string scoreText;
	static int Score;

	static void RenderPlayerScore(std::string playerName);
	static void Render();
	static void Update();
	static void AddScore(int value);

};

