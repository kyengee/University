#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
float pi = 3.141592;

char state = NULL;
int shape = 1;
int used = 0;
float CameraDegree_x = 0;
float CameraDegree_y = 0;
float CameraDegree_z = 0;
float CameraMove_z = 0;
float move_x = 0;
float move_y = 0;
float Red_Box = 0;
float Red_Box_Dr = 3;
float Red_Box_Y = 0;
float Green_Box_X = 0;
float Green_Box_Y = 0;
float Blue_Box_X = 0;
float Blue_Box_Z = 0;

void draw__(int a) {
	switch (a) {
	case 1:
	case 0:
		glRotatef(CameraDegree_x, 1.0, 0.0, 0.0);
		glRotatef(CameraDegree_y, 0.0, 1.0, 0.0);
		glRotatef(CameraDegree_z, 0.0, 0.0, 1.0);
		break;
	case 2:
		glRotatef(CameraDegree_y, 0.0, 1.0, 0.0);
		glRotatef(CameraDegree_x, 1.0, 0.0, 0.0);
		glRotatef(CameraDegree_z, 0.0, 0.0, 1.0);
		break;
	case 3:
		glRotatef(CameraDegree_z, 0.0, 0.0, 1.0);
		glRotatef(CameraDegree_y, 0.0, 1.0, 0.0);
		glRotatef(CameraDegree_x, 1.0, 0.0, 0.0);
		break;
	}

}




GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);

void DoTimer(int value);

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
	Red_Box += Red_Box_Dr;
	if (Red_Box > 200)
		Red_Box_Dr = -3;
	if (Red_Box < -200)
		Red_Box_Dr = 3;
	glutPostRedisplay();
	glutTimerFunc(30, DoTimer, 1);
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	gluLookAt(0.0, 200.0 + CameraMove_z / 3.0, 600.0 + CameraMove_z, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
	draw__(used);
	glTranslated(move_x, move_y, 0.0);

	glTranslatef(0.0, -300.0, 0.0);

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glScalef(80.0, 1.0, 80.0);
	glutSolidCube(10);
	glPopMatrix();

	glTranslatef(Red_Box, 0.0, 0.0);
	glRotatef(Red_Box_Y, 0.0, 1.0, 0.0);
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glScalef(4.0, 3.0, 3.0);
	glutSolidCube(50);
	glColor3f(1.0, 1.0, 1.0);
	glutWireCube(50);
	glPopMatrix();

	glTranslatef(0.0, 50.0, 0.0);
	glRotatef(Green_Box_Y, 0.0, 1.0, 0.0);
	glRotatef(Green_Box_X, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 100.0, 0.0);
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glScalef(1.5, 4.0, 1.5);
	glutSolidCube(40);
	glColor3f(1.0, 1.0, 1.0);
	glutWireCube(40);
	glPopMatrix();

	glTranslatef(0.0, 50.0, 0.0);
	glRotatef(Blue_Box_X, 1.0, 0.0, 0.0);
	glRotatef(Blue_Box_Z, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 100.0, 0.0);
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glScalef(0.5, 4.0, 0.5);
	glutSolidCube(40);
	glColor3f(1.0, 1.0, 1.0);
	glutWireCube(40);
	glPopMatrix();


	glPopMatrix();



	glutSwapBuffers();
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 2000.0);
	glMatrixMode(GL_MODELVIEW);
}

GLvoid Keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case '1':
		Red_Box_Y += 3;
		if (Red_Box_Y > 90)
			Red_Box_Y = 90;
		break;
	case '!':
		Red_Box_Y -= 3;
		if (Red_Box_Y < -90)
			Red_Box_Y = -90;
		break;
	case '2':
		Green_Box_X += 3;
		if (Green_Box_X > 90)
			Green_Box_X = 90;
		break;
	case '@':
		Green_Box_X -= 3;
		if (Green_Box_X < -90)
			Green_Box_X = -90;
		break;
	case '3':
		Green_Box_Y += 3;
		if (Green_Box_Y > 90)
			Green_Box_Y = 90;
		break;
	case '#':
		Green_Box_Y -= 3;
		if (Green_Box_Y < -90)
			Green_Box_Y = -90;
		break;
	case '4':
		Blue_Box_X += 3;
		if (Blue_Box_X > 90)
			Blue_Box_X = 90;
		break;
	case '$':
		Blue_Box_X -= 3;
		if (Blue_Box_X < -90)
			Blue_Box_X = -90;
		break;
	case '5':
		Blue_Box_Z += 3;
		if (Blue_Box_Z > 90)
			Blue_Box_Z = 90;
		break;
	case '%':
		Blue_Box_Z -= 3;
		if (Blue_Box_Z < -90)
			Blue_Box_Z = -90;
		break;
	case 'X':
		CameraDegree_x += 10;
		used = 1;
		break;
	case 'Y':
		CameraDegree_y += 10;
		used = 2;
		break;
	case 'Z':
		CameraDegree_z += 10;
		used = 3;
		break;
	case 'x':
		CameraDegree_x -= 10;
		used = 1;
		break;
	case 'y':
		CameraDegree_y -= 10;
		used = 2;
		break;
	case 'z':
		CameraDegree_z -= 10;
		used = 3;
		break;
	case 'w':
		move_y += 10;
		break;
	case 's':
		move_y -= 10;
		break;
	case 'd':
		move_x += 10;
		break;
	case 'a':
		move_x -= 10;
		break;
	case '+':
		CameraMove_z -= 10;
		break;
	case '-':
		CameraMove_z += 10;
		break;
	case 'i':
		CameraDegree_x = 0;
		CameraDegree_y = 0;
		CameraDegree_z = 0;
		move_x = 0;
		move_y = 0;
		CameraMove_z = 0;
		break;
	

	}



	glutPostRedisplay();


}

GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

	}



}

