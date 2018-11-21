#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
float pi = 3.141592;

typedef struct Dot {
	int x = 0;
	int y = 0;
};

typedef struct Target {
	Dot dot;
	double Dgree;
	Target() {
		dot.x = rand() % 800;
		dot.y = rand() % 130 + 470;
		Dgree = rand() % 360;
	}
	void update() {
		dot.x++;
		if (dot.x >= 800)
			dot.x = 0;
		Dgree++;
		if (Dgree >= 360)
			Dgree = 0;
	}

	void draw() {
		glPushMatrix();
			glTranslatef(dot.x, dot.y, 0);
			glRotatef(Dgree, 0, 0, 1);
			glBegin(GL_LINE_LOOP);
				glVertex2f(0, 20);
				glVertex2f(20, -20);
				glVertex2f(-20, -20);
			glEnd();
		glPopMatrix();

	}

};

typedef struct Rect {
	Dot dot;
	double Dgree;
	Rect() {
		dot.x = rand() % 800;
		dot.y = rand() % 450;
		Dgree = 0;
	}
	void update() {
		dot.y++;
		if (dot.y >= 420)
			dot.y = 0;
	}

	void draw() {
		glPushMatrix();
		glTranslatef(dot.x, dot.y, 0);
		glRotatef(Dgree, 0, 0, 1);
		glBegin(GL_LINE_LOOP);
		glVertex2f(-30, -30);
		glVertex2f(-30, +30);
		glVertex2f(+30, +30);
		glVertex2f(+30, -30);
		glEnd();
		glPopMatrix();

	}

};

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);

void DoTimer(int value);

Target target[10] = {};
Rect rect[10] = {};

void main(int argc, char *argv[])
{
	//초기화함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Example");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(30, DoTimer, 1);
	glutMainLoop();

}

void DoTimer(int value)

{

	glutTimerFunc(30, DoTimer, 1);
	glutPostRedisplay();
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	for (int i = 0; i < 10; i++) {
		target[i].update();
		rect[i].update();
		target[i].draw();
		rect[i].draw();
	}
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -100, 100);
	glMatrixMode(GL_MODELVIEW);
}

GLvoid Keyboard(unsigned char key, int x, int y) {

	switch (key) {



	}
	glutPostRedisplay();


}

GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

	}



}

