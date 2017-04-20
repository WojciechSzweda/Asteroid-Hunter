#pragma once
#include "Lib.h"
class TextManager
{
private:

	Vector2 centrePos;
	float textWidth = 0;
	std::string prevText = "";
public:
	TextManager();
	TextManager(float x, float y);
	~TextManager();
	static int GetTextWidth(std::string text);
	void SetPosition(float x, float y);
	void ShowCentreText(std::string text);
	void ShowCentre8BitText(std::string text);
	static void ShowText(float x, float y, std::string text, bool center = false);
	static void Show8BitText(float x, float y, std::string text, bool center = false);
};

