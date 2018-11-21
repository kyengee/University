#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
float pi = 3.141592;

int shape = 1;
float Zoom = 0;
float localDegree = 0;
float CameraDegree_x = 0;
float CameraDegree_y = 0;
float CameraDegree_z = 0;
float LeftDegree = 0;
float RightDegree = 0;
float ShapeDegree = 0;
bool LeftDegreeflag = true;
bool RightDegreeflag = true;
bool ShapeDegreeflag = false;
float move_x = 0;
float move_y = 0;

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
	glTranslated(move_x, move_y, 0.0);
	if (localDegree == 360)
		localDegree = 0;
	gluLookAt((900+Zoom)*sin(localDegree/180.0*pi), 0.0, (900 + Zoom)*cos(localDegree / 180.0*pi), 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
	glRotatef(CameraDegree_x, 1.0, 0.0, 0.0);
	glRotatef(CameraDegree_y, 0.0, 1.0, 0.0);
	glRotatef(CameraDegree_z, 0.0, 0.0, 1.0);
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(25.0f, 0.0f, 0.0f);
	glScalef(5.0f, 1.0f, 1.0f);
	glutSolidCube(10);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 25.0f, 0.0f);
	glScalef(1.0f, 5.0f, 1.0f);
	glutSolidCube(10);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, 0.0f, 25.0f);
	glScalef(1.0f, 1.0f, 5.0f);
	glutSolidCube(10);
	glPopMatrix();

	glTranslatef(0.0, -300.0, 0.0);
	glPushMatrix();
	glColor3f(0.7f, 0.7f, 0.0f);
	glScalef(80.0, 1.0, 80.0);
	glutSolidCube(10);
	glPopMatrix();
	if (ShapeDegreeflag == true)
		ShapeDegree += 5;
	if (ShapeDegree == 360)
		ShapeDegree = 0;
	glRotatef(ShapeDegree, 0.0, 1.0, 0.0);
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(-300, 150.0, 0.0);
	glScalef(15, 30, 15);
	if (LeftDegreeflag == true)
		LeftDegree += 5;
	if (LeftDegree == 360)
		LeftDegree = 0;
	glRotatef(LeftDegree, 0.0, 1.0, 0.0);
	switch (shape) {
	case 1:
		glutSolidCube(10);
		break;
	case 2:
		glutSolidSphere(10, 15, 15);
		break;
	case 3:
		glRotatef(-90, 1.0, 0.0, 0.0);
		glutSolidCone(10, 10, 15, 15);
		break;
	case 4:
		glutSolidTeapot(10);
		break;
	}
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(300, 150.0, 0.0);
	glScalef(15, 30, 15);
	if (RightDegreeflag == true)
		RightDegree += 5;
	if (RightDegree == 360)
		RightDegree = 0;
	glRotatef(RightDegree, 0.0, 1.0, 0.0);
	switch (shape) {
	case 1:
		glutWireCube(10);
		break;
	case 2:
		glutWireSphere(10, 15, 15);
		break;
	case 3:
		glRotatef(-90, 1.0, 0.0, 0.0);
		glutWireCone(10, 10, 15, 15);
		break;
	case 4:
		glutWireTeapot(10);
		break;
	}
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
	case 'X':
		CameraDegree_x += 10;
		break;
	case 'Y':
		CameraDegree_y += 10;
		break;
	case 'Z':
		CameraDegree_z += 10;
		break;
	case 'L':
		if (LeftDegreeflag == false)
			LeftDegreeflag = true;
		else
			LeftDegreeflag = false;
		break;
	case 'R':
		switch (RightDegreeflag) {
		case true:
			RightDegreeflag = false;
			break;
		case false:
			RightDegreeflag = true;
			break;
		}
		break;
	case 'O':
		if (ShapeDegreeflag == false)
			ShapeDegreeflag = true;
		else
			ShapeDegreeflag = false;
		break;
	case 'C':
		shape++;
		if (shape == 5)
			shape = 1;
		break;
	case 'i':
		Zoom -= 5;
		break;
	case 'o':
		Zoom += 5;
		break;
	case '+':
		localDegree += 5;
		break;
	case '-':
		localDegree -= 5;
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


	}
	glutPostRedisplay();


}

GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

	}



}