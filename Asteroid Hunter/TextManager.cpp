#include "TextManager.h"



TextManager::TextManager()
{
}

TextManager::TextManager(float x, float y) : centrePos(x, y)
{
}

TextManager::~TextManager()
{
}

void TextManager::SetPosition(float x, float y)
{
	centrePos.x = x;
	centrePos.y = y;
}

int TextManager::GetTextWidth(std::string text)
{
	int width = 0;
	for (int i = 0; i < text.size(); i++)
	{
		width += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
	return width;
}



void TextManager::ShowCentreText(std::string text)
{

	glRasterPos2f(centrePos.x - textWidth / 2, centrePos.y);

	for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
		if (prevText != text)
		{
			textWidth = GetTextWidth(text);
		}
	}
	prevText = text;
}
void TextManager::ShowCentre8BitText(std::string text)
{
	int distortionScale = 3;
	for (int i = 0; i < distortionScale; i++)
	{

		auto offsetX = rand() % 6;
		auto offsetY = rand() % 6;

		glRasterPos2f(centrePos.x - (textWidth / 2) + offsetX, centrePos.y + offsetY);

		for (int i = 0; i < text.size(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
			if (prevText != text)
			{
				textWidth = GetTextWidth(text);
			}
		}
		prevText = text;
	}
}

void TextManager::ShowText(float x, float y, std::string text, bool center)
{
	if (center)
	{
		x -= GetTextWidth(text) / 2;
	}

	glRasterPos2f(x, y);

	for (int i = 0; i < text.size(); i++)
	{	
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
}


void TextManager::Show8BitText(float x, float y, std::string text, bool center)
{
	int distortionScale = 3;
	for (int i = 0; i < distortionScale; i++)
	{

		auto offsetX = rand() % 6;
		auto offsetY = rand() % 6;
		TextManager::ShowText(x + offsetX, y + offsetY, text, center);
	}
}
