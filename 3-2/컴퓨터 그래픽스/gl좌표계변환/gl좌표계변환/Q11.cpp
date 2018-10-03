#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
float pi = 3.141592;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

GLvoid draw_sin();
GLvoid draw_spring();
GLvoid draw_ribon();
GLvoid draw_ractang();


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
	glutMainLoop();

}

//윈도우 출력함수
GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

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
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

GLvoid draw_sin() {
	glBegin(GL_LINE_STRIP);
	int x = 200;
	while (x < 600) {
		glVertex2f(x, 150 + sin(x*pi / 180)*10);
		x++;
	}
	glEnd();

}
//GLvoid draw_spring()
//GLvoid draw_ribon()
//GLvoid draw_ractang()