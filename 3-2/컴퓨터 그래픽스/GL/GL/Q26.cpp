#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
float pi = 3.141592;



float SpinDG = 0;
typedef struct Box {
	float x = 0;
	float xFlag = 0;
	float y = 0;
	float yFlag = 0;
	float z = 0;
	int r = 0;
	void update() {
		int temp = abs((int)SpinDG);
		int flag = (SpinDG >= 0 ? +1 : -1);
		int compare = ((temp % 361) / 90 + 1) * flag;
		switch (compare) {
		case 1:
			xFlag-= 5;
			yFlag-= 5;
			break;
		case 2:
			xFlag-= 5;
			yFlag+= 5;
			break;
		case 3:
			xFlag+= 5;
			yFlag+= 5;
			break;
		case 4:
			xFlag+= 5;
			yFlag-= 5;
			break;
		case -4:
			xFlag-= 5;
			yFlag-= 5;
			break;
		case -3:
			xFlag-= 5;
			yFlag+= 5;
			break;
		case -2:
			xFlag+= 5;
			yFlag+= 5;
			break;
		case -1:
			xFlag+= 5;
			yFlag-= 5;
			break;
		}
		x += xFlag;
		y += yFlag;
		x = (x > 200 - r ? 200 - r : (x < -200 + r ? -200 + r : x));
		y = (y > 200 - r ? 200 - r : (y < -200 + r ? -200 + r : y));
		xFlag = (xFlag > 50 ? 50 : (xFlag < -50 ? -50 : xFlag));
		yFlag = (yFlag > 50 ? 50 : (yFlag < -50 ? -50 : yFlag));

	}
};



typedef struct Ball
{
	float x = rand() % 200 * (rand() % 2 == 1 ? -1 : 1);
	float y = rand() % 200 * (rand() % 2 == 1 ? -1 : 1);
	float z = rand() % 200 * (rand() % 2 == 1 ? -1 : 1);
	float xDR = rand() % 15 * (rand() % 2 == 1 ? -1 : 1);
	float yDR = rand() % 15 * (rand() % 2 == 1 ? -1 : 1);
	float zDR = rand() % 15 * (rand() % 2 == 1 ? -1 : 1);

	void update() {
		x += xDR;
		y += yDR;
		z += zDR;
	}

	void colide() {
		xDR = (x >= 190 ? xDR * -1 : (x <= -190 ? xDR * -1 : xDR));
		yDR = (y >= 190 ? yDR * -1 : (y <= -190 ? yDR * -1 : yDR));
		zDR = (z >= 190 ? zDR * -1 : (z <= -190 ? zDR * -1 : zDR));
	}
};

Ball Balls[5] = { 0, };
int BallCount = 0;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid MouseMove(int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
void Draw_RunningMachine();
void Draw_IronBar();
void Draw_Pushup();
void Draw_Tree();
void Draw_Airplane();
void Draw_Box();

void DoTimer(int value);

int Red_Box = 0;
int Red_Box_Dr = 1;
int Red_Box_Y = 0;
int Green_Box_X = 0;
int Green_Box_Y = 0;
int Blue_Box_X = 0;
int Blue_Box_Z = 0;
Box Boxs[3] = { 0, };

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
	glutPassiveMotionFunc(MouseMove);
	glutKeyboardFunc(Keyboard);
	Boxs[0].z = -100; Boxs[0].r = 30;
	Boxs[1].r = 20;
	Boxs[2].z = 100; Boxs[2].r = 10;
	glutTimerFunc(30, DoTimer, 1);
	glutMainLoop();

}
int TreeScale = 100;
float TreeFlag = 1;
int x_ = -90, y_ = 0, Z_ = -200;
int armDG = 0;
int armFlag = 1;
int NectDG = 0;
int RunningMC = 0;
int RunningDG = 0;
int RunningFlag = 5;
int Propel = 0;
int smoge = 0;
int smogeflag = 1;
int AirDG = 0;
int moveX = 0;
int moveZ = 0;
bool moveFlag = false;
int SphereX = 0;
int SphereFlagX = 1;
int SphereZ = 0;
int SphereFlagZ = 0;
int Sphere_pX = 0;
int Sphere_pZ = 0;
int UP_DG = 0;
int UP_DG_flag = -3;
int FRONT_DG = 0;
int FRONT_DG_flag = -3;
int SPRING = 0;
float SPRING_flag = 0.1;
float One_DG = 0;
bool isFlat = true;
float SpinX = 0;




void DoTimer(int value)

