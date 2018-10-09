#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

struct Dot {
	int x = 0;
	int y = 0;
};

float pi = 3.141592;
Dot DrawVec[5] = { 0, };
int length = 0;
int way = 0;
bool position  = false;



GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);

GLvoid draw_sin();
GLvoid draw_spring();
GLvoid draw_ribon();
GLvoid draw_ractang();
GLvoid draw_circle();
GLvoid draw_zig();
GLvoid just_draw();

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
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutTimerFunc(30, DoTimer, 1);
	glutMainLoop();

}
int spin = 0;

void DoTimer(int value)

{
	Sleep(30);
	glutPostRedisplay();
	if (spin == 1) {
		glTranslatef(400, 0, 0);
		glRotatef(3, 0.0, 1.0, 0.0);
		glTranslatef(-400, 0, 0);
	}
	if (spin == -1) {
		glTranslatef(400, 0, 0);
		glRotatef(-3, 0.0, 1.0, 0.0);
		glTranslatef(-400, 0, 0);
	}
	
	glutTimerFunc(30, DoTimer, 1);
}
int SinX = 200;
int TriangleX = 200;
int TriangleY = 250;
int CircleX = 0;
float scale = 1;
float flag = 0.1;
float degree = 0;
int springX = 200;
int springDegree = 225;
int shapeFlag = 1;
int TriangleFlag = 3;
int currnt = 0;
Dot start, foward;



//윈도우 출력함수
GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_LINE_STRIP);
	glVertex2f(-1, 0);
	glVertex2f(1, 0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 1);
	glVertex2f(0, -1);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	if (way == 0)
		draw_circle();
	if (way == 1)
		draw_sin();
	if (way == 2)
		draw_spring();
	if (way == 3)
		draw_zig();
	if (way == 4)
		just_draw();
	glPopMatrix();



	glFlush();
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -800.0, 800.0);
}

GLvoid draw_sin() {
	glBegin(GL_LINE_STRIP);
	int x = 200;
	while (x < 600) {
		glVertex2f(x, 300 + sin(x *pi / 180) * 60);
		
		x++;
	}
	glEnd();
	
		glPushMatrix();
		glTranslatef(SinX, 300 + sin(SinX *pi / 180) * 60, 0);
		if (scale < 1)
			flag = 0.1;
		if (scale > 1.7)
			flag = -0.1;
		glScalef(scale, scale, 1.0);
		scale += flag;
		glRotatef(-90, 1, 0, 0);
		if(shapeFlag > 0)
			glutSolidCone(10,10,15,15);
		if(shapeFlag < 0)
			glutSolidCube(10);
		glPopMatrix();
		SinX +=3;
		if (SinX > 600)
			SinX = 200;
	
	

	glFlush();
}
GLvoid draw_spring() {
	int x = 200;
	int r = 60;
	int set = -45;
	while (x < 600 + 1) {
		glBegin(GL_LINE_STRIP);
		while (set < 224 + 1) {
			glVertex2f(x + r * cos(set*pi / 180), 300 + r * sin(set*pi / 180));
			set++;
		}
		x += 90;
		set = -45;
		glEnd();
	}

	glPushMatrix();
	glTranslatef(springX + r * cos(springDegree*pi / 180), 300 + r * sin(springDegree*pi / 180),0.0);
	if (scale < 1)
		flag = 0.1;
	if (scale > 1.7)
		flag = -0.1;
	glScalef(scale, scale, 1.0);
	scale += flag;
	glRotatef(-90, 1, 0, 0);
	if (shapeFlag > 0)
		glutSolidCone(10, 10, 15, 15);
	if (shapeFlag < 0)
		glutSolidCube(10);
	glPopMatrix();
	if (springX > 600)
		springX = 200;
	if (springDegree < -45) {
		springX += 90;
		springDegree = 225;
	}
	springDegree -= 3;

	glFlush();

}

