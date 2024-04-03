// CS 445/545 Prog 4 for Colby McClure

// Requrired libraries for the program
#include <GL/glew.h>
#include <iostream>
#include <GL/freeglut.h> 
#include "OpenGL445Setup-jan24.h"
#include <cmath> 
#include <ctime>
using namespace std; 

// To compile and link the code: g++ mcclurePgm4.cpp -o mcclurePgm4.exe -Wall -lGL -lGLU -lglut -lGLEW 
// In case WSL can't run executable: export MESA_GL_VERSION_OVERRIDE=4.5

int xpos = 0;
int ypos = 0;

int foodX = 0;
int foodY = 0;

int minRange = -100;
int maxRange = 100; 

int score = 0; 

int timer = 30; 

int feedTimer = 0;

float turn = 0;

bool spawnFood = false; 

bool foodEaten = false;

bool gameOver = false;

float euclidean(int x1, int y1, int x2, int y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void timerFunc(int val) {
	if(timer <= 0) {
		gameOver = true;
	} else {

		if(spawnFood == false) {
			if(feedTimer == 4) {
				foodX = rand() % (maxRange - minRange + 1) + minRange;
				foodY = rand() % (maxRange - minRange + 1) + minRange;
				feedTimer = 0; 
				spawnFood = true;
				foodEaten = false;
			}
		} else {
			if(feedTimer == 3) {
				spawnFood = false;
				foodEaten = false;
			}
		}

		timer--;
		feedTimer++;

		glutPostRedisplay();
		glutTimerFunc(1000, timerFunc, 0);
	}


}

void fanRotation(int val) {
	if(turn == 360) {
		turn = 0;
	}
	turn += 7;

	glutPostRedisplay();

	glutTimerFunc(25, fanRotation, 0);

}

void timerText() {
	char firstDigitChar;
	char secondDigitChar;
	int firstDigit;
	int secondDigit;
	int number;

	number = timer;
	secondDigit = number % 10;
	secondDigitChar = secondDigit + '0';

	number = number / 10;

	firstDigit = number;
	firstDigitChar = firstDigit + '0';

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(125, 225, -50);

	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'T');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'm');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ':');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, firstDigitChar);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, secondDigitChar);

}

void scoreText() {
	char firstDigitChar;
	char secondDigitChar;
	char thirdDigitChar;
	int firstDigit;
	int secondDigit;
	int thirdDigit;
	int number; 

	number = score;
	thirdDigit = number % 10;
	thirdDigitChar = thirdDigit + '0';

	number = number / 10;

	secondDigit = number % 10;
	secondDigitChar = secondDigit + '0';

	number = number / 10;

	firstDigit = number;
	firstDigitChar = firstDigit + '0';

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(-275, 200, -50);

	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'S');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'c');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ':');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, firstDigitChar);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, secondDigitChar);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, thirdDigitChar);

}

void feedingTime(int val) {
	spawnFood = true;
	foodEaten = false;
	foodX = rand() % (maxRange - minRange + 1) + minRange;
	foodY = rand() % (maxRange - minRange + 1) + minRange;
	glutPostRedisplay();
	glutTimerFunc(4000, feedingTime, 0);
}

void collisionDetection() {
	if(foodX && foodY != 0) {
		if(foodEaten == false) {
			if(euclidean(xpos, ypos, foodX, foodY) <= 50) {
				feedTimer = 3; 
				foodEaten = true;
				spawnFood = false;
				score += 10; 
				glutPostRedisplay();
			}
		}
	}

}

void keyboardInput(unsigned char key, int x, int y) {
	if (key == 'H') {
		if(xpos > -100) {
			xpos -= 10;
			glutPostRedisplay();
		}
		
	} else if (key == 'J') {
		if(xpos < 100) {
			xpos += 10;
			glutPostRedisplay();
		}
	} else if (key == 'U') {
		if(ypos < 100) {
			ypos += 10;
			glutPostRedisplay();
		}
	} else if (key == 'N') {
		if(ypos > -100) {
			ypos -= 10;
			glutPostRedisplay();
		}
	}
}

void drawFan() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	GLfloat ambient[] = {1.0, 0.0, 0.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, ambient);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(turn, 0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.0, -300.0);
	glVertex3f(35.0, 50.0, -300.0);
	glVertex3f(17.5, 50.0, -300.0);
	glEnd(); 

	for(int i = 1; i <= 6; i++) {
		glRotatef(60.0, 0.0, 0.0, 1.0);
		glBegin(GL_TRIANGLES);
		glVertex3f(0.0, 0.0, -300.0);
		glVertex3f(35.0, 50.0, -300.0);
		glVertex3f(17.5, 50.0, -300.0);
		glEnd();
	} 

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_COLOR_MATERIAL);
}


void drawFish(float xpos, float ypos) {
	glColor3f(0.7, 0.9, 0.7); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(xpos, ypos, -175.0); 
	glScalef(37.5, 15.0, 12.5);
	glutWireOctahedron();
	glLoadIdentity();
	glTranslatef(0, 0, -175.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(xpos - 37.5, ypos, 0.0);
	glVertex3f(xpos - 52.5, ypos - 10, 0.0);
	glVertex3f(xpos - 52.5, ypos + 10, 0.0);
	glEnd();
}

void drawFood(int xpos, int ypos) {
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(xpos, ypos, -175.0);
	glutSolidSphere(5, 30, 30);
	glLoadIdentity();
}

void drawTank() {
	glColor3f(1.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -175.0);
	glutWireCube(250);
	glLoadIdentity();
}

void display_func(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	drawFan();
	drawFish(xpos, ypos); 

	if (spawnFood == true && gameOver == false) {
		drawFood(foodX, foodY);
	}

	drawTank();
	scoreText();
	timerText();
    glutSwapBuffers();
	
}


// Set the canvas size to be 640 x 640
#define canvas_Width 640
#define canvas_Height 640

// Name the canvas 
char canvas_Name[] = "Colby McClure Fishtank";

// This is my driver function 
int main(int argc, char ** argv) {

	srand(static_cast<unsigned int>(std::time(nullptr)));

	// Initiate glut
	glutInit(&argc, argv);
	my_setup(canvas_Width, canvas_Height, canvas_Name);

	// Start the keyboard and display event handlers along with the main loop
	glutDisplayFunc(display_func);
	glutKeyboardFunc(keyboardInput);

	glutIdleFunc(collisionDetection);

	glutTimerFunc(25, fanRotation, 0);
	glutTimerFunc(1000, timerFunc, 0);
	glutMainLoop();
	return 0;
}