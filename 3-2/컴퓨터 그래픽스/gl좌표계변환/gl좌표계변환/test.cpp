#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <ctime>
time_t t = time(NULL);
struct tm tm;
int twink = 1;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid draw_number(int);

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
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(30, DoTimer, 1);
	glutMainLoop();

}
int i = 0;
int flag = 1;
void DoTimer(int value)

{
	Sleep(30);
	i += flag;
	if (i < 0)
		flag = 1;
	if (i > 10)
		flag = -1;
	glutPostRedisplay();
	glutTimerFunc(30, DoTimer, 1);
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
	glutSolidTeacup(100.0);
	glTranslatef(800, 600, 0);
	glutSolidCube(100.0);

	glFlush();
}
int CC = 0;
GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	if(CC < 2)
	glOrtho(0.0, 800.0, 0.0, 600.0, -800.0, 800.0);
	CC++;
	glMatrixMode(GL_MODELVIEW);
}

GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

	}

}

GLvoid Keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 'a':
		glTranslatef(400.0, 0.0, 0.0);
		glRotatef(5, 0.0, 1.0, 0.0);
		glTranslatef(-400.0, 0.0, 0.0);
		break;
	case 'd':
		glTranslatef(400.0, 0.0, 0.0);
		glRotatef(-5, 0.0, 1.0, 0.0);
		glTranslatef(-400.0, 0.0, 0.0);
		break;



	}
	drawScene();
}

GLvoid draw_number(int a) {
	switch (a)
	{
	case 1:
		glColor3f(0.5839, 0.875, 0.3);
		glPushMatrix();
		glTranslatef(35.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, 35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, -35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPopMatrix();
		break;

	case 2:
		glColor3f(0.5839, 0.875, 0.3);
		glPushMatrix();
		glTranslatef(35.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, 35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-35.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, -35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glScalef(5.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 70.0, 0.0);
		glScalef(5.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, -70.0, 0.0);
		glScalef(5.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		break;

	case 3:
		glColor3f(0.5839, 0.875, 0.3);
		glPushMatrix();
		glTranslatef(35.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, 35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, -35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glScalef(5.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 70.0, 0.0);
		glScalef(5.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, -70.0, 0.0);
		glScalef(5.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		break;

	case 4:
		glColor3f(0.5839, 0.875, 0.3);
		glPushMatrix();
		glTranslatef(35.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, 35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, -35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-35.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, 35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glScalef(5.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		break;

	case 5:
		glColor3f(0.5839, 0.875, 0.3);
		glPushMatrix();
		glTranslatef(35.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, -35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-35.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, 35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glScalef(5.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 70.0, 0.0);
		glScalef(5.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, -70.0, 0.0);
		glScalef(5.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		break;

	case 6:
		glColor3f(0.5839, 0.875, 0.3);
		glPushMatrix();
		glTranslatef(35.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, -35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-35.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, 35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, -35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glScalef(5.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 70.0, 0.0);
		glScalef(5.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, -70.0, 0.0);
		glScalef(5.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		break;

	case 7:
		glColor3f(0.5839, 0.875, 0.3);
		glPushMatrix();
		glTranslatef(35.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, 35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, -35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 70.0, 0.0);
		glScalef(5.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		break;

	case 8:
		glColor3f(0.5839, 0.875, 0.3);
		glPushMatrix();
		glTranslatef(35.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, 35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, -35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-35.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, 35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, -35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glScalef(5.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 70.0, 0.0);
		glScalef(5.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, -70.0, 0.0);
		glScalef(5.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		break;

	case 9:
		glColor3f(0.5839, 0.875, 0.3);
		glPushMatrix();
		glTranslatef(35.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, 35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, -35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-35.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, 35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glScalef(5.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 70.0, 0.0);
		glScalef(5.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, -70.0, 0.0);
		glScalef(5.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		break;

	case 0:
		glColor3f(0.5839, 0.875, 0.3);
		glPushMatrix();
		glTranslatef(35.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, 35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, -35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-35.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, 35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, -35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 70.0, 0.0);
		glScalef(5.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, -70.0, 0.0);
		glScalef(5.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();
		break;

	case 10:
		glColor3f(0.2, 0.2, 0.2);
		glPushMatrix();
		glTranslatef(35.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, 35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutWireCube(10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, -35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutWireCube(10);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-35.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, 35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutWireCube(10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, -35.0, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glutWireCube(10);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glScalef(5.0, 1.0, 1.0);
		glutWireCube(10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 70.0, 0.0);
		glScalef(5.0, 1.0, 1.0);
		glutWireCube(10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, -70.0, 0.0);
		glScalef(5.0, 1.0, 1.0);
		glutWireCube(10);
		glPopMatrix();
		break;
	}


}