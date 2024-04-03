// CS 445/545 Prog 4 for Colby McClure

// Requrired libraries for the program
#include <GL/glew.h>
#include <iostream>
#include <GL/freeglut.h> 
#include "OpenGL445Setup-jan24.h"
#include <cmath> 
#include <ctime>
using namespace std; 

/*****************************************************************************************

Author: Colby McClure
Program: CS 445 Program 4 
Date: 4/4/2024
Architecture Statement: as soon as the program starts, the timer will begin counting down
from 30 seconds using the global 'timer' variable. Besides the timer event handler that 
controls the fan rotation, the main timer event handler that handles not only the timer 
but food generation would be the 'timerFunc' event handler. As soon as the program 
starts, the timer gets decremented by 1 every second that passes. If the timer reaches 
zero, the food stops spawning and the game is essectially over. As previouly stated, this
timer event handler also handles the food generation. The food will spawn every 4 seconds 
and disappear after 3 seconds. The 'feedTimer' variable is used to keep track of the timer 
specifically for the food. Since my 'timerFunc' event handler is called every second, it 
makes sense to use that same timer to keep track of the food. The 'collisionDetection' 
idle event handler is used to check for collisions between the fish and the food using
the Euclidean heuristic. If the center of the fish is within 50 units of the center of the
food, then the food gets 'eaten', meaning that the 'foodEaten' boolean is set to true and 
the display function stops drawing it until the next food iteration. Also whenever a food 
gets eaten, the 'foodTimer' is set to 3 seconds so that the food can respawn after 1 more 
second. But the 'foodTimer' variable gets reset to 0 each time a food has spawned. So 
essentially, if a food gets eaten, the food timer gets set to 3 which is like going into 
the future by whatever amount it takes to reach 3. My 'keyboardInput' function serves as
my keyboard input event handler. Each time one of the directional keys is pressed, then 
the fish IMMEDIATELY moves in that direction by 10 units and the screen is redisplayed.
The 'drawFan' function is used to draw the fan blades. The first fan blade gets drawn then
I use glRotatef to rotate the fan blades by 60 degrees 5 more times to draw the remaining 
fan blades. And after much testing, I found that increasing the angle of the rotation by 7
every 25 milliseconds was the best speed for the fan bladees to make sure they do a full 
turn every two seconds smoothly. To spawn the food, I used the rand() function to generate
a random x and y position for the food to spawn that is within my range of -100 to 100.
Every time a new food gets created, the x and y position of the food gets set to a random
number that falls within the range of -100 to 100. I even seeded the random number in the 
main function to ensure that I don't get teh same random numbers every time I run the 
program. Both the score and timer text use the strategy of converting the integer values
to characters and then adding the ASCII value of '0' to each digit to get the correct 
character representation of the digit. Using the criteria provided, I placed my 
gluLookAt and gluPerspective calls in the header file since it only needs to be called
once. 

*****************************************************************************************/

// To compile and link the code: g++ mcclurePgm4.cpp -o mcclurePgm4.exe -Wall -lGL -lGLU -lglut -lGLEW 
// In case WSL can't run executable: export MESA_GL_VERSION_OVERRIDE=4.5


// Global variables for the program

// Fish position variables
int xpos = 0;
int ypos = 0;

// Food position variables
int foodX = 0;
int foodY = 0;

// Range for food to spawn
int minRange = -100;
int maxRange = 100; 

// Score and timer variables
int score = 0; 
int timer = 30; 

// Timer for food spawning
int feedTimer = 0;

// Turn variable for fan rotation
float turn = 0;

// Booleans for food spawning and eating as well as game state 
bool spawnFood = false; 
bool foodEaten = false;
bool gameOver = false;

/**************************************************************************************/

