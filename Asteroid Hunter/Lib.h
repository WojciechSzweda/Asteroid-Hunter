#pragma once
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define _USE_MATH_DEFINES
#include "math.h"
#include <ctime>
#include <vector>
#include "Vector2.h"
#include "Colors.h"
#include "Sprite.h"
#include "SoundManager.h"
#include "TextManager.h"
#include "TGAloader.h"

#include <iostream>


#define GL_GENERATE_MIPMAP		0x8191

