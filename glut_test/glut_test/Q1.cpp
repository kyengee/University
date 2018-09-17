#include <gl/freeglut.h>
#include <stdlib.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid drawrect_(float, float, float, float);

void main(int argc, char *argv[])
{
	//초기화함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(250, 250);
	glutCreateWindow("Example");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}


//윈도우 출력함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	drawrect_(-1.0f, 1.0f, -0.8f, 0.8f);
	drawrect_(-1.0f, -1.0f, -0.8f, -0.8f);
	drawrect_(1.0f, 1.0f, 0.8f, 0.8f);
	drawrect_(1.0f, -1.0f, 0.8f, -0.8f);
	glBegin(GL_LINES);
	glVertex2i(-1, 0);
	glVertex2i(1, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex2i(0, -1);
	glVertex2i(0, 1);
	glEnd();
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0.2);
	glVertex2f(0.2, -0.1);
	glVertex2f(-0.2, -0.1);
	glEnd();



	glFlush();
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

GLvoid drawrect_(float x, float y, float z, float w) {
	glColor4f((float)(rand() % 100 * 0.01), (float)(rand() % 100 * 0.01), 0.0f, 1.0f);
	glRectf(x, y, z, w);

}