#include "lib.h"
#include "globalvariables.h"
#include "player.h"
#include "Asteroid.h"
#include "Game.h"


#pragma comment(lib, "winmm.lib")

bool play = false;
Game game;

void Setup() {
	game.Setup();
}

void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT);

	game.Render();

	glutSwapBuffers();
}



void ChangeSize(GLsizei width, GLsizei height) {
	if (height == 0)
		height = 1;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	
	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void TimerFunction(int value) {
	if (play)
	{
		game.Update();
	}

	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}


void KeyDown(int key, int x, int y) {
	//std::cout << key << std::endl;
	game.player.InputDOWN(key);
}

void KeyUp(int key, int x, int y) {
	//std::cout << "key up" << std::endl;
	game.player.InputUP(key);
}

void Input(unsigned char key, int x, int y) {
	if (key == 13)
	{
		play = true;
	}
	else if (key == 27)
	{
		play = false;
	}
	game.player.Input(key);

}

void main(int argc, char* argv[]) {
	
	srand((unsigned int)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Asteroid Hunter");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);


	glutIgnoreKeyRepeat(true);
	glutKeyboardFunc(Input);
	glutSpecialFunc(KeyDown);
	glutSpecialUpFunc(KeyUp);

	glutTimerFunc(16, TimerFunction, 1);
	Setup();
	glutMainLoop();
}

