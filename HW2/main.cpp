/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 *******************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#if __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = {0,1,4,1};
int windowWidth = 640, windowHeight = 480;
double yRot = 0;
int curProblem = 1; // TODO: change this number to try different examples

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };

void problem1() {
	// Teapots numbered in clockwise order.
    // Teapot 1, 5, 6, and 10
	glPushMatrix();
	glTranslatef(0.30f, 1.0f, 0.0f);
	glRotatef(75.0f, 0.0f, 0.0f, 1.0f);
	glutSolidTeapot(0.25);
	glRotatef(-75.0f, 0.0f, 0.0f, 1.0f);
	
	glTranslatef(-0.60f, 0.0f, 0.0f);
	glRotatef(105.0f, 0.0f, 0.0f, 1.0f);
	glutSolidTeapot(0.25);
	glRotatef(-105.0f, 0.0f, 0.0f, 1.0f);
	
	glTranslatef(0.0f, -2.0f, 0.0f);
	glRotatef(-105.0f, 0.0f, 0.0f, 1.0f);
	glutSolidTeapot(0.25);
	glRotatef(105.0f, 0.0f, 0.0f, 1.0f);

	glTranslatef(0.60f, 0.0f, 0.0f);
	glRotatef(-75.0f, 0.0f, 0.0f, 1.0f);
	glutSolidTeapot(0.25);
	glPopMatrix();

	// Teapot 2, 4, 7, and 9
	glPushMatrix();
	glTranslatef(0.75f, 0.6f, 0.0f);
	glRotatef(30.0f, 0.0f, 0.0f, 1.0f);
	glutSolidTeapot(0.25);
	glRotatef(-30.0f, 0.0f, 0.0f, 1.0f);

	glTranslatef(-1.50f, 0.0f, 0.0f);
	glRotatef(150.0f, 0.0f, 0.0f, 1.0f);
	glutSolidTeapot(0.25);
	glRotatef(-150.0f, 0.0f, 0.0f, 1.0f);

	glTranslatef(0.0f, -1.2f, 0.0f);
	glRotatef(-150.0f, 0.0f, 0.0f, 1.0f);
	glutSolidTeapot(0.25);
	glRotatef(150.0f, 0.0f, 0.0f, 1.0f);

	glTranslatef(1.5f, 0.0f, 0.0f);
	glRotatef(-30.0f, 0.0f, 0.0f, 1.0f);
	glutSolidTeapot(0.25);
	glPopMatrix();

	// Teapot 3 and 8
	glPushMatrix();
	glTranslatef(1.0f, 0.0f, 0.0f);
	glutSolidTeapot(0.25);

	glTranslatef(-2.0f, 0.0f, 0.0f);
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
	glutSolidTeapot(0.25);
	glPopMatrix();
}

void problem2() {
	// 15 cubes of increasing height.
	float height = 0.0f;
	float height_increase = 0.05f;

	// Start at the far left and slowly move to the right while
	// increasing the height of the cubes.
	// Works by drawing a cube at the bottom and then at the top and
	// then use other cubes to fill in the blank spaces.
	glPushMatrix();
	glTranslatef(-2.0f, 0.0f, 0.0f);
	for (int i = 1; i <= 15; i++) {
		height = height_increase * i;
		glTranslatef(0.25f, 0.0f, 0.0f);
		glutSolidCube(0.25);
		
		for (int j = 0; j < i; j++) {
			glTranslatef(0.0f, height_increase, 0.0f);
			glutSolidCube(0.25);
		}
		glutSolidCube(0.25);
		glTranslatef(0.0f, -height, 0.0f);
		
		height_increase += 0.001;
	}
	glPopMatrix();
}

void problem3() {
    // 6 rows of teapots.
	float height = 1.45f;
	float height_decrease = 0.55f;

	float width = 0.5f;

	// Create each row with the row number of teapots with an equal distance from each other.
	for (int i = 0; i < 6; i++) {
		glPushMatrix();		
		glTranslatef(-width * i, height, 0.0f);
		for (int j = 0; j <= i; j++) {
			glutSolidTeapot(0.25);
			glTranslatef(2 * width, 0.0f, 0.0f);
		}
		height -= height_decrease;
		glPopMatrix();
	}
}

void problem4() {
    // Draw a happy face with a party hat.
	glPushMatrix();
	// Draw a sphere for the head.
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.6, 10, 10);

	glPushMatrix();
	glPushMatrix();

	// Draw a triangle for the mouth.
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.2f, -0.05f, 0.6f);
	glVertex3f(0.0f, -0.2f, 0.6f);
	glVertex3f(0.2f, -0.05f, 0.6f);
	glEnd();
	
	glPopMatrix();
	// Draw two spheres for the eyes.
	glTranslatef(-0.2f, 0.15f, 0.35f);
	glutSolidSphere(0.2, 10, 10);

	glTranslatef(0.4f, 0.0f, 0.0f);
	glutSolidSphere(0.2, 10, 10);
	glPopMatrix();
	
	// Draw a cone for the hat.
	glTranslatef(0.0f, 0.275f, -0.2f);
	glRotatef(-180.0f, 0.0f, 1.0f, 1.0f);
	glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.5, 1.5, 10, 10);

	glPopMatrix();
}

void display() {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
		glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(1,0,0); // x axis
		glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,1,0); // y axis
		glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,1); // z axis
	glEnd(/*GL_LINES*/);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,windowWidth,windowHeight);

	float ratio = (float)windowWidth / (float)windowHeight;
	gluPerspective(50, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

	glRotatef(yRot,0,1,0);

	if (curProblem == 1) problem1();
	if (curProblem == 2) problem2();
	if (curProblem == 3) problem3();
	if (curProblem == 4) problem4();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

	lastPos[0] = x;
	lastPos[1] = y;
}

void mouseMoved(int x, int y) {
	if (leftDown) yRot += (x - lastPos[0])*.1;
	if (rightDown) {
		for (int i = 0; i < 3; i++)
			cameraPos[i] *= pow(1.1,(y-lastPos[1])*.1);
	}


	lastPos[0] = x;
	lastPos[1] = y;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	curProblem = key-'0';
    if (key == 'q' || key == 'Q' || key == 27){
        exit(0);
    }
	glutPostRedisplay();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("HW2");

	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
