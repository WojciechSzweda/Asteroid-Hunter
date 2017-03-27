#include "TextureLoader.h"

bool TextureLoader::LoadTexture(const char * filename, GLsizei & width, GLsizei & height, GLenum &type, GLenum &format, GLvoid *& pixels)
{
	pixels = NULL;
	width = 0;
	height = 0;

	FILE *tga = fopen(filename, "r");

	if (!tga)
		return false;

	unsigned char header[18];

	fread(header, 18, 1, tga);
	fseek(tga, header[0], SEEK_CUR);

	width = header[12] + (header[13] << 8);
	height = header[14] + (header[15] << 8);

	pixels = new unsigned char[width * height * 4];
	fread((void*)pixels, width * height * 4, 1, tga);
	type = GL_UNSIGNED_BYTE;
	format = GL_BGRA;

	fclose(tga);

	return true;

}
