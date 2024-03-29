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

	// Top fan blade 
	glVertex3f(0.0, 0.0, -250.0);
	glVertex3f(50.0, 0.0, -250.0);
	glVertex3f(25.0, 50.0, -250.0);

	glVertex3f(0.0, 0.0, -250.0);
	glVertex3f(-50.0, 0.0, -250.0);
	glVertex3f(-25.0, 50.0, -250.0);

	
	glEnd(); 
}


void drawFish(float xpos, float ypos) {
	glColor3f(0.7, 0.9, 0.7); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(xpos, ypos, 0.0); 
	glScalef(75.0, 30.0, 25.0);
	glutWireOctahedron();
	glLoadIdentity();
	glBegin(GL_TRIANGLES);
	glVertex3f(xpos - 75, ypos, 0.0);
	glVertex3f(xpos - 100, ypos - 25, 0.0);
	glVertex3f(xpos - 100, ypos + 25, 0.0);
	glEnd();
}

void drawFood(float xpos, float ypos) {
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(xpos, ypos, 0.0);
	glutSolidSphere(10, 30, 30);
	glLoadIdentity();
}

void drawTank() {
	glColor3f(1.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -50.0);
	glutWireCube(250);
	glLoadIdentity();
}

void display_func(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 640.0 / 640.0, 400.0, 2000.0);
	gluLookAt(175, 320, 500, 0, 0, 0, 0, 1, 0); 
	drawFan();
	drawFish(xpos, ypos); 
	//drawFood(100, 100);
	drawTank();
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
	gluLookAt(175, 320, 500, 0, 0, 0, 0, 1, 0);
	glutMainLoop();
	return 0;
}