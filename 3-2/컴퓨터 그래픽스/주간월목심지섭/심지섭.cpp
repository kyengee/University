#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
float pi = 3.141592;
int mouse = 0;

typedef struct Dot {
	int x = 0;
	int y = 0;
};

Dot First, Second;

typedef struct STAR {
	Dot dot[100];
	Dot togo[100];
	int count = 0;
	int rotate[100];
	float scale[100] = { 0, };
	int flag[100] = { 0, };



	void add(float x,float y) {
		dot[count].x = x;
		dot[count].y = y;
		togo[count].y = rand() % 400 + 20;
		togo[count].x = rand() % 800 ;
		rotate[count] = 0;
		count++;
	}
	void update() {
		for (int i = 0; i < count; i++) {
			if (dot[i].x != togo[i].x && dot[i].x != togo[i].x) {
				dot[i].x += (togo[i].x - dot[i].x) / 50.0;
				dot[i].y += (togo[i].y - dot[i].y) / 50.0;
			}
			if (abs(togo[i].x - dot[i].x) < 3)
				dot[i].x = togo[i].x;
			if (abs(togo[i].y - dot[i].y) < 3)
				dot[i].y = togo[i].y;
			rotate[i]++;
			if (rotate[i] > 360)
				rotate[i] = 0;
				
			if (scale[i] == 0)
				scale[i] = 1;
			if (flag[i] == 0)
				scale[i] += 0.1;
			if(flag[i] == 1)
				scale[i] -= 0.1;
			if (scale[i] <= 0.5)
				flag[i] = 0;
			if (scale[i] >= 1.5)
				flag[i] = 1;


		}
	}

	void draw() {
		for (int i = 0; i < count; i++) {
			glPushMatrix();
			glTranslatef(dot[i].x, dot[i].y, 0);
			glScalef(scale[i], scale[i], 1);
			glRotatef(rotate[i], 0, 0, 1);
			glColor3d((rand() % 500+500) * 0.001, (rand() % 500+500) * 0.001, (rand() % 200+200) * 0.001);
			glBegin(GL_TRIANGLES);
			glVertex2f(0, 50);
			glVertex2f(40, -30);
			glVertex2f(-40, -30);
			glVertex2f(0, -50);
			glVertex2f(-40, 30);
			glVertex2f(40, 30);
			glEnd();
			glColor3f(1.0, 1.0, 1.0);
			glPopMatrix();
		}
	}
};

typedef struct Right {
	Dot dot[100];
	int count = 0;
	int grap = 1000;
	int stati_c[100] = { 0, };

	void add(Dot dd) {
		dot[count] = dd;
		count++;
	}

	void update() {
		for (int i = 0; i < count; i++) {
			if (stati_c[i] == 0) {
				if (dot[i].x < 780)
					dot[i].x++;
				if (dot[i].y > 20)
					dot[i].y--;
				if (grap == i) {
					dot[i].x = Second.x;
					dot[i].y = Second.y;
				}
				if (dot[i].x >= 780 && dot[i].y <= 20) {
					dot[i].x = 800 - (i * 20) % 400;
					dot[i].y = (i * 20) / 400 * 20;
					stati_c[i] = i;
				}
			}
		}
	}

	void draw() {
		for (int i = 0; i < count; i++) {
			glPushMatrix();
			glTranslatef(dot[i].x, dot[i].y, 0);
			if (stati_c[i] % 2 == 1) 
				glRotatef(180, 0, 0, 1);
			if(stati_c[i] != 0)
				glBegin(GL_LINE_LOOP);
			else
				glBegin(GL_TRIANGLES);
			glVertex2f(10, 10);
			glVertex2f(10, -30);
			glVertex2f(-30, 10);
			glEnd();
			glPopMatrix();
		}

	}


};

typedef struct Left {
	Dot dot[100];
	int count = 0;
	int grap = 1000;
	int stati_c[100] = { 0, };

	void add(Dot dd) {
		dot[count] = dd;
		count++;
	}

	void update() {
		for (int i = 0; i < count; i++) {
			if (stati_c[i] == 0) {
				if (dot[i].x > 20)
					dot[i].x--;
				if (dot[i].y > 20)
					dot[i].y--;
				if (grap == i) {
					dot[i].x = Second.x;
					dot[i].y = Second.y;
				}
				if (dot[i].x <= 20 && dot[i].y <= 20) {
					dot[i].x = (i * 20) % 400;
					dot[i].y = (i * 20) / 400 * 20;
					stati_c[i] = i;
				}
			}
		}
	}
	void draw() {
		for (int i = 0; i < count; i++) {
			glPushMatrix();
			glTranslatef(dot[i].x, dot[i].y, 0);
			if (stati_c[i] % 2 == 1) 
				glRotatef(180, 0, 0, 1);
			if (stati_c[i] != 0)
				glBegin(GL_LINE_LOOP);
			else
				glBegin(GL_TRIANGLES);
			glVertex2f(-10, -10);
			glVertex2f(-10, 30);
			glVertex2f(30, -10);
			glEnd();
			glPopMatrix();
		}

	}


};