// This function calculates the distance between two points using the Euclidean heuristic 
float euclidean(int x1, int y1, int x2, int y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

/**************************************************************************************/

// Timer event handler for the game. This will not only serve as the timer for the game but also handle the spawning of food 
void timerFunc(int val) {

	// If the timer reaches 0, the game is over
	if(timer <= 0) {
		gameOver = true;
		glutPostRedisplay();

	} else {
		
		// If the food has not been spawned, spawn the food if the food timer is at 4
		if(spawnFood == false) {
			if(feedTimer == 4) {

				// Calulate the random position for the food to spawn 
				foodX = rand() % (maxRange - minRange + 1) + minRange;
				foodY = rand() % (maxRange - minRange + 1) + minRange;

				// Reset the feed timer and set game state variables
				feedTimer = 0; 
				spawnFood = true;
				foodEaten = false;
			}
		} else {

			// After 3 seconds, the food will disappear and the game state variables will be reset
			if(feedTimer == 3) {
				spawnFood = false;
				foodEaten = false;
			}
		}

		// Decrement the timer and increment the feed timer
		timer--;
		feedTimer++;

		glutPostRedisplay();
		glutTimerFunc(1000, timerFunc, 0);
	}
}

/**************************************************************************************/

// This timer event handler will rotate the fan blades
void fanRotation(int val) {

	// If the turn reaches 360, reset the turn to 0
	if(turn == 360) {
		turn = 0;
	}

	// Increment the turn by 7 degrees and redisplay the screen
	turn += 7;

	glutPostRedisplay();
	glutTimerFunc(25, fanRotation, 0);
}

/**************************************************************************************/

// This function will display the timer on the screen
void timerText() {

	// Variables for the first and second digit of the timer
	char firstDigitChar;
	char secondDigitChar;
	int firstDigit;
	int secondDigit;
	int number;

	// Calculate the first and second digit of the timer
	number = timer;
	secondDigit = number % 10;
	secondDigitChar = secondDigit + '0';

	number = number / 10;

	firstDigit = number;
	firstDigitChar = firstDigit + '0';

	// Set the modelview matrix and reload the identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set the color to white and position the text on the screen
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

/**************************************************************************************/

// This function will display the score on the screen
void scoreText() {

	// Variables for the first, second, and third digit of the score
	char firstDigitChar;
	char secondDigitChar;
	char thirdDigitChar;
	int firstDigit;
	int secondDigit;
	int thirdDigit;
	int number; 

	// Calculate the first, second, and third digit of the score
	number = score;
	thirdDigit = number % 10;
	thirdDigitChar = thirdDigit + '0';

	number = number / 10;

	secondDigit = number % 10;
	secondDigitChar = secondDigit + '0';

	number = number / 10;

	firstDigit = number;
	firstDigitChar = firstDigit + '0';

	// Set the modelview matrix and reload the identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set the color to white and position the text on the screen
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

/**************************************************************************************/

// This idle function handler will check for collisions between the fish and the food
void collisionDetection() {

	// If the food has not initially spawned
	if(foodX && foodY != 0) {

		// If the food has not been eaten, check for a collision between the fish and the food
		if(foodEaten == false) {

			// If the fish is within 50 units of the food, the food is eaten, score is incremented, and the feed timer is set to 3 
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

/**************************************************************************************/

// This is my keyboard input handler for the program
void keyboardInput(unsigned char key, int x, int y) {

	// If the key pressed is 'H', move the fish 'left' by 10 units
	if (key == 'H') {

		// Check if the fish is within the bounds of the tank
		if(xpos > -100) {
			xpos -= 10;
			glutPostRedisplay();
		}
	
	// If the key pressed is 'J', move the fish 'right' by 10 units
	} else if (key == 'J') {

		// Check if the fish is within the bounds of the tank
		if(xpos < 100) {
			xpos += 10;
			glutPostRedisplay();
		}
	
	// If the key pressed is 'U', move the fish 'up' by 10 units
	} else if (key == 'U') {

		// Check if the fish is within the bounds of the tank
		if(ypos < 100) {
			ypos += 10;
			glutPostRedisplay();
		}
	
	// If the key pressed is 'N', move the fish 'down' by 10 units
	} else if (key == 'N') {

		// Check if the fish is within the bounds of the tank
		if(ypos > -100) {
			ypos -= 10;
			glutPostRedisplay();
		}
	}
}

/**************************************************************************************/

// This function will draw the fan blades 
void drawFan() {

	// Enable lighting, light0, and color material
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	// Set the color material to the front and set the ambient light to red
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	GLfloat ambient[] = {1.0, 0.0, 0.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, ambient);

	// Set the color of the blades, set the matrix to modelview, and load the identity matrix
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Rotate the blades by the turn variable and draw the blades
	glRotatef(turn, 0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.0, -300.0);
	glVertex3f(35.0, 50.0, -300.0);
	glVertex3f(17.5, 50.0, -300.0);
	glEnd(); 

	// Using a for loop, draw the remaining 5 blades
	for(int i = 1; i <= 6; i++) {
		glRotatef(60.0, 0.0, 0.0, 1.0);
		glBegin(GL_TRIANGLES);
		glVertex3f(0.0, 0.0, -300.0);
		glVertex3f(35.0, 50.0, -300.0);
		glVertex3f(17.5, 50.0, -300.0);
		glEnd();
	} 

	// Disable lighting, light0, and color material
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_COLOR_MATERIAL);
}

/**************************************************************************************/

// This function will draw the fish given the x and y position
void drawFish(float xpos, float ypos) {

	// Set the color of the fish to green, set the matrix to modelview, and load the identity matrix
	glColor3f(0.7, 0.9, 0.7); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw the fish using the given x and y position while keeping the z position constant
	glTranslatef(xpos, ypos, -175.0); 

	// Scale the fish to the correct size then draw the fish
	glScalef(37.5, 15.0, 12.5);
	glutWireOctahedron();

	// Reload the identity matrix, translate the tail to the correct position, and draw the tail
	glLoadIdentity();
	glTranslatef(0, 0, -175.0);

	glBegin(GL_TRIANGLES);
	glVertex3f(xpos - 37.5, ypos, 0.0);
	glVertex3f(xpos - 52.5, ypos - 10, 0.0);
	glVertex3f(xpos - 52.5, ypos + 10, 0.0);
	glEnd();
}

/**************************************************************************************/

// This function will draw the food given the x and y position
void drawFood(int xpos, int ypos) {

	// Set the color of the food to white, set the matrix to modelview, and load the identity matrix
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw the food using the given x and y position while keeping the z position constant
	glTranslatef(xpos, ypos, -175.0);
	glutSolidSphere(5, 30, 30);
}

/**************************************************************************************/

// This function will draw the tank
void drawTank() {

	// Set the color of the tank to yellow, set the matrix to modelview, and load the identity matrix
	glColor3f(1.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw the tank using the given x and y position while keeping the z position constant
	glTranslatef(0, 0, -175.0);
	glutWireCube(250);
	glLoadIdentity();
}

/**************************************************************************************/

// This is my display function handler for the program
void display_func(void)
{
	// Set the clear color to black and clear the color buffer
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw the fan, fish, food, timer, score, and tank
	drawFan();
	drawFish(xpos, ypos); 

	// If the food has spawned and the game is not over, draw the food
	if (spawnFood == true && gameOver == false) {
		drawFood(foodX, foodY);
	}

	drawTank();
	scoreText();
	timerText();

	// Swap the buffers
    glutSwapBuffers();
}

/**************************************************************************************/

// Set the canvas size to be 640 x 640
#define canvas_Width 640
#define canvas_Height 640

// Name the canvas 
char canvas_Name[] = "Colby McClure Fishtank";

// This is my driver function 
int main(int argc, char ** argv) {

	// Seed the random number generator so that its truly random each program run
	srand(static_cast<unsigned int>(std::time(nullptr)));

	// Initiate glut
	glutInit(&argc, argv);
	my_setup(canvas_Width, canvas_Height, canvas_Name);

	// Start the keyboard, display, and idle function handlers 
	glutDisplayFunc(display_func);
	glutKeyboardFunc(keyboardInput);
	glutIdleFunc(collisionDetection);
	glutTimerFunc(25, fanRotation, 0);
	glutTimerFunc(1000, timerFunc, 0);
	glutMainLoop();
	return 0;
}