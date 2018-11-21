#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
float pi = 3.141592;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
void Motion(int x, int y);

void DoTimer(int value);

GLfloat ctrlpoints[19][3] = { 0, };
int ctrlcount = 0;


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
	glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(30, DoTimer, 1);
	glutMainLoop();

}




void DoTimer(int value)

{
	

	glutTimerFunc(30, DoTimer, 1);
	glutPostRedisplay();
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	// 제어점에 점을 그린다. 
	glPointSize (5.0); 
	glColor3f (0.0, 0.0, 1.0); 
	glBegin(GL_POINTS); 
	for ( int i = 0; i < ctrlcount ; i++ ) 
		glVertex3fv (&ctrlpoints[i][0]); 
	glEnd ();

	for (int i = 0; i + 3 < ctrlcount;) {
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[i][0]);
		glEnable(GL_MAP1_VERTEX_3);
		glMapGrid1f(10.0, 0.0, 1.0); // 매개변수 0~1 사이를 10개로 나눔 
		glEvalMesh1(GL_LINE, 0, 10);   // 선분으로 나눈 부분 0~10까지 선으로 그림
		glDisable(GL_MAP1_VERTEX_3);
		i = i + 3;
	}
	

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1000, 0, 1000, -1000, 1000);
	glMatrixMode(GL_MODELVIEW);
}

GLvoid Keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 'r':
		for (int i = 0; i < 19; i++) {
			ctrlpoints[i][0] = 0;
			ctrlpoints[i][1] = 0;
		}
		ctrlcount = 0;
		break;

	


	}
	glutPostRedisplay();


}
bool left_button = false;
GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		left_button = true;
		ctrlcount = (ctrlcount >= 19 ? 20 : ctrlcount + 1);
		if (ctrlcount != 20) {
			ctrlpoints[ctrlcount - 1][0] = x * 2;
			ctrlpoints[ctrlcount - 1][1] = 1000 - y * 2;
		}

	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
		left_button = false;

}

void Motion(int x, int y) { 
	if (left_button == true)
		for (int i = 0; i < ctrlcount; i++) {
			if (abs((int)ctrlpoints[i][0] - x * 2) < 7 && abs((int)ctrlpoints[i][1] - (1000 - y * 2))< 7) {
				ctrlpoints[i][0] = x * 2;
				ctrlpoints[i][1] = 1000 - y * 2;
			}
		}
}