typedef struct Target {
	Dot dot;
	double Dgree;
	Target() {
		dot.x = rand() % 800;
		dot.y = rand() % 130 + 470;
		Dgree = rand() % 360;
	}
	void update() {
		dot.x++;
		if (dot.x >= 800)
			dot.x = 0;
		Dgree++;
		if (Dgree >= 360)
			Dgree = 0;
	}

	void draw() {
		glPushMatrix();
		glTranslatef(dot.x, dot.y, 0);
		glRotatef(Dgree, 0, 0, 1);
		glBegin(GL_LINE_LOOP);
		glVertex2f(0, 20);
		glVertex2f(20, -20);
		glVertex2f(-20, -20);
		glEnd();
		glPopMatrix();

	}

};

typedef struct Rect {
	Dot dot;
	double Dgree;
	Rect() {
		dot.x = rand() % 800;
		dot.y = rand() % 450;
		Dgree = 0;
	}
	void update() {
		dot.y++;
		if (dot.y >= 420)
			dot.y = 0;
	}

	void draw() {
		glPushMatrix();
		glTranslatef(dot.x, dot.y, 0);
		glRotatef(Dgree, 0, 0, 1);
		glBegin(GL_LINE_LOOP);
		glVertex2f(-30, -30);
		glVertex2f(-30, +30);
		glVertex2f(+30, +30);
		glVertex2f(+30, -30);
		glEnd();
		glPopMatrix();

	}

};

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
void Motion(int x, int y);

void DoTimer(int value);

Target target[10] = {};
Rect rect[10] = {};
Right right;
Left left;
STAR star;

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
int LengthX, LengthY;

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	for (int i = 0; i < 10; i++) {
		target[i].update();
		rect[i].update();
		target[i].draw();
		rect[i].draw();
	}
	switch (mouse)
	{
	case 1:
		if (right.grap > 999 && left.grap > 999) {
			glBegin(GL_LINE_LOOP);
			glVertex2f(First.x, First.y);
			glVertex2f(Second.x, Second.y);
			glEnd();
		}
		break;
	case 2:
		if (right.grap > 999 && left.grap > 999) {
			glBegin(GL_LINE_LOOP);
			glVertex2f(First.x, First.y);
			glVertex2f(Second.x, Second.y);
			glEnd();
			LengthX = First.x - Second.x;
			LengthY = First.y - Second.y;
			float area, AB;
			if (LengthX != 0 && LengthY != 0)
			if (abs(LengthY / LengthX) < 2 && abs(LengthY / LengthX) > 0.5) {
				for (int i = 0; i < 10; i++) {
					area = abs((First.x - rect[i].dot.x) * (Second.y - rect[i].dot.y) - (First.y - rect[i].dot.y) * (Second.x - rect[i].dot.x));
					AB = sqrt((First.x - Second.x) * (First.x - Second.x) + (First.y - Second.y) * (First.y - Second.y));
					if (area / AB < 20) {
						left.add(rect[i].dot);
						right.add(rect[i].dot);
						rect[i].dot.y = 0;

					}

				}
			}
			mouse = 0;
		}
		else {
			left.grap = 1000;
			right.grap = 1000;
			mouse = 0;
		}
		break;
	default:
		break;
	}
	right.update();
	left.update();
	right.draw();
	left.draw();
	star.update();
	star.draw();

	

	glutSwapBuffers();

}


GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -100, 100);
	glMatrixMode(GL_MODELVIEW);
}

GLvoid Keyboard(unsigned char key, int x, int y) {

	switch (key) {



	}
	glutPostRedisplay();


}

GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (mouse == 0) {
			First.x = x * 1.6;
			First.y = 600 - y * 1.2;
			mouse++;
		}
		if (mouse == 1) {
			Second.x = x * 1.6;
			Second.y = 600 - y * 1.2;
		}
		for (int i = 0; i < right.count; i++) {
			if (abs((long)(right.dot[i].x - (x * 1.6))) < 15 && abs((long)(right.dot[i].y - (600 - y * 1.2))) < 15)
				right.grap = i;
		}
		for (int i = 0; i < left.count; i++) {
			if (abs((long)(left.dot[i].x - (x * 1.6))) < 15 && abs((long)(left.dot[i].y - (600 - y * 1.2))) < 15)
				left.grap = i;
		}
		
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		if (mouse == 1) {
			Second.x = x * 1.6;
			Second.y = 600 - y * 1.2;
			mouse++;
		}

		if (left.grap < 999) {
			for (int i = 0; i < 10; i++) {
				if (abs(target[i].dot.x - left.dot[left.grap].x) < 10 && abs(target[i].dot.y - left.dot[left.grap].y) < 10) {
					star.add(target[i].dot.x, target[i].dot.y);
					target[i].dot.x = 0;
					left.dot[left.grap].y = 0;
				}
			}
		}

		if (right.grap < 999) {
			for (int i = 0; i < 10; i++) {
				if (abs(target[i].dot.x - right.dot[right.grap].x) < 10 && abs(target[i].dot.y - right.dot[right.grap].y) < 10) {
					star.add(target[i].dot.x, target[i].dot.y);
					target[i].dot.x = 0;
					right.dot[right.grap].y = 0;
				}
			}
		}
	}



}

void Motion(int x, int y) {
	if (mouse == 1) {
		Second.x = x * 1.6;
		Second.y = 600 - y * 1.2;
	}
}

