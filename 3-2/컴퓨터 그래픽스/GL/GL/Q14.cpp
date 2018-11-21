#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
int key_ = 1;
struct Shape {
	float x;
	float y;
	float rotate = 0;
	float scale = 1.0;
	int flag = 1;
	int shape = 0;

};
Shape List[30] = { 0, };
int length = 0;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);

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

void DoTimer(int value)

{
	Sleep(300);
	glutPostRedisplay();
	glutTimerFunc(30, DoTimer, 1);
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	for (int i = 0; i <= length; i++) {
		glPushMatrix();
		glTranslatef(List[i].x, List[i].y, 0.0);
		glScalef(List[i].scale, List[i].scale, List[i].scale);
		glRotatef(List[i].rotate * key_, 1.0, 0.0, 0.0);
		if (List[i].shape == 1)
			glutWireCone(10, 10, 15, 15);
		if (List[i].shape == 2)
			glutWireCube(10);
		if (List[i].shape == 3)
			glutWireSphere(10, 15, 15);
		if (List[i].shape == 4)
			glutWireTorus(8, 10, 15, 15);
		if (List[i].shape == 5)
			glutSolidTeapot(10);
		List[i].rotate += 10;
		if (List[i].rotate > 360)
			List[i].rotate = 0;
		if (List[i].scale > 10)
			List[i].flag = -1;
		List[i].scale += List[i].flag;
		if (List[i].scale < 0) {
			List[i].scale = 0;
			List[i].flag = 0;
		}
		glPopMatrix();

	}


	glFlush();
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -800.0, 800.0);
}

GLvoid Keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 'a':
		key_ = 1;
		break;
	case 'd':
		key_ = -1;
		break;



	}
	drawScene();


}

GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		List[length].x = x * 1.6;
		List[length].rotate = 0;
		List[length].scale = 1;
		List[length].flag = 1;
		List[length].shape = rand() % 6;
		List[length++].y = 600 - y * 1.2;
		if (length > 29)
			length = 0;
	}



}