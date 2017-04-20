#pragma once
#include "Lib.h"

class Sprite
{
public:
	virtual void SetTexture(GLuint textureBuffer);
protected:
	GLuint Texture;

};
