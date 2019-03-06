#define _CRT_SECURE_NO_WARNINGS
#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
float pi = 3.141592;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
int target = 0;
float alpha[9] = { 0, };


void DoTimer(int value);
void setblend(int);

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
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(30, DoTimer, 1);
	glutMainLoop();

}
GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat DiffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.7f };
GLfloat SpecularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPos[] = { 0.0, 1200.0, 500.0,1.0 };



void DoTimer(int value)

{
	glutPostRedisplay();

	glutTimerFunc(30, DoTimer, value);       // 30밀리초마다 호출

}
//윈도우 출력함수
GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_BLEND); 
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientLight);



	glPushMatrix();

	glTranslated(300, 300, 0);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if ((i * 3 + j + 1) == target) {
				glDisable(GL_BLEND);
				glBegin(GL_LINE_LOOP);
				glVertex2d(-300, -300);
				glVertex2d(-300, 300);
				glVertex2d(300, 300);
				glVertex2d(300, -300);
				glEnd();
				glEnable(GL_BLEND);
			}
			glColor3f(1, 1, 1);
			setblend(i*3 + j + 1);
			
			glPushMatrix();
			glColor4f(1, 0, 0, (90 - j * 10) / 100.0 + alpha[i * 3 + j]);
			glutSolidSphere(50, 15, 15);
			glTranslatef(-50, -50,0);
			glColor4f(0, 1, 0, (90 - j * 10) / 100.0 + alpha[i * 3 + j]);
			glutSolidTeapot(50);
			glTranslatef(100, 0, 0);
			glRotatef(-90, 1, 0,0);
			glColor4f(0, 0, 1, (90 - j * 10) / 100.0 + alpha[i * 3 + j]);
			glutSolidCone(50, 70, 15, 15);
			glPopMatrix();
			glTranslatef(600, 0, 0);
		}
		glTranslatef(0, 600, 0);
		glTranslatef(-600*3, 0, 0);
	}

	glPopMatrix();



	glFlush();
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1800, 0.0, 1800.0, -800.0, 800.0);
}

void setblend(int arg) {
	char *c = (char *)malloc(sizeof(char) * 100);
	char temp[100] = { 0, };
	switch (arg)
	{

	case 9:
		glBlendFunc(GL_ONE, GL_ONE);
		glRasterPos2f(-300, -300.0);
		for (strcpy(c,"(GL_ONE, GL_ZERO)\0"); *c != '\0'; c++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
		}
		glBlendFunc(GL_ONE, GL_ZERO);

		break;
	case 8:
		glBlendFunc(GL_ONE, GL_ONE);
		glRasterPos2f(-300, -300.0);
		for (strcpy(c, "(GL_ZERO, GL_ONE)\0"); *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
		}
		glBlendFunc(GL_ZERO, GL_ONE);
		break;
	case 7:
		glBlendFunc(GL_ONE, GL_ONE);
		glRasterPos2f(-300, -300.0);
		for (strcpy(c, "(GL_ONE, GL_ONE)\0"); *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
		}
		glBlendFunc(GL_ONE, GL_ONE);
		break;
	case 6:
		glBlendFunc(GL_ONE, GL_ONE);
		glRasterPos2f(-300, -300.0);
		for (strcpy(c, "(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)\0"); *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
		}
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	case 5:
		glBlendFunc(GL_ONE, GL_ONE);
		glRasterPos2f(-300, -300.0);
		for (strcpy(c, "(GL_SRC_ALPHA, GL_ONE)\0"); *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
		}
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		break;
	case 4:
		glBlendFunc(GL_ONE, GL_ONE);
		glRasterPos2f(-300, -300.0);
		for (strcpy(c, "(GL_ZERO, GL_SRC_COLOR)\0"); *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
		}
		glBlendFunc(GL_ZERO, GL_SRC_COLOR);
		break;
	case 3:
		glBlendFunc(GL_ONE, GL_ONE);
		glRasterPos2f(-300, -300.0);
		for (strcpy(c, "(GL_ONE_MINUS_DST_COLOR, GL_ZERO)\0"); *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
		}
		glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
		break;
	case 2:
		glBlendFunc(GL_ONE, GL_ONE);
		glRasterPos2f(-300, -300.0);
		for (strcpy(c, "(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR)\0"); *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
		}
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
		break;
	case 1:
		glBlendFunc(GL_ONE, GL_ONE);
		glRasterPos2f(-300, -300.0);
		for (strcpy(c, "(GL_ONE, GL_ONE)\0"); *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
		}
		glBlendFunc(GL_ONE, GL_ONE);
		break;

	}
}




GLvoid Keyboard(unsigned char key, int x, int y) {
	
	switch (key) {
	case '1':
		target = 1;
		alpha[target - 1] -= 0.1;
		break;
	case '!':
		target = 1;
		alpha[target - 1] += 0.1;
		break;
	case '2':
		target = 2;
		alpha[target - 1] -= 0.1;
		break;
	case '@':
		target = 2;
		alpha[target - 1] += 0.1;
		break;
	case '3':
		target = 3;
		alpha[target - 1] -= 0.1;
		break;
	case '#':
		target = 3;
		alpha[target - 1] += 0.1;
		break;
	case '4':
		target = 4;
		alpha[target - 1] -= 0.1;
		break;
	case '$':
		target = 4;
		alpha[target - 1] += 0.1;
		break;
	case '5':
		target = 5;
		alpha[target - 1] -= 0.1;
		break;
	case '%':
		target = 5;
		alpha[target - 1] += 0.1;
		break;
	case '6':
		target = 6;
		alpha[target - 1] -= 0.1;
		break;
	case '^':
		target = 6;
		alpha[target - 1] += 0.1;
		break;
	case '7':
		target = 7;
		alpha[target - 1] -= 0.1;
		break;
	case '&':
		target = 7;
		alpha[target - 1] += 0.1;
		break;
	case '8':
		target = 8;
		alpha[target - 1] -= 0.1;
		break;
	case '*':
		target = 8;
		alpha[target - 1] += 0.1;
		break;
	case '9':
		target = 9;
		alpha[target - 1] -= 0.1;
		break;
	case '(':
		target = 9;
		alpha[target - 1] += 0.1;
		break;


	}


	drawScene();


}
