#include "lib.h"
#include "globalvariables.h"
#include "player.h"
#include "Asteroid.h"
#include "Game.h"

//edit properties?
#pragma comment(lib, "winmm.lib")

//using namespace std;
std::vector<Asteroid> asteroids;
bool play = false;
Player player = Player::Player(0,0, 20);
//Asteroid asteroid = Asteroid::Asteroid(20);
Game game;
// Ustalenie stanu rendrowania  
void SetupRC(void) {
	game.Setup();
}

// Funkcja wywo�ywana w celu narysowania sceny
void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);


	game.Render();

	glutSwapBuffers();
}



void ChangeSize(GLsizei w, GLsizei h) {
	// Zabezpieczenie przed dzieleniem przez zero
	if (h == 0)
		h = 1;

	// Ustalenie wielko�ci widoku zgodnego z rozmiarami okna
	glViewport(0, 0, w, h);

	// Ustalenie uk�adu wsp�rz�dnych
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Keep the square square, this time, save calculated
	// width and height for later use
	/*if (w <= h)
	{
		windowHeight = 250.0f*h / w;
		windowWidth = 250.0f;
	}
	else
	{
		windowWidth = 250.0f*w / h;
		windowHeight = 250.0f;
	}*/

	// Ustanowienie przestrzeni ograniczaj�cej (lewo, prawo, d�, g�ra, blisko, daleko)
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

// G��wny punki wej�cia programu  
void main(int argc, char* argv[]) {
	

	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Asteroid Hunter");
	glutDisplayFunc(RenderScene);
	//glutSpecialFunc(Input);
	glutIgnoreKeyRepeat(true);
	glutKeyboardFunc(Input);
	glutSpecialFunc(KeyDown);
	glutSpecialUpFunc(KeyUp);
	//glutIgnoreKeyRepeat(false);

	//glutKeyboardUpFunc(KeyUp);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(16, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}

