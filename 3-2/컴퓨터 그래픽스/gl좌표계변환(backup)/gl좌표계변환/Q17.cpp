#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
float pi = 3.141592;


int shape = 1;
int used = 0;
float X = 0;
float Y = 200;
float Z = 600;
float CameraDegree_x = 0;
float CameraDegree_xy = 0;
float CameraDegree_y = 90;
float CameraDegree_z = 0;
float CameraMove_z = 0;
float move_x = 0;
float move_y = 0;
int type = 1;
int toyung = 1;

class planet {
public:
	int r = 200;
	int degree = 0;
	int speed = 1;
	planet(int r1,int degree1, int speed1) {
		r = r1;
		degree = degree1;
		speed = speed1;

	}

};


GLvoid MenuFunc(int button);
GLvoid DrawPlanet(planet* a);
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
	GLint MenuID = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Solid Model", 1);
	glutAddMenuEntry("Wire Model", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutTimerFunc(30, DoTimer, 1);
	glutMainLoop();

}

void DoTimer(int value)

{
	glutPostRedisplay();
	glutTimerFunc(30, DoTimer, 1);
}
planet* a = new planet(200, 30, 1);
planet* b = new planet(200, 0, 3);
planet* c = new planet(200, 20, 5);

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	gluLookAt(X, Y, Z, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
	glTranslated(move_x, move_y, 0.0);

	glColor3f(1.0f, 0.5f, 0.0f);
	if(type == 1)
		glutSolidSphere(100, 30, 15);
	else
		glutWireSphere(100, 30, 15);
	glRotatef(90, 1.0, 0.0, 0.0);
	glPushMatrix();
		glColor3f(1.0, 1.0, 0.0);
		DrawPlanet(a);
		glScalef(0.5, 0.5, 0.5);
		glColor3f(1.0, 0.0, 0.0);
		DrawPlanet(c);
		a->degree += a->speed;
	glPopMatrix();

	glPushMatrix();
		glRotatef(45, 0.0, 1.0, 0.0);
		glColor3f(1.0, 1.0, 1.0);
		DrawPlanet(b);
		glScalef(0.5, 0.5, 0.5);
		glColor3f(1.0, 0.0, 1.0);
		DrawPlanet(a);
		b->degree += b->speed;
	glPopMatrix();

	glPushMatrix();
		glRotatef(-45, 0.0, 1.0, 0.0);
		glColor3f(1.0, 0.1, 0.5);
		DrawPlanet(c);
		glScalef(0.5, 0.5, 0.5);
		glColor3f(1.0, 0.6, 0.0);
		DrawPlanet(b);
		c->degree += c->speed;
	glPopMatrix();

	glPopMatrix();


	glutSwapBuffers();
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(toyung == 1)
		gluPerspective(60.0, 1.0, 1.0, 2000.0);
	else
		glOrtho(-800.0, 800.0, -600.0, 600.0, -800.0, 800.0);

	glMatrixMode(GL_MODELVIEW);
}

GLvoid Keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 't':
		if (toyung == 1)
			toyung = 2;
		else
			toyung = 1;
		break;
	case 'X':
		CameraDegree_x++;
		X = X;
		Y = Y * cos(CameraDegree_x) + -1 * Z*sin(CameraDegree_x);
		Z = Y * sin(CameraDegree_x) + Z * cos(CameraDegree_x);
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

GLvoid DrawPlanet(planet* a) {
	GLUquadric* obj = gluNewQuadric();
	gluDisk(obj, 199.0, 200.0, 100, 3);
	glTranslatef(a->r*sin(a->degree/180.0*pi),a->r*cos(a->degree/180.0*pi),0);
	if(type == 1)
	glutSolidSphere(20, 15, 15);
	else
		glutWireSphere(20, 15, 15);
	if (a->degree >= 360)
		a->degree = 0;
}

GLvoid MenuFunc(int button) {
	switch (button) {
	case 1:
		type = 1;
		break;
	case 2:
		type = 2;
		break;
	}
}