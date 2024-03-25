// CS 445/545 Prog 3 for Colby McClure

// Requrired libraries for the program
#include <GL/glew.h>
#include <iostream>
#include <GL/freeglut.h> 
#include "OpenGL445Setup-jan24.h"
#include <cmath> 
using namespace std; 

// To compile and link the code: g++ mcclurePgm4.cpp -o mcclurePgm4.exe -Wall -lGL -lGLU -lglut -lGLEW 
// In case WSL can't run executable: export MESA_GL_VERSION_OVERRIDE=4.5

void display_func(void)
{
    glFlush();
}

// Set the canvas size to be 600 x 600 
#define canvas_Width 600
#define canvas_Height 600

// Name the canvas 
char canvas_Name[] = "Colby McClure Fishtank";

// This is my driver function 
int main(int argc, char ** argv) {

	// Initiate glut
	glutInit(&argc, argv);
	my_setup(canvas_Width, canvas_Height, canvas_Name);

	// Start the keyboard and display event handlers along with the main loop
	glutDisplayFunc(display_func);
	glutMainLoop();
	return 0;
}