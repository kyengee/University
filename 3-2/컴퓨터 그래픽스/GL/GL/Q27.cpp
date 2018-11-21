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

void main(int argc, char *argv[])
{
	//ÃÊ±âÈ­ÇÔ¼öµé
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
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
int TreeScale = 100;
float TreeFlag = 1;
int x_ = -45, y_ = 30, Z_ = 0;
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
float HumanDG = 0;
float HumanX = 0;
float HumanY = 0;
float HumanZ = 0;
float HumanDG_flag = 1;



void DoTimer(int value)

{
	UP_DG += UP_DG_flag;
	HumanDG += HumanDG_flag = (HumanDG >= 60 ? -3 : (HumanDG <= -60 ? 3 : HumanDG_flag));
	UP_DG = (UP_DG > 90 ? 90 : (UP_DG < 0 ? 0 : UP_DG));
	SPRING_flag = (UP_DG_flag == 3 ? (SPRING_flag >= 1.0 ? 1.0 : SPRING_flag * 1.2) : (SPRING_flag <= 0.15 ? 0.1 : SPRING_flag * 0.9));
	One_DG = (FRONT_DG_flag == 3 ? (One_DG >= 300 ? 300 : One_DG + 10) : (One_DG <= 0 ? 0 : One_DG - 10));
	FRONT_DG += FRONT_DG_flag;
	FRONT_DG = (FRONT_DG > 90 ? 90 : (FRONT_DG < 0 ? 0 : FRONT_DG));
	if ((fabs((moveX + Red_Box) - SphereX) < 170) && (abs((-200 + moveZ) - (SphereZ + 230)) < 165))
	{
		Sphere_pX = fabs(moveX + Red_Box - SphereX) / (float)(moveX + Red_Box - SphereX)*-20.0;
		Sphere_pZ = fabs(-200 + moveZ - (SphereZ + 230)) / (float)(-200 + moveZ - (SphereZ + 230))*-20.0;
	}
	if (moveFlag == false) {
		Red_Box += Red_Box_Dr;
		if (Red_Box > 400)
			Red_Box_Dr = -1;
		if (Red_Box < -400)
			Red_Box_Dr = 1;
	}
	else
		moveFlag = false;
	SphereX += SphereFlagX = (SphereX > 400 ? -1 : (SphereX < -400 ? 1 : SphereFlagX));
	SphereZ += SphereFlagZ = (SphereZ > 1 ? -1 : (SphereZ < -1 ? 1 : SphereFlagZ));
	SphereX += Sphere_pX = Sphere_pX * 0.8;
	SphereZ += Sphere_pZ = Sphere_pZ * 0.8;
	TreeScale += TreeFlag = (TreeScale > 150 ? -1 : (TreeScale < 70 ? 1 : TreeFlag));
	armDG += armFlag = (armDG > 30 ? -1 : (armDG < 0 ? 1 : armFlag));
	NectDG += (NectDG > 360 ? -360 : 1);
	RunningMC += (RunningMC > 500 ? -400 : 1);
	RunningDG += RunningFlag = (RunningDG > 40 ? -5 : (RunningDG < -40) ? 5 : RunningFlag);
	Propel += (Propel > 360 ? -360 : 10);
	smoge += smogeflag = (smoge > 5 ? -2 : (smoge < -5) ? 2 : smogeflag);
	AirDG += (AirDG > 360 ? -360 : 1);

	glutTimerFunc(30, DoTimer, 1);
	glutPostRedisplay();
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	gluLookAt((1000 + Z_)*cos(y_ / 180.0*pi)*cos(x_ / 180.0*pi), (1000 + Z_)*sin(y_ / 180.0*pi), (1000 + Z_)*cos(y_ / 180.0*pi)*sin(x_ / 180.0*pi), 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	glScalef(0.4, 0.4, 0.4);
	glTranslatef(0, 10, 0);
	glPushMatrix();
	glColor3f(1.0, 0.9, 0.9);
	glBegin(GL_TRIANGLES);
	glVertex3f(-500, 0, -500);
	glVertex3f(-500, 0, 0);
	glVertex3f(0, 0, -500);
	glEnd();
	glColor3f(0.9, 1.0, 0.9);
	glBegin(GL_TRIANGLES);
	glVertex3f(500, 0, 500);
	glVertex3f(500, 0, 0);
	glVertex3f(0, 0, 500);
	glEnd();
	glColor3f(0.9, 0.9, 1.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(-500, 0, 500);
	glVertex3f(-500, 0, 0);
	glVertex3f(0, 0, 500);
	glEnd();
	glColor3f(1.0, 1.0, 0.9);
	glBegin(GL_TRIANGLES);
	glVertex3f(500, 0, -500);
	glVertex3f(500, 0, 0);
	glVertex3f(0, 0, -500);
	glEnd();
	glColor3f(0.9, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-500, 0, 0);
	glVertex3f(0, 0, 500);
	glVertex3f(500, 0, 0);
	glVertex3f(0, 0, -500);
	glEnd();
	glPopMatrix();

	glColor3d(0, 0, 0);
	glPushMatrix();
	glTranslated(HumanX, HumanY, HumanZ);
	glPushMatrix();
	//¿Þ´Ù¸®
	glColor3d(1, 0, 0);
	glTranslatef(-20, 20, 0);
	glTranslated(0, 20, 0);
	glRotatef(HumanDG, 1, 0, 0);
	glTranslated(0, -20, 0);
	glScalef(1, 6, 1);
	glutSolidCube(7);
	glPopMatrix();

	glPushMatrix();
	//¿À¸¥´Ù¸®
	glTranslatef(20, 20, 0);
	glTranslated(0, 20, 0);
	glRotatef(-HumanDG, 1, 0, 0);
	glTranslated(0, -20, 0);
	glScalef(1, 6, 1);
	glutSolidCube(7);
	glPopMatrix();
	glTranslatef(0, 60, 0);

	glPushMatrix();
	//¸ö
	glColor3d(0, 1, 0);
	glScalef(5, 6, 4);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	//¿ÞÆÈ
	glColor3f(0.3, 0.7, 1.0);
	glTranslatef(30, 0, 0);
	glTranslated(0, 20, 0);
	glRotatef(HumanDG, 1, 0, 0);
	glTranslated(0, -20, 0);
	glScalef(1, 6, 1);
	glutSolidCube(7);
	glPopMatrix();

	glPushMatrix();
	//¿À¸¥ÆÈ
	glTranslatef(-30, 0, 0);
	glTranslated(0, 20, 0);
	glRotatef(-HumanDG, 1, 0, 0);
	glTranslated(0, -20, 0);
	glScalef(1, 6, 1);
	glutSolidCube(7);
	glPopMatrix();

	glTranslatef(0, 40, 0);
	glColor3f(1, 1, 0);
	glutSolidCube(25);
	glTranslatef(0, 0, 5);
	glColor3f(1, 1, 1);
	glutSolidCone(7, 15, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-400, 0, -400);
	Draw_RunningMachine();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(400, 0, -400);
	Draw_IronBar();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(400, 0, 400);
	Draw_Pushup();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-400, 0, 400);
	Draw_Tree();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 200, 0);
	glRotated(-1 * AirDG, 0, 1, 0);
	glTranslatef(0, 0, -400);
	glScalef(0.7, 0.7, 0.7);
	Draw_Airplane();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, 400, 0);
	glTranslatef(0, 0, 200);
	glRotatef(UP_DG, 1, 0, 0);
	glTranslatef(0, 0, -200);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 0);
	glVertex3f(200, 0, 200);
	glColor3f(1, 1, 1);
	glVertex3f(200, 0, -200);
	glColor3f(0, 1, 1);
	glVertex3f(-200, 0, -200);
	glColor3f(0, 1, 0);
	glVertex3f(-200, 0, 200);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(200, 200, 0);
	glRotatef(-90, 0, 0, 1);
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex3f(200, 0, 200);
	glColor3f(1, 0, 1);
	glVertex3f(200, 0, -200);
	glColor3f(1, 1, 1);
	glVertex3f(-200, 0, -200);
	glColor3f(1, 1, 0);
	glVertex3f(-200, 0, 200);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200, 200, 0);
	glRotatef(90, 0, 0, 1);
	glBegin(GL_POLYGON);
	glColor3f(0, 1, 0);
	glVertex3f(200, 0, 200);
	glColor3f(0, 1, 1);
	glVertex3f(200, 0, -200);
	glColor3f(0, 0, 1);
	glVertex3f(-200, 0, -200);
	glColor3f(0, 0, 0);
	glVertex3f(-200, 0, 200);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 200, -200);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, 0, -200);
	glRotatef(-FRONT_DG, 1, 0, 0);
	glTranslatef(0, 0, 200);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex3f(200, 0, 200);
	glColor3f(1, 0, 1);
	glVertex3f(200, 0, -200);
	glColor3f(0, 0, 1);
	glVertex3f(-200, 0, -200);
	glColor3f(0, 1, 1);
	glVertex3f(-200, 0, 200);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 200, 200);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex3f(200, 0, 200);
	glColor3f(1, 1, 0);
	glVertex3f(200, 0, -200);
	glColor3f(0, 1, 0);
	glVertex3f(-200, 0, -200);
	glColor3f(0, 0, 0);
	glVertex3f(-200, 0, 200);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0);
	glRotatef(180, 1, 0, 0);
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 1);
	glVertex3f(200, 0, 200);
	glColor3f(1, 0, 0);
	glVertex3f(200, 0, -200);
	glColor3f(0, 0, 0);
	glVertex3f(-200, 0, -200);
	glColor3f(0, 0, 1);
	glVertex3f(-200, 0, 200);
	glEnd();
	glPopMatrix();







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

	switch (key) {
	case 'i':
		if (glIsEnabled(GL_DEPTH_TEST)) {
			glDisable(GL_DEPTH_TEST);
		}
		else
			glEnable(GL_DEPTH_TEST);
		break;
	case 'o':
		if (glIsEnabled(GL_CULL_FACE)) {
			glDisable(GL_CULL_FACE);
		}
		else
			glEnable(GL_CULL_FACE);
		break;
	case 'p':
		if (isFlat == true) {
			isFlat = false;
			glShadeModel(GL_SMOOTH);
		}
		else {
			isFlat = true;
			glShadeModel(GL_FLAT);
		}
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
		HumanZ++;
		HumanDG++;
		break;
	case '.':
		HumanZ--;
		HumanDG++;
		break;
	case ',':
		HumanX++;
		HumanDG++;
		break;
	case '/':
		HumanX++;
		HumanDG++;
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
	//»ç¶÷
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
	//ÆÈ±×¸®±â
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