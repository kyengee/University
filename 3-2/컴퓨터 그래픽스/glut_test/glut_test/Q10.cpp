#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdlib.h>
#include <math.h>

typedef struct dot {
	float x, y;
	float Xspeed = 10;
	float Yspeed = 10;
	float size = 10;
	int sizetemp = +1;
	int type = 0;
	int lastY, lastX;
	int dir = 0;
	float r, g, b;

}Dot;


Dot DotList[30];
Dot eraiser;
int DotCount = 0;
int DotLength = 0;
bool left_button = false;
bool draw = false;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);
GLvoid TimerFunction(int value);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid init() {
	for (int i = 0; i < 30; i++) {
		DotList[i].x = rand() % 800;
		DotList[i].y = rand() % 600;
		DotList[i].r = rand() % 500 * 0.001;
		DotList[i].g = rand() % 500 * 0.001;
		DotList[i].b = rand() % 500 * 0.001;
		DotList[i].Xspeed = rand() % 40;
		DotList[i].Yspeed = rand() % 40;
	}
}


void main(int argc, char *argv[])
{
	//초기화함수들
	glutInit(&argc, argv);
	init();
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Example");
	glutDisplayFunc(drawScene);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
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
		left_button = true;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		left_button = false;
}

GLvoid Motion(int x, int y) {
	if (left_button == true) {
		eraiser.x = x * 1.6;
		eraiser.y = 600 - y * 1.2;
	}



}


//윈도우 출력함수
GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT);

	float Xs,Ys, x, y, size = 10,long_;
	for (int i = 0; i < 30; i++) {
		glColor3f(DotList[i].r, DotList[i].g, DotList[i].b);

		if (DotList[i].x - size <= 0 || DotList[i].x + size >= 800)
			DotList[i].Xspeed *= -1;
		if (DotList[i].y - size - 5 <= 0 || DotList[i].y + size - 5 >= 600)
			DotList[i].Yspeed *= -1;


		Xs = DotList[i].Xspeed;
		Ys = DotList[i].Yspeed;


		x = DotList[i].x + Xs;
		DotList[i].x = x;
		y = DotList[i].y + Ys;
		DotList[i].y = y;
		glBegin(GL_POLYGON);
		if (DotList[i].type == 0) {
			glVertex2f(x - size, y - size + 2);
			glVertex2f(x + size, y - size + 2);
			glVertex2f(x + size, y + size - 2);
			glVertex2f(x - size, y + size - 2);
		}
		if (DotList[i].type > 0) {
			glColor3f(rand() % 500 * 0.001, rand() % 500 * 0.001, rand() % 500 * 0.001);
			long_ = DotList[i].type;
			glVertex2f(x - size - long_, y - size - long_ + 2);
			glVertex2f(x + size + long_, y - size - long_ + 2);
			glVertex2f(x + size - long_, y + size + long_ - 2);
			glVertex2f(x - size + long_, y + size + long_ - 2);
			DotList[i].type++;
		}
		if (DotList[i].type > 10)
			DotList[i].type = -10;

		if (DotList[i].type < 0) {
			glColor3f(rand() % 500 * 0.001, rand() % 500 * 0.001, rand() % 500 * 0.001);
			long_ = DotList[i].type * -1;
			glVertex2f(x - size - long_, y - size + 2);
			glVertex2f(x + size + long_, y - size + 2);
			glVertex2f(x + size - long_, y + size + long_ - 2);
			glVertex2f(x - size + long_, y + size + long_ - 2);
			DotList[i].type++;
		}



		glEnd();
	}

	if (left_button == true) {
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_POLYGON);
		x = eraiser.x;
		y = eraiser.y;
		size = 20;
		glVertex2f(x - size, y - size + 2);
		glVertex2f(x + size, y - size + 2);
		glVertex2f(x + size, y + size - 2);
		glVertex2f(x - size, y + size - 2);
		glEnd();
	}

	if (left_button == true)
		for (int i = 0; i < 30; i++) {
			int xtemp = DotList[i].x - eraiser.x;
			if (xtemp < 0)
				xtemp *= -1;
			int ytemp = DotList[i].y - eraiser.y;
			if (ytemp < 0)
				ytemp *= -1;


			if (xtemp < 30 && ytemp < 26 && DotList[i].type == 0) {
				DotList[i].type = 1;
			}
			

		}


	glFlush();
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

