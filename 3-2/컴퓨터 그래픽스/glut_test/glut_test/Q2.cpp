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


		float Color = (rand() % 25565)*0.001;
		float colorTemp = (rand() % 5) * 10 * 0.01;
		//가로 : (rand() % 5 + 1)*2;
		int Horizental_count = (rand() % 5 + 1) * 2;
		float Horizental = 800 / Horizental_count;
		//세로 : (rand() % 10 + 11)*2;
		float vertical_count = (rand() % 10 + 5) * 2;
		float vertical = 600 / vertical_count;
		for (int i = 0; i < Horizental_count; i++) {
			for (int j = 0; j < vertical_count; j++) {
				glColor3f(Color, colorTemp, 0.5f);
				colorTemp += 0.005f;
				glRectf(i*Horizental-400, 300 - (j*vertical), (i+1)*Horizental - 400, 300 - ((j+1)*vertical));
			}
		}

	glFlush();
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glOrtho( -400.0, 400.0, -300.0, 300.0, -1.0, 1.0);
}

