#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

float little_rotate = 0;
float little_x = 400.0;
float little_y = 500.0;
float flag = 1;
float rotate;
int scale = 0;
int scale_ = 0;




GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);

void DoTimer(int value);

void main(int argc, char *argv[])
{
	//초기화함수들
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(30, DoTimer, 1);
	glutMainLoop();

}

void DoTimer(int value) {


	if (flag == 1) {
		little_x -= 5;
		little_y -= 6;
		if (little_x == 150 && little_y == 200)
			flag = 2;
	}
	if (flag == 2) {
		little_x += 5;
		if (little_x == 650 && little_y == 200)
			flag = 3;
	}
	if (flag == 3) {
		little_x -= 5;
		little_y += 6;
		if (little_x == 400 && little_y == 500)
			flag = 1;
	}

	little_rotate+= 5;
	Sleep(30);
	glutPostRedisplay();
	glutTimerFunc(30, DoTimer, 1);
}

//윈도우 출력함수
GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	if (rotate != 0) {
		glTranslatef(400, 0.0, 0.0);
		glRotatef(rotate, 0.0, 1.0, 0.0);
		glTranslatef(-400, 0.0, 0.0);
	}

	if (scale > 0) {
		glTranslatef(400, 300.0, 0.0);
		glScalef(1.2, 1.2, 1.0);
		glTranslatef(-400, -300.0, 0.0);
	}
	if (scale < 0) {
		glTranslatef(400, 300.0, 0.0);
		glScalef(0.7, 0.7, 1.0);
		glTranslatef(-400, -300.0, 0.0);
	}

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(400, 500);
	glVertex2f(150, 200);
	glVertex2f(650, 200);
	glEnd();

	glPushMatrix();
		glTranslatef(little_x, little_y, 0.0);
		if(rotate != 0)
			glRotatef(little_rotate, 0.0, 1.0, 0.0);
		if (scale_ > 0)
			glScalef(0.7, 0.7, 1.0);
		if (scale_ < 0)
			glScalef(1.2, 1.2, 1.0);
		glBegin(GL_TRIANGLES);
		glVertex2f(0.0, 0.0 + 10);
		glVertex2f(0.0 + 15, 0.0 - 10);
		glVertex2f(0.0 - 15, 0.0 - 10);
		glEnd();
		if (little_rotate > 360)
			little_rotate = 0;
	glPopMatrix();

	glPushMatrix();
		glTranslatef(400, 0.0, 0.0);
		glRotatef(90, 0.0, 1.0, 0.0);
		glTranslatef(-400, 0.0, 0.0);
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(400, 500);
		glVertex2f(150, 200);
		glVertex2f(650, 200);
		glEnd();

		glPushMatrix();
			glTranslatef(little_x, little_y, 0.0);
			if (rotate != 0)
				glRotatef(little_rotate, 0.0, 1.0, 0.0);
			if (scale_ > 0)
				glScalef(0.7, 0.7, 1.0);
			if (scale_ < 0)
				glScalef(1.2, 1.2, 1.0);
			glBegin(GL_TRIANGLES);
			glVertex2f(0.0, 0.0 + 10);
			glVertex2f(0.0 + 15, 0.0 - 10);
			glVertex2f(0.0 - 15, 0.0 - 10);
			glEnd();
			if (little_rotate > 360)
				little_rotate = 0;
		glPopMatrix();

		if(scale != 0)
			scale = 0;

	glFlush();
}


GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -800.0, 800.0);
}


GLvoid Keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 'y':
		rotate = 3;
		break;
	case 'Y':
		rotate = -3;
		break;
	case 's':
		scale = 5;
		scale_ = scale;
		break;
	case 'S':
		scale = -5;
		scale_ = scale;
		break;
	
	

	}
	drawScene();


}