#pragma once

#include "Lib.h"
#define GL_BGRA					0x80E1

class TextureLoader
{
public:
	
	static bool LoadTexture(const char *filename, GLsizei &width, GLsizei &height, GLenum &type, GLenum &format, GLvoid *&pixels);
};

