#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdlib.h>

typedef struct dot {
	float x, y;
	float size = 10;
	int sizetemp = +1;
	int type;
	float r=0, g=0, b=0;
}Dot;


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
		DotList[DotCount].type = rand() % 2;
		if (DotList[DotCount].type == 0) {
			DotList[DotCount].r = rand() % 500 * 0.001;
			DotList[DotCount].g = rand() % 500 * 0.001;
			DotList[DotCount].b = rand() % 500 * 0.001;
		}
		DotCount++;
		if (DotCount > 9)
			DotCount = 0;
	}
}


//윈도우 출력함수
GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT);

	float x, y, Xs, Ys, size;

	for (int i = 0; i < DotLength; i++) {

		if (DotList[i].type == 0) {
			glColor3f(DotList[i].r, DotList[i].g, DotList[i].b);
		}
		glColor3f(rand() % 1000 * 0.001, rand() % 1000 * 0.001, rand() % 1000 * 0.001);
		size = DotList[i].size;
		if (DotList[i].x - size <= 0 || DotList[i].x + size >= 800)
			DotList[i].Xspeed *= -1;
		if (DotList[i].y - size - 5 <= 0 || DotList[i].y + size - 5 >= 600)
			DotList[i].Yspeed *= -1;
		Xs = DotList[i].Xspeed;
		Ys = DotList[i].Yspeed;


		x = DotList[i].x = DotList[i].x + Xs;
		y = DotList[i].y = DotList[i].y + Ys;
		glBegin(GL_POLYGON);
		if (type == 1) {
			glVertex2f(x, y + size);
			glVertex2f(x - size, y - size);
			glVertex2f(x + size, y - size);

		}

		if (type == 2) {
			glVertex2f(x - size, y - size - 5);
			glVertex2f(x + size, y - size - 5);
			glVertex2f(x + size, y + size - 5);
			glVertex2f(x - size, y + size - 5);
		}
		glEnd();
		if (size > 50)
			DotList[i].sizetemp = -1;
		if (size < 10)
			DotList[i].sizetemp = +1;
		DotList[i].size = size + DotList[i].sizetemp;


	}



	glFlush();
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