GLvoid draw_circle(){
	int set = 0;
	glBegin(GL_LINE_STRIP);
	while (set < 360 + 1) {
		glVertex2f(400 + 200 * cos(set*pi / 180), 300 + 200 * sin(set*pi / 180));
		set++;
		
	}
	glEnd();

	glPushMatrix();
	glTranslatef(400 + 200 * cos(CircleX*pi / 180), 300 + 200 * sin(CircleX*pi / 180),0.0);
	if (scale < 1)
		flag = 0.1;
	if (scale > 1.7)
		flag = -0.1;
	glScalef(scale, scale, 1.0);
	scale += flag;
	glRotatef(-90, 1, 0, 0);
	glRotatef(degree, 0, 1, 0);
	degree += -1;
	if (degree > 360)
		degree = 0;
	if (shapeFlag > 0)
		glutSolidCone(10, 10, 15, 15);
	if (shapeFlag < 0)
		glutSolidCube(10);
	glPopMatrix();
		CircleX++;
	if (CircleX > 360)
		CircleX = 0;
	
	glFlush();
}
GLvoid draw_zig(){
	int x = 200;
	int y = 250;
	int flag_ = 3;
	glBegin(GL_LINE_STRIP);
	while (x < 600 + 1) {
		glVertex2f(x, y);
		if (y > 350)
			flag_ = -3;
		if (y < 250)
			flag_ = 3;
		y += flag_;
		x++;
		
	}

	glEnd();
	glPushMatrix();
	glTranslatef(TriangleX, TriangleY, 0);
	if (scale < 1)
		flag = 0.1;
	if (scale > 1.7)
		flag = -0.1;
	glScalef(scale, scale, 1.0);
	scale += flag;
	glRotatef(-90, 1, 0, 0);
	if (TriangleY > 350)
		TriangleFlag = -3;
	if (TriangleY < 250)
		TriangleFlag = 3;
	if (shapeFlag > 0)
		glutSolidCone(10, 10, 15, 15);
	if (shapeFlag < 0)
		glutSolidCube(10);
	glPopMatrix();
	TriangleX += 1;
	TriangleY += TriangleFlag;
	if (TriangleX > 600) {
		TriangleX = 200;
		TriangleY = 250;
		TriangleFlag = 3;
	}



	glFlush();
}
int count = 1;
GLvoid just_draw(){
	glBegin(GL_LINE_STRIP);
	for (int x = 0; x < length; x++)
		glVertex2f(DrawVec[x].x, DrawVec[x].y);
	glEnd();

	if (position == true) {
		if (currnt == length-1)
			currnt = 0;
		if (currnt < length) {
			start.x = DrawVec[currnt].x;
			start.y = DrawVec[currnt].y;
			foward.x = DrawVec[currnt + 1].x;
			foward.y = DrawVec[currnt + 1].y;
		}

		glPushMatrix();
		glTranslatef(start.x + (foward.x- start.x)*0.1*count, start.y + (foward.y- start.y)*0.1*count, 0);
		count++;
		if (count == 10) {
			count = 0;
			currnt++;
		}
		if (scale < 1)
			flag = 0.1;
		if (scale > 1.7)
			flag = -0.1;
		glScalef(scale, scale, 1.0);
		scale += flag;
		glRotatef(-90, 1, 0, 0);
		if (shapeFlag > 0)
			glutSolidCone(10, 10, 15, 15);
		if (shapeFlag < 0)
			glutSolidCube(10);
		glPopMatrix();
		}
	glFlush();
	}



GLvoid Keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case '0':
		way = 0;
		break;
	case '1':
		way = 1;
		break;
	case '2':
		way = 2;
		break;
	case '3':
		way = 3;
		break;
	case '4':
		way = 4;
		length = 0;
		position = false;
		break;
	case 'T':
		shapeFlag = 1;
		break;
	case 'R':
		shapeFlag = -1;
		break;
	case 'y':
		spin = 1;
		break;
	case 'Y':
		spin = -1;
		break;

	
	}
	drawScene();


}

GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (way == 4 && length < 5) {
			DrawVec[length].x = x * 1.6;
			DrawVec[length++].y = 600 - y * 1.2;
		}
		
		
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		if (way == 4) {
			position = true;
		}
	}
}