{
	UP_DG += UP_DG_flag;
	UP_DG = (UP_DG > 90 ? 90 : (UP_DG < 0 ? 0 : UP_DG));
	SPRING_flag = (UP_DG_flag == 3 ? (SPRING_flag >= 1.0 ? 1.0 : SPRING_flag * 1.2) : (SPRING_flag <= 0.15 ? 0.1 : SPRING_flag * 0.9));
	One_DG = (FRONT_DG_flag == 3 ? (One_DG >= 300 ? 300 : One_DG + 10) : (One_DG <= 0 ? 0 : One_DG - 10));
	FRONT_DG += FRONT_DG_flag;
	FRONT_DG = (FRONT_DG > 90 ? 90 : (FRONT_DG < 0 ? 0 : FRONT_DG));

	glutTimerFunc(30, DoTimer, 1);
	glutPostRedisplay();
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_FLAT);

	glPushMatrix();
	glRotatef(SpinDG, 0, 0, 1);
	glTranslatef(0, -200, +30);
	gluLookAt((1000 + Z_)*cos(y_ / 180.0*pi)*cos(x_ / 180.0*pi), (1000 + Z_)*sin(y_ / 180.0*pi), (1000 + Z_)*cos(y_ / 180.0*pi)*sin(x_ / 180.0*pi), 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);


	glPushMatrix();
	glTranslatef(0, 400, 0);
	glTranslatef(0, 0, 200);
	glRotatef(UP_DG, 1, 0, 0);
	glTranslatef(0, 0, -200);
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(200, 0, 200);
	glVertex3f(200, 0, -200);
	glVertex3f(-200, 0, -200);
	glVertex3f(-200, 0, 200);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(200, 200, 0);
	glRotatef(-90, 0, 0, 1);
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(200, 0, 200);
	glVertex3f(200, 0, -200);
	glVertex3f(-200, 0, -200);
	glVertex3f(-200, 0, 200);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200, 200, 0);
	glRotatef(90, 0, 0, 1);
	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(200, 0, 200);
	glVertex3f(200, 0, -200);
	glVertex3f(-200, 0, -200);
	glVertex3f(-200, 0, 200);
	glEnd();
	glPopMatrix();

	

	glPushMatrix();
	glTranslatef(0, 200, 200);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(200, 0, 200);
	glVertex3f(200, 0, -200);
	glVertex3f(-200, 0, -200);
	glVertex3f(-200, 0, 200);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0);
	glRotatef(180, 1, 0, 0);
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(200, 0, 200);
	glVertex3f(200, 0, -200);
	glVertex3f(-200, 0, -200);
	glVertex3f(-200, 0, 200);
	glEnd();
	glPopMatrix();


	for (int i = 0; i < BallCount; i++) {
		Balls[i].colide();
		Balls[i].update();
		glColor3f(0, 0, 1);
		glPushMatrix();
		glTranslatef(Balls[i].x, 200 + Balls[i].y, Balls[i].z);
		glutSolidSphere(10, 15, 15);
		glPopMatrix();
	}

	for (int i = 0; i < 3; i++) {
		Boxs[i].update();
		glColor3f(1, 0, 0);
		glPushMatrix();
		glTranslatef(-Boxs[i].x, 200 +Boxs[i].y, Boxs[i].z);
		glutSolidCube(Boxs[i].r);
		glPopMatrix();
	}



	glPopMatrix();

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 2000.0);
	glMatrixMode(GL_MODELVIEW);
}

GLvoid Keyboard(unsigned char key, int x, int y) {
	Ball newBall;
	switch (key) {
	case 'B':
		if (BallCount > 4)
			BallCount = 4;
		Balls[BallCount % 5] = newBall;
		BallCount++;
		break;

	case 'a':
		x_--;
		break;
	case 'd':
		x_++;
		break;
	case 'w':
		y_++;
		break;
	case 's':
		y_--;
		break;

	case '1':
		Red_Box_Y += 3;
		if (Red_Box_Y > 90)
			Red_Box_Y = 90;
		break;
	case '!':
		Red_Box_Y -= 3;
		if (Red_Box_Y < -90)
			Red_Box_Y = -90;
		break;
	case '2':
		Green_Box_X += 3;
		if (Green_Box_X > 90)
			Green_Box_X = 90;
		break;
	case '@':
		Green_Box_X -= 3;
		if (Green_Box_X < -90)
			Green_Box_X = -90;
		break;
	case '3':
		Green_Box_Y += 3;
		if (Green_Box_Y > 90)
			Green_Box_Y = 90;
		break;
	case '#':
		Green_Box_Y -= 3;
		if (Green_Box_Y < -90)
			Green_Box_Y = -90;
		break;
	case '4':
		Blue_Box_X += 3;
		if (Blue_Box_X > 90)
			Blue_Box_X = 90;
		break;
	case '$':
		Blue_Box_X -= 3;
		if (Blue_Box_X < -90)
			Blue_Box_X = -90;
		break;
	case '5':
		Blue_Box_Z += 3;
		if (Blue_Box_Z > 90)
			Blue_Box_Z = 90;
		break;
	case '%':
		Blue_Box_Z -= 3;
		if (Blue_Box_Z < -90)
			Blue_Box_Z = -90;
		break;

	case 'l':
		moveZ += 5;
		moveFlag = true;
		break;
	case '.':
		moveZ -= 5;
		moveFlag = true;
		break;
	case ',':
		moveX += 5;
		break;
	case '/':
		moveX -= 5;
		break;
	case '+':
		Z_ += 5;
		break;
	case '=':
		Z_ -= 5;
		break;

	case 'z':
		if (UP_DG_flag == 3)
			UP_DG_flag = -3;
		else if (UP_DG_flag == -3)
			UP_DG_flag = +3;
		break;

	case 'x':
		if (FRONT_DG_flag == 3)
			FRONT_DG_flag = -3;
		else if (FRONT_DG_flag == -3)
			FRONT_DG_flag = +3;
		break;


	}
	glutPostRedisplay();


}

GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		
	}




}

GLvoid MouseMove(int x, int y) {
	if (SpinX == 0)
		SpinX = x;
	if (SpinX != x) {
		SpinDG += SpinX - x;
		SpinX = x;
	}
}


void Draw_RunningMachine() {
	glPushMatrix();
	glTranslatef(60, 0, 0);
	glRotated(180, 0, 1, 0);
	glColor3f(0.9, 0.2, 0.2);
	glScalef(1, 1, 20);
	for (int i = 0; i < 10; i++) {
		glPushMatrix();
		glTranslatef((RunningMC + i * 11) % 120, 0, 0);
		glutSolidCube(5);
		glPopMatrix();
	}
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.9, 0, 0);
	glTranslatef(0, 0, 50);
	glScalef(7, 1, 1);
	glutSolidTorus(4, 5, 15, 15);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, -50);
	glScalef(7, 1, 1);
	glutSolidTorus(4, 5, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(50, 0, 0);
	glPushMatrix();
	glTranslatef(0, 50, -50);
	glScalef(1, 20, 1);
	glutSolidCube(5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 50, 50);
	glScalef(1, 20, 1);
	glutSolidCube(5);
	glPopMatrix();
	glTranslatef(0, 100, 0);
	glScalef(1, 5, 20);
	glutSolidCube(5);
	glPopMatrix();
	//사람
	glPushMatrix();
	glColor3f(0.9, 0.9, 0.2);
	glTranslatef(0, 80, 0);
	glScalef(3, 5, 4);
	glutSolidCube(15);
	glPopMatrix();
	glTranslatef(0, 50, 0);
	glPushMatrix();
	glTranslated(0, 0, 20);
	glRotatef(RunningDG, 0, 0, 1);
	glTranslated(0, -20, 0);
	glScalef(1, 10, 1);
	glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, -20);
	glRotatef(-1 * RunningDG, 0, 0, 1);
	glTranslated(0, -20, 0);
	glScalef(1, 10, 1);
	glutSolidCube(5);
	glPopMatrix();
}

void Draw_IronBar() {
	glPushMatrix();
	glColor3f(0.2, 0.9, 0.2);
	glTranslatef(0, 50, 0);
	glPushMatrix();
	glTranslatef(40, 0, 0);
	glScalef(1, 10, 1);
	glutSolidCube(10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-40, 0, 0);
	glScalef(1, 10, 1);
	glutSolidCube(10);
	glPopMatrix();
	glTranslatef(0, 50, 0);
	glPushMatrix();
	glScalef(15, 1, 1);
	glutSolidCube(5);
	glPopMatrix();
	glColor3f(0.2, 0.2, 0.9);
	glRotatef(NectDG, 1, 0, 0);
	glTranslatef(0, -30, 0);
	glPushMatrix();
	glTranslatef(20, 0, 0);
	glScalef(1, 20, 1);
	glutSolidCube(3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-20, 0, 0);
	glScalef(1, 20, 1);
	glutSolidCube(3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -20, 0);
	glutSolidSphere(10, 15, 15);
	glPopMatrix();
	glTranslatef(0, -40, 0);
	glScalef(4, 2, 2);
	glutSolidCube(10);
	glPopMatrix();
}

