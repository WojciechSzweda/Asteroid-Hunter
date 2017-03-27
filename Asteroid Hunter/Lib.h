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
#include "Colors.h"
#include "IMovable.h"
#include "SoundManager.h"
#include "TextureLoader.h"

#include <iostream>


#define GL_GENERATE_MIPMAP		0x8191

