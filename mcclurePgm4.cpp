// CS 445/545 Prog 4 for Colby McClure

// Requrired libraries for the program
#include <GL/glew.h>
#include <iostream>
#include <GL/freeglut.h> 
#include "OpenGL445Setup-jan24.h"
#include <cmath> 
using namespace std; 

// To compile and link the code: g++ mcclurePgm4.cpp -o mcclurePgm4.exe -Wall -lGL -lGLU -lglut -lGLEW 
// In case WSL can't run executable: export MESA_GL_VERSION_OVERRIDE=4.5

int xpos = 0;
int ypos = 0;

int minRange = -100;
int maxRange = 100; 

int turn = 0;

bool spawnFood = false; 

void fanRotation(int val) {
	if(turn == 360) {
		turn = 0;
	}
	turn += 10;

	glutTimerFunc(100, fanRotation, 0);

	glutPostRedisplay();
}

void collisionDetection() {

}

void keyboardInput(unsigned char key, int x, int y) {
	if (key == 'H') {
		xpos -= 10;
		glutPostRedisplay();
	} else if (key == 'J') {
		xpos += 10;
		glutPostRedisplay();
	} else if (key == 'U') {
		ypos += 10;
		glutPostRedisplay();
	} else if (key == 'N') {
		ypos -= 10;
		glutPostRedisplay();
	}
}

void drawFan() {
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_TRIANGLES);

	// Draw one fan 
	glVertex3f(0.0, 0.0, -300.0);
	glVertex3f(35.0, 50.0, -300.0);
	glVertex3f(17.5, 50.0, -300.0);
	glEnd(); 

	for(int i = 1; i <= 6; i++) {
		glRotatef(60.0 + turn, 0.0, 0.0, 1.0);
		glBegin(GL_TRIANGLES);
		glVertex3f(0.0, 0.0, -300.0);
		glVertex3f(35.0, 50.0, -300.0);
		glVertex3f(17.5, 50.0, -300.0);
		glEnd();
	} 
}


void drawFish(float xpos, float ypos) {
	glColor3f(0.7, 0.9, 0.7); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(xpos, ypos, 0.0); 
	glScalef(37.5, 15.0, 12.5);
	glutWireOctahedron();
	glLoadIdentity();
	glBegin(GL_TRIANGLES);
	glVertex3f(xpos - 37.5, ypos, 0.0);
	glVertex3f(xpos - 52.5, ypos - 10, 0.0);
	glVertex3f(xpos - 52.5, ypos + 10, 0.0);
	glEnd();
}

void drawFood(float xpos, float ypos) {
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(xpos, ypos, 0.0);
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
	int randomNumX = rand() % (maxRange - minRange + 1) + minRange;
	int randomNumY = rand() % (maxRange - minRange + 1) + minRange;

	cout << randomNumX << " " << randomNumY << endl;

	drawFan();
	drawFish(xpos, ypos); 

	if (spawnFood == true) {
		drawFood(randomNumX, randomNumY);
	}

	drawTank();
    //glutSwapBuffers();
	glFlush();
}


// Set the canvas size to be 640 x 640
#define canvas_Width 640
#define canvas_Height 640

// Name the canvas 
char canvas_Name[] = "Colby McClure Fishtank";

// This is my driver function 
int main(int argc, char ** argv) {

	// Initiate glut
	glutInit(&argc, argv);
	my_setup(canvas_Width, canvas_Height, canvas_Name);

	// Start the keyboard and display event handlers along with the main loop
	glutDisplayFunc(display_func);
	glutKeyboardFunc(keyboardInput);
	glutIdleFunc(collisionDetection);
	glutTimerFunc(100, fanRotation, 0);
	glutMainLoop();
	return 0;
}