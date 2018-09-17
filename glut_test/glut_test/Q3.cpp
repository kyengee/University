#include <gl/freeglut.h>
#include <stdlib.h>


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

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

	int Shape = (rand() %4) + 2;
	int add = +1;
	float Horizental = 300;
	float vertical = 300;
	float x, y;
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			
			//시작좌표 : x = -450 + (i*Horizental), y = 450 - (j*vertical)
			x = -150 + (j*Horizental);
			y = 450 - (i*vertical);

			glBegin(GL_POLYGON);
			
			switch (Shape) {
			case 2:
				glVertex2f(x - 120, y - 120);
				glVertex2f(x - 120, y - 122);
				glVertex2f(x - 180, y - 182);
				glVertex2f(x - 180, y - 180);
				break;
			case 3:
				glVertex2f(x - 150, y - 120);
				glVertex2f(x - 120, y - 170);
				glVertex2f(x - 180, y - 170);
				break;
			case 4:
				glVertex2f(x - 120, y - 120);
				glVertex2f(x - 180, y - 120);
				glVertex2f(x - 180, y - 180);
				glVertex2f(x - 120, y - 180);
				break;
			case 5:
				glVertex2f(x - 150, y - 120);
				glVertex2f(x - 170, y - 135);
				glVertex2f(x - 160, y - 160);
				glVertex2f(x - 140, y - 160);
				glVertex2f(x - 130, y - 135);
				break;
			}
			
			glEnd();

			if (Shape == 5)
				add = -1;
			if (Shape == 2)
				add = +1;
			Shape = Shape + add;
		}
	}

	glFlush();
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glOrtho(-450.0, 450.0, -450.0, 450.0, -1.0, 1.0);
}

