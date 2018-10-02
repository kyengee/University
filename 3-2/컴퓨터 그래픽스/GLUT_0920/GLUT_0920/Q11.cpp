#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef struct dot {
	float x, y;
	float size = 5;
	int sizetemp = +1;
	float degree = 0;
	int type = 0;
	int degreetemp = 5;
	float r = 0, g = 0, b = 0;
}Dot;

float pi = 3.141592;
Dot DotList[10];
int DotCount = 0;
int DotLength = 0;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid TimerFunction(int value);

void main(int argc, char *argv[])
{
	//초기화함수들
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Example");
	glutDisplayFunc(drawScene);
	glutMouseFunc(Mouse);
	glutTimerFunc(50, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();

}



GLvoid TimerFunction(int value) {
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}


GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		DotLength++;
		if (DotLength > 10)
			DotLength = 10;
		DotList[DotCount].x = x * 1.6;
		DotList[DotCount].y = 600 - y * 1.2;
		DotList[DotCount].size = 3;
		DotList[DotCount].degree = 0;
		DotList[DotCount].type = 0;
		DotList[DotCount].degreetemp = 5;
		DotList[DotCount].r = rand() % 500 * 0.001;
		DotList[DotCount].g = rand() % 500 * 0.001;
		DotList[DotCount].b = rand() % 500 * 0.001;
		DotCount++;
		if (DotCount > 9)
			DotCount = 0;
	}
}


//윈도우 출력함수
GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2);

	float x, y, size, degree;

	for (int i = 0; i < DotLength; i++) {

		glColor3f(DotList[i].r, DotList[i].g, DotList[i].b);
		size = DotList[i].size;
		degree = DotList[i].degree;
		x = DotList[i].x;
		y = DotList[i].y;

		glBegin(GL_POINTS);
		if (DotList[i].type == 0) {
			for (int i = 0; i < degree;) {
				glVertex2f(x + i * 0.1 * sin(i / 180.0f * pi), y + (i*0.1 * cos(i / 180.0f * pi))*0.8);
				i += 7;
			}
		}

		else {
			for (int i = 0; i < 810;) {
				glVertex2f(x + i * 0.1 * sin(i / 180.0f * pi), y + (i*0.1 * cos(i / 180.0f * pi))*0.8);
				i += 7;
			}
			for (int i = 810; i > degree;) {
				glVertex2f((81 * 2) + x - i * 0.1 * sin(i / 180.0f * pi), y - (i*0.1 * cos(i / 180.0f * pi))*0.8);
				i -= 7;
			}

		}
		glEnd();

		DotList[i].degree = degree + DotList[i].degreetemp;

		if (DotList[i].type == 0 && DotList[i].degree >= 810) {
			DotList[i].type = 1;
			DotList[i].degreetemp = -5;
			DotList[i].degree = 810;
		}

		if (DotList[i].type == 1 && DotList[i].degree <= 3) {
			DotList[i].x = NULL;
			DotList[i].y = NULL;
			DotList[i].size = NULL;
			DotList[i].type = NULL;
		}

	}



	glFlush();
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

