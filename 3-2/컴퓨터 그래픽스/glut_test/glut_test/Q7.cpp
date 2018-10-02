#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdlib.h>
#include <math.h>

typedef struct dot {
	float x, y;
	float size = 5;
	int sizetemp = +1;
	int type = 0;
	float r=0, g=0, b=0;
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
		
		DotList[DotCount].r = rand() % 500 * 0.001;
		DotList[DotCount].g = rand() % 500 * 0.001;
		DotList[DotCount].b = rand() % 500 * 0.001;
		DotList[DotCount].type = rand() % 2;
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

		if (DotList[i].type == 0)
			glColor3f(DotList[i].r, DotList[i].g, DotList[i].b);
		else
			glColor3f(rand() % 500 * 0.001, rand() % 500 * 0.001, rand() % 500 * 0.001);

		x = DotList[i].x;
		y = DotList[i].y;
		size = DotList[i].size;

		glBegin(GL_POINTS);
		for (int i = 0; i <= 360; i++)
			glVertex2f(x + size * sin(i / 180.0f * pi), y + (size * cos(i / 180.0f * pi))*0.8);
		glEnd();

		DotList[i].size = size + DotList[i].sizetemp;

		if (DotList[i].type == 0) {
			if (DotList[i].size >= 50)
				DotList[i].size = 5;
		}

		if (DotList[i].type == 1 ) {
			if (DotList[i].size >= 300) {
				DotList[i].x = NULL;
				DotList[i].y = NULL;
				DotList[i].size = NULL;
				DotList[i].type = NULL;
			}
		}
	}
	glFlush();
}

	

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

