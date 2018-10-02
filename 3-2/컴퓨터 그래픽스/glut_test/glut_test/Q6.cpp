#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdlib.h>

typedef struct dot {
	float x, y;
	float Xspeed = 10;
	float Yspeed = 10;
	float size = 10;
	int sizetemp = +1;
	int type = 0;
	int lastY,lastX;
	int dir = 0;
}Dot;


Dot DotList[10];
int DotCount = 0;
int DotLength = 0;
char keyInput = 'a';
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid TimerFunction(int value);
GLvoid Keyboard(unsigned char key, int x, int y);


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
	glutKeyboardFunc(Keyboard);
	glutMainLoop();

}


GLvoid Keyboard(unsigned char key, int x, int y) {
	int numkey = 100;
	switch (key) {
	case '1':
		numkey = 1;
		break;
	case '2':
		numkey = 2;
		break;
	case '3':
		numkey = 3;
		break;
	case '4':
		numkey = 4;
		break;
	case '5':
		numkey = 5;
		break;
	case '6':
		numkey = 6;
		break;
	case '7':
		numkey = 7;
		break;
	case '8':
		numkey = 8;
		break;
	case '9':
		numkey = 9;
		break;
	case '0':
		numkey = 0;
		break;
	case 's':
		keyInput = 's';
		break;
	case 'p':
		keyInput = 'p';
		for (int i = 0; i < DotLength; i++) {
			DotList[i].Xspeed = rand() % 40;
			DotList[i].Yspeed = rand() % 40;
			DotList[i].type = 0;
		}
		break;
		
	}
	if (1 <= numkey && numkey <= 9) {
		DotList[numkey - 1].type = rand() % 2 + 1;
		DotList[numkey - 1].lastX = DotList[numkey - 1].x;
		DotList[numkey - 1].lastY = DotList[numkey - 1].y;
		DotList[numkey - 1].dir = 0;

		if (DotList[numkey - 1].type == 1) {
			DotList[numkey - 1].Xspeed = -5;
			DotList[numkey - 1].Yspeed = 0;
		}
		if (DotList[numkey - 1].type == 2) {
			DotList[numkey - 1].Xspeed = 5;
			DotList[numkey - 1].Yspeed = 0;
		}
	}

		if (numkey == 0) {
			for (int i = 0; i < DotLength; i++) {
				DotList[i].type = rand() % 2 + 1;
				DotList[i].lastX = DotList[i].x;
				DotList[i].lastY = DotList[i].y;
				DotList[i].dir = 0;

				if (DotList[i].type == 1) {
					DotList[i].Xspeed = -5;
					DotList[i].Yspeed = 0;
				}
				if (DotList[i].type == 2) {
					DotList[i].Xspeed = 5;
					DotList[i].Yspeed = 0;
				}
			}
		}

	}






GLvoid TimerFunction(int value) {
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}


GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		DotLength++;
		if (DotLength >= 10)
			DotLength = 9;
		DotList[DotCount].x = x * 1.6;
		DotList[DotCount].y = 600 - y * 1.2;
		DotList[DotCount].Xspeed = rand() % 40;
		DotList[DotCount].Yspeed = rand() % 40;
		DotCount++;
		if (DotCount > 8)
			DotCount = 0;
	}
}


//윈도우 출력함수
GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);

	float x, y, Xs, Ys, size;
	for (int i = 0; i < DotLength; i++) {
		size = DotList[i].size;
		if (DotList[i].type == 0) {
			if (DotList[i].x - size <= 0 || DotList[i].x + size >= 800)
				DotList[i].Xspeed *= -1;
			if (DotList[i].y - size - 5 <= 0 || DotList[i].y + size - 5 >= 600)
				DotList[i].Yspeed *= -1;
		}
		if (DotList[i].type == 1) {
			if (DotList[i].x - size <= 0 && DotList[i].dir == 0) {
				DotList[i].Xspeed = 0;
				DotList[i].Yspeed = -5;
				DotList[i].dir = 1;
			}
			if (DotList[i].y - size - 5 <= 0 && DotList[i].dir == 1) {
				DotList[i].Xspeed = 5;
				DotList[i].Yspeed = 0;
				DotList[i].dir = 2;
			}
			if (DotList[i].x + size >= 800 && DotList[i].dir == 2) {
				DotList[i].Xspeed = 0;
				DotList[i].Yspeed = 5;
				DotList[i].dir = 3;
			}
			if (DotList[i].y >= DotList[i].lastY && DotList[i].dir == 3) {
				DotList[i].Xspeed = -5;
				DotList[i].Yspeed = 0;
				DotList[i].dir = 4;
			}

			if (DotList[i].y == DotList[i].lastY && DotList[i].x <= DotList[i].lastX && DotList[i].dir == 4) {
				DotList[i].Xspeed = rand() % 40;
				DotList[i].Yspeed = rand() % 40;
				DotList[i].dir = 0;
				DotList[i].type = 0;
			}
		}

		if (DotList[i].type == 2) {
			if (DotList[i].x - size <= 0 && DotList[i].dir == 2) {
				DotList[i].Xspeed = 0;
				DotList[i].Yspeed = 5;
				DotList[i].dir = 3;
			}
			if (DotList[i].x + size >= 800 && DotList[i].dir == 0) {
				DotList[i].Xspeed = 0;
				DotList[i].Yspeed = -5;
				DotList[i].dir = 1;
			}
			if (DotList[i].y - size - 5 <= 0 && DotList[i].dir == 1) {
				DotList[i].Xspeed = -5;
				DotList[i].Yspeed = 0;
				DotList[i].dir = 2;
			}
			if (DotList[i].y >= DotList[i].lastY && DotList[i].dir == 3) {
				DotList[i].Xspeed = 5;
				DotList[i].Yspeed = 0;
				DotList[i].dir = 4;
			}
			if (DotList[i].y >= DotList[i].lastY && DotList[i].x >= DotList[i].lastX && DotList[i].dir == 4) {
				DotList[i].Xspeed = rand() % 40;
				DotList[i].Yspeed = rand() % 40;
				DotList[i].dir = 0;
				DotList[i].type = 0;
			}
		}
		Xs = DotList[i].Xspeed;
		Ys = DotList[i].Yspeed;


		if (keyInput == 's') {
			x = DotList[i].x;
			DotList[i].x = x;
			y = DotList[i].y;
			DotList[i].y = y;
		}
		else{
			x = DotList[i].x + Xs;
			DotList[i].x = x;
			y = DotList[i].y + Ys;
			DotList[i].y = y;
		}
		glBegin(GL_POLYGON);
			glVertex2f(x - size, y - size - 5);
			glVertex2f(x + size, y - size - 5);
			glVertex2f(x + size, y + size - 5);
			glVertex2f(x - size, y + size - 5);
		
		glEnd();
		if (size > 50)
			DotList[i].sizetemp = -1;
		if (size < 10)
			DotList[i].sizetemp = +1;
		if(DotList[i].type == 0 && keyInput != 's')
		DotList[i].size = size + DotList[i].sizetemp;


	}



	glFlush();
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

