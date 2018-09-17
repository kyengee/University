#include <gl/freeglut.h>
#include <stdlib.h>

typedef struct dot {
	float x, y;
	float size = 10;
	int sizetemp = +1;
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
		DotList[DotCount].x = x*1.6;
		DotList[DotCount].y = 600 - y*1.2;
		DotCount++;
		if (DotCount > 9)
			DotCount = 0;
	}
}


//윈도우 출력함수
GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT);

	float x, y,size;
	for (int i = 0; i < DotLength; i++) {
		glColor3f(rand()%1000*0.001, rand() % 1000 * 0.001, rand() % 1000 * 0.001);
		size = DotList[i].size;
		x = DotList[i].x;
		y = DotList[i].y;
		glBegin(GL_POLYGON);
		glVertex2f(x - size, y - size-5);
		glVertex2f(x + size, y - size-5);
		glVertex2f(x + size, y + size-5);
		glVertex2f(x - size, y + size-5);
		glEnd();
		if (size > 50)
			DotList[i].sizetemp = -1;
		if(size < 10)
			DotList[i].sizetemp = +1;
		DotList[i].size = size + DotList[i].sizetemp;

	}



	glFlush();
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