void Draw_Pushup() {
	glPushMatrix();
	glColor3f(0.3, 0.3, 0);
	glTranslatef(0, 10, 0);
	glPushMatrix();
	glTranslatef(35, 0, 50);
	glScalef(1, 4, 1);
	glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-35, 0, 50);
	glScalef(1, 4, 1);
	glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(35, 0, -50);
	glScalef(1, 4, 1);
	glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-35, 0, -50);
	glScalef(1, 4, 1);
	glutSolidCube(5);
	glPopMatrix();
	glTranslatef(0, 10, 0);
	glPushMatrix();
	glScalef(15, 1, 20);
	glutSolidCube(5);
	glPopMatrix();
	glTranslatef(0, 20, 0);

	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	glScalef(7, 3, 15);
	glutSolidCube(5);
	glPopMatrix();
	glTranslatef(0, 0, -30);
	glutSolidSphere(30, 15, 15);
	glTranslatef(0, 0, 15);
	//팔그리기
	glPushMatrix();
	glColor3f(0, 0.9, 0.9);
	glTranslated(15, 0, 0);
	glRotatef(-1 * armDG, 0, 0, 1);
	glTranslatef(0, 10, 0);
	glPushMatrix();
	glScalef(1, 8, 1);
	glutSolidCube(5);
	glPopMatrix();
	glTranslatef(0, 20, 0);
	glRotatef(2 * armDG, 0, 0, 1);
	glTranslatef(0, 20, 0);
	glPushMatrix();
	glScalef(1, 8, 1);
	glutSolidCube(5);
	glPopMatrix();
	glTranslatef(0, 20, 0);
	glRotated(-1 * armDG, 0, 0, 1);
	glColor3f(1, 1, 0.2);
	glTranslatef(-15, 0, 0);
	glTranslatef(30, 0, 0);
	glutSolidSphere(10, 15, 15);
	glTranslatef(-60, 0, 0);
	glutSolidSphere(10, 15, 15);
	glTranslatef(30, 0, 0);
	glScalef(20, 1, 1);
	glutSolidCube(3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0.9, 0.9);
	glTranslated(-15, 0, 0);
	glRotatef(armDG, 0, 0, 1);
	glTranslatef(0, 10, 0);
	glPushMatrix();
	glScalef(1, 8, 1);
	glutSolidCube(5);
	glPopMatrix();
	glTranslatef(0, 20, 0);
	glRotatef(-2 * armDG, 0, 0, 1);
	glTranslatef(0, 20, 0);
	glPushMatrix();
	glScalef(1, 8, 1);
	glutSolidCube(5);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void Draw_Tree() {

	glPushMatrix();
	glColor3f(0.2, 0.2, 0);
	glTranslatef(0, 100, 0);
	glScalef(1.0, 20.0, 1.0);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0.9, 0);
	glTranslatef(0.0, 200.0, 0.0);
	glutWireSphere(TreeScale, 15, 15);
	glPopMatrix();
}

void Draw_Airplane() {
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glRotatef(-90, 0, 1, 0);
	glutSolidCone(30, 150, 15, 15);
	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotatef(Propel, 0, 0, 1);
	glScalef(30, 5, 1);
	glutSolidCube(5);
	glPopMatrix();
	glRotatef(180, 0, 1, 0);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCone(10, 10, 15, 15);
	glTranslatef(0, 0, -50);
	glPushMatrix();
	glColor3f(0, 1.0, 1.0);
	glScalef(50, 1, 10);
	glutSolidCube(5);
	glPopMatrix();
	glTranslatef(0, 0, -90);
	glutSolidCube(30);
	glTranslatef(0, 0, -70);
	glColor3f(0.5, 0.5, 0.5);
	glutSolidSphere(40 + smoge, 15, 15);
	glTranslatef(0, 0, -80);
	glutSolidSphere(20 - smoge * 0.8, 15, 15);
	glTranslatef(0, 0, -50);
	glutSolidSphere(10 + smoge * 0.7, 15, 15);
	glTranslatef(0, 0, -40);
	glutSolidSphere(5 - smoge * 0.6, 15, 15);
	glTranslatef(0, 0, -30);
	glutSolidSphere(2 + smoge * 0.5, 15, 15);
	glPopMatrix();
}

void Draw_Box() {
	glPushMatrix();
	glTranslatef(Red_Box, 0.0, 0.0);
	glRotatef(Red_Box_Y, 0.0, 1.0, 0.0);
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glScalef(4.0, 3.0, 3.0);
	glutSolidCube(50);
	glColor3f(1.0, 1.0, 1.0);
	glutWireCube(50);
	glPopMatrix();

	glTranslatef(0.0, 50.0, 0.0);
	glRotatef(Green_Box_Y, 0.0, 1.0, 0.0);
	glRotatef(Green_Box_X, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 100.0, 0.0);
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glScalef(1.5, 4.0, 1.5);
	glutSolidCube(40);
	glColor3f(1.0, 1.0, 1.0);
	glutWireCube(40);
	glPopMatrix();

	glTranslatef(0.0, 50.0, 0.0);
	glRotatef(Blue_Box_X, 1.0, 0.0, 0.0);
	glRotatef(Blue_Box_Z, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 100.0, 0.0);
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glScalef(0.5, 4.0, 0.5);
	glutSolidCube(40);
	glColor3f(1.0, 1.0, 1.0);
	glutWireCube(40);
	glPopMatrix();
	glPopMatrix();
}