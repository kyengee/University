#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
float pi = 3.141592;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);

GLvoid draw_sin();
GLvoid draw_spring();
GLvoid draw_ribon();
GLvoid draw_ractang();
GLvoid loop(int);
void DoTimer(int value);

void main(int argc, char *argv[])
{
	//초기화함수들
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Example");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(30, DoTimer, 1);
	glutMainLoop();

}
int ani = 0;
int temp = 0;

void DoTimer(int value)

{
	glutPostRedisplay();
	if (value == temp)
	glutTimerFunc(30, DoTimer, value);       // 30밀리초마다 호출

}
//윈도우 출력함수
GLvoid drawScene(GLvoid)
{
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);

		
		glPushMatrix();
		glLoadIdentity();
		glBegin(GL_LINE_STRIP);
		glVertex2f(-1, 0);
		glVertex2f(1, 0);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex2f(0, 1);
		glVertex2f(0, -1);
		glEnd();
		glPopMatrix();

		
		ani += temp;
		if (temp < 0 && ani < 0)
			ani = 300;
		if (temp > 0 && ani > 300)
			ani = 0;


		glPushMatrix();
		draw_sin();
		draw_spring();
		draw_ribon();
		draw_ractang();
		glPopMatrix();


		
		glFlush();
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -800.0, 800.0);
}

GLvoid draw_sin() {
	glBegin(GL_LINE_STRIP);
	int x = 200;
	while (x < 600) {
		glVertex2f(x, 400 + sin((ani+x)*pi / 180)*60);
		x++;
	}
	glEnd();


}
GLvoid draw_spring() {
	int x = 200;
	int r = 20;
	int set = -45;
	int X = 0;
	while (x < 600 + 1) {
		glBegin(GL_LINE_STRIP);
		X = x + ani;
		if (X > 600)
			X -= 420;
		while (set < 224 + 1) {
			glVertex2f(X + r * cos(set*pi / 180), 300 + r * sin(set*pi / 180));
			set++;
		}
		x += 30;
		set = -45;
		glEnd();
	}
	

}
GLvoid draw_ribon() {
	int set = -45;
	glBegin(GL_LINE_STRIP);
	glVertex2f(ani-100 + 300.0, 150.0);

	while (set < 224 + 1) {
		glVertex2f(ani-100 + 400.0 + 30 * cos(set*pi / 180), 215.0 + 30 * sin(set*pi / 180));
		set++;
	}
	glVertex2f(ani-100 + 500.0, 150.0);
	glEnd();
}
GLvoid draw_ractang() {
	int x = 200;
	int r = 30;
	int y = 100;
	int X = 0;
	while (x < 600 + 1) {
		X = x + ani;
		if (X > 600)
			X -= 450;
		glBegin(GL_LINE_STRIP);
		glVertex2i(X + r, y + r);
		glVertex2i(X - r, y + r);
		glVertex2i(X - r, y - r);
		glVertex2i(X + r, y - r);
		glVertex2i(X + r, y + r);
		glEnd();
		x += 90;
	}
	
}


GLvoid Keyboard(unsigned char key, int x, int y) {
	int t;
	switch (key) {
	case 'x':
		glTranslatef(3.0, 0.0, 0.0);
		break;
	case 'X':
		glTranslatef(-3.0, 0.0, 0.0);
		break;
	case 'y':
		glTranslatef(0.0, 3.0, 0.0);
		break;
	case 'Y':
		glTranslatef(0.0, -3.0, 0.0);
		break;
	case 's':
		glScalef(2.0, 1.0, 1.0);
		break;
	case 'S':
		glScalef(0.5, 1.0, 1.0);
		break;
	case 'r':
		printf("Input :");
		scanf_s("%d", &t);
		glTranslatef(t, 0.0, 0.0);
		break;
	case 'R':
		printf("Input :");
		scanf_s("%d", &t);
		glTranslatef(t*-1, 0.0, 0.0);
		break;
	case 'a':
		temp = 1;
		glutTimerFunc(30, DoTimer, temp);
		break;
	case 'A':
		temp = -1;
		glutTimerFunc(30, DoTimer, temp);
		break;
	case 'T':
		temp = 0;
		break;
	case 'Q':
		exit(0);
		break;


	}
		

	drawScene();
	

}
