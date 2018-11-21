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
float CameraDegree_y = 90;
float CameraDegree_z = 0;
float CameraMove_z = 0;
float move_x = 0;
float move_y = 0;
float X = 0;
float Y = 0;
float Z = 0;
float X_g = 0;
float Y_g = 0;
float Z_g = 0;

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

	glPushMatrix();
	glTranslatef(0.0, -150.0, 0.0);
	glColor3f(0.0f, 1.0f, 1.0f);
	glScalef(1.0, 60.0, 1.0);
	glutSolidCube(5);
	glPopMatrix();

	glTranslatef(0.0, -300.0, 0.0);

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glScalef(80.0, 1.0, 80.0);
	glutSolidCube(10);
	glPopMatrix();

	glTranslatef(0.0, 50.0, 0.0);
	glTranslatef(X, Y, Z);
	if (state == 'x') {
		glRotatef(X_g, 1.0, 0.0, 0.0);
		glRotatef(Z_g, 0.0, 0.0, 1.0);
	}
	else if (state == 'y') {
		glRotatef(Y_g, 0.0, 1.0, 0.0);
	}
	else {
		glRotatef(Z_g, 0.0, 0.0, 1.0);
		glRotatef(X_g, 1.0, 0.0, 0.0);
	}
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glScalef(1.0, 4.0, 1.0);
	glutSolidCube(10);
	glPopMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glutWireSphere(50, 30, 15);

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
		X = 0; y = 0; Z = 0;
		X_g = 0; Y_g = 0; Z_g = 0;
		break;
	case 'l':
		if (X < 400) 
			X+=3;
			Z_g-=3;
			state = 'z';
		break;
	case 'L':
		if (X > -400) 
			X-=3;
			Z_g+=3;
			state = 'z';
		break;
	case 'm':
			Y_g-=3;
			state = 'y';
		break;
	case 'M':
			Y_g+=3;
			state = 'y';
		break;
	case 'n':
		if (Z < 400) 
			Z+=3;
			X_g+=3;
			state = 'x';
		break;
	case 'N':
		if (Z > -400) 
			Z-=3;
			X_g-=3;
			state = 'x';
		break;








	}



	glutPostRedisplay();


}

GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

	}



}

