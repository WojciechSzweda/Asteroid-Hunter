#include "TGAloader.h"


#define TARGA_HEADER_SIZE 0x12
#define TARGA_UNCOMP_RGB_IMG 0x02
#define TARGA_UNCOMP_BW_IMG 0x03

GLuint loadTGA(const char *filename)
{
	GLuint textureBuffer;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// pocz¹tkowe wartości danych wyjściowych
	GLvoid *pixels = NULL;
	GLsizei width = 0;
	GLsizei height = 0;
	GLenum format;
	GLenum type;

	// otwarcie pliku do odczytu
	FILE *tga = fopen (filename,"r");

	// sprawdzenie poprawności otwarcia pliku
	if (!tga)
		return GL_FALSE;

	// tablica na nagłówek pliku TGA
	unsigned char header [TARGA_HEADER_SIZE];

	// odczyt nagłówka pliku
	fread (header,TARGA_HEADER_SIZE,1,tga);

	// ominięcie pola ImageID
	fseek (tga,header [0],SEEK_CUR);

	// szerokość obrazu
	width = header [12] + (header [13] << 8);

	// wysokość obrazu
	height = header [14] + (header [15] << 8);

	 //obraz w formacie BGR - 24 bity na piksel
	if (header [2] == TARGA_UNCOMP_RGB_IMG && header [16] == 24)
	{
		pixels = new unsigned char [width * height * 3];
		fread ((void*)pixels,width * height * 3,1,tga);
		format = GL_BGR;
		type = GL_UNSIGNED_BYTE;
	}
	else

		// obraz w formacie BGRA - 32 bity na piksel
		if (header [2] == TARGA_UNCOMP_RGB_IMG && header [16] == 32)
		{
			pixels = new unsigned char [width * height * 4];
			fread ((void*)pixels,width * height * 4,1,tga);
			format = GL_BGRA;
			type = GL_UNSIGNED_BYTE;
		}
		else

			// obraz w odcieniach szarości - 8 bitów na piksel
			if (header [2] == TARGA_UNCOMP_BW_IMG && header [16] == 8)
			{
				pixels = new unsigned char [width * height];
				fread ((void*)pixels,width * height,1,tga);
				format = GL_LUMINANCE;
				type = GL_UNSIGNED_BYTE;
			}
			else
				return GL_FALSE;

	// zamknięcie pliku
	fclose (tga);

	
	glGenTextures(1, &textureBuffer);

	glBindTexture(GL_TEXTURE_2D, textureBuffer);

	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, type, pixels);

	delete[](unsigned char*)pixels;

	// sukces
	return textureBuffer;
}
