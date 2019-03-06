#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
float pi = 3.141592;
int mode = 3;
float w_, h_;
int Devil = 0;
int Devil2 = 0;
int Devil3 = 0;
int Grap = 0;
int view = 1;
int wether = 1;
float snow[34][34] = { 0, };

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
void Motion(int x, int y);
void Robot();
void Robot2();
void iscolide();

void DoTimer(int value);

GLfloat ctrlpoints[20][3] = { 0, };
GLfloat copypoints[20][3] = { 0, };
GLfloat modelPoint1[20][3] = { 0, };
GLfloat modelPoint2[20][3] = { 0, };
int ctrlcount = 0;
int x_ = 90, y_ = 20, Z_ = 0;
float t = 0;
float t2 = 0.07;
float t3 = 0.14;

float HumanX = 0;
float HumanY = 0;
float HumanZ = 0;
float HumanDG = 0;
float HumanDG_flag = 6;
float HumanRotate = 180;
float xHumanX = 3;
float xHumanX_ = 200;
float xHumanZ_ = -490;
float xHumanZ = 3;
float xHumanDG = 0;
float xHumanDG_flag = 6;
float xHumanRotate = 0;
int Humanmove = 0;



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
	
	if (snow[rand() % 34][rand() % 34] == 0 && wether > 1)
		snow[rand() % 34][rand() % 34] = 500;

	if (Humanmove > 0) {
		HumanDG += HumanDG_flag = (HumanDG >= 60 ? -6 : (HumanDG <= -60 ? 6 : HumanDG_flag));
		Humanmove--;

	}
	else
		HumanDG = 0;

	if (Grap == 0) {
		xHumanDG += xHumanDG_flag = (xHumanDG >= 60 ? -6 : (xHumanDG <= -60 ? 6 : xHumanDG_flag));
		xHumanX_ += xHumanX;
		xHumanZ_ += xHumanZ;
		iscolide();
	}
	else {
		xHumanX_ = HumanX + 50 * cos(Grap / 180.0*pi);
		xHumanZ_ = HumanZ + 500 + 50 * sin(Grap / 180.0*pi);
		if (Grap >= 361)
			Grap = 1;
		Grap++;
	}




	glutTimerFunc(30, DoTimer, 1);
	glutPostRedisplay();
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);

	glPushMatrix();


	switch (mode)
	{
	case 1:
		gluLookAt(0 ,875 ,0 , 0.0 , -100.0 , 0.0, 0.0, 0.0, -1.0);
		break;

	case 2:
		gluLookAt(0, 0, 875, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
		break;
	case 3:
		if(view == 1)gluLookAt((1000 + Z_)*cos(y_ / 180.0*pi)*cos(x_ / 180.0*pi), (1000 + Z_)*sin(y_ / 180.0*pi), (1000 + Z_)*cos(y_ / 180.0*pi)*sin(x_ / 180.0*pi), 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
		else if (view == 3) {
			if (Devil3 >= 0) {
				gluLookAt(ctrlpoints[Devil2][0] * pow(1 - t2, 3) + 3 * ctrlpoints[Devil2 + 1][0] * t2*pow(1 - t2, 2) + 3 * ctrlpoints[Devil2 + 2][0] * pow(t2, 2)*(1 - t2) + ctrlpoints[Devil2 + 3][0] * pow(t2, 3),
					ctrlpoints[Devil2][1] * pow(1 - t2, 3) + 3 * ctrlpoints[Devil2 + 1][1] * t2*pow(1 - t2, 2) + 3 * ctrlpoints[Devil2 + 2][1] * pow(t2, 2)*(1 - t2) + ctrlpoints[Devil2 + 3][1] * pow(t2, 3) + 50,
					ctrlpoints[Devil2][2] * pow(1 - t2, 3) + 3 * ctrlpoints[Devil2 + 1][2] * t2*pow(1 - t2, 2) + 3 * ctrlpoints[Devil2 + 2][2] * pow(t2, 2)*(1 - t2) + ctrlpoints[Devil2 + 3][2] * pow(t2, 3),
					ctrlpoints[Devil3][0] * pow(1 - t3, 3) + 3 * ctrlpoints[Devil3 + 1][0] * t3*pow(1 - t3, 2) + 3 * ctrlpoints[Devil3 + 2][0] * pow(t3, 2)*(1 - t3) + ctrlpoints[Devil3 + 3][0] * pow(t3, 3),
					ctrlpoints[Devil3][1] * pow(1 - t3, 3) + 3 * ctrlpoints[Devil3 + 1][1] * t3*pow(1 - t3, 2) + 3 * ctrlpoints[Devil3 + 2][1] * pow(t3, 2)*(1 - t3) + ctrlpoints[Devil3 + 3][1] * pow(t3, 3) + 50,
					ctrlpoints[Devil3][2] * pow(1 - t3, 3) + 3 * ctrlpoints[Devil3 + 1][2] * t3*pow(1 - t3, 2) + 3 * ctrlpoints[Devil3 + 2][2] * pow(t3, 2)*(1 - t3) + ctrlpoints[Devil3 + 3][2] * pow(t3, 3), 0.0, 1.0, 0.0);
			}
			else
				gluLookAt((1 - t2)*ctrlpoints[ctrlcount - 2][0] + t2 * ctrlpoints[0][0],
				(1 - t2)*ctrlpoints[ctrlcount - 2][1] + t2 * ctrlpoints[0][1] + 50,
					(1 - t2)*ctrlpoints[ctrlcount - 2][2] + t2 * ctrlpoints[0][2],
					(1 - t3)*ctrlpoints[ctrlcount - 2][0] + t3 * ctrlpoints[0][0],
					(1 - t3)*ctrlpoints[ctrlcount - 2][1] + t3 * ctrlpoints[0][1] + 50,
					(1 - t3)*ctrlpoints[ctrlcount - 2][2] + t3 * ctrlpoints[0][2], 0.0, 1.0, 0.0);
	
		}
		else if (view == 2) {
			if (HumanRotate == 180)gluLookAt(HumanX, 200, HumanZ + 550, HumanX, 150, HumanZ + 450, 0.0, 1.0, 0.0);
			if (HumanRotate == 0)gluLookAt(HumanX, 200, HumanZ + 450, HumanX, 150, HumanZ + 550, 0.0, 1.0, 0.0);
			if (HumanRotate == 270)gluLookAt(HumanX + 50, 200, HumanZ + 500, HumanX -50, 150, HumanZ + 500, 0.0, 1.0, 0.0);
			if (HumanRotate == -270)gluLookAt(HumanX - 50, 200, HumanZ + 500, HumanX + 50, 150, HumanZ +500, 0.0, 1.0, 0.0);
		}
		break;

	}
	glColor3f(0.5, 1.0, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(-500, 0, -500);
	glVertex3f(-500, 0,  500);
	glVertex3f(500, 0, 500);
	glVertex3f(500, 0, -500);
	glEnd();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-500, 0, -500);
	for (int i = 0; i < 4; i++) {
		glTranslated(200, 0, 0);
		for (int j = 0; j < 4; j++)
		{
			glTranslated(0, 0, 200);
			glutSolidCube(10);
		}
		glTranslated(0, 0, -800);
	}
	glPopMatrix();

	// 제어점에 점을 그린다. 
	glPointSize(5.0);
	glColor3f(0.0, 0.0, 1.0);
	switch (mode)
	{
	case 1:
		for (int i = 0; i < 19; i++) {
			copypoints[i][0] = ctrlpoints[i][0];
			copypoints[i][1] = 0;
			copypoints[i][2] = ctrlpoints[i][2];
		}
		break;
	case 2:
		for (int i = 0; i < 19; i++) {
			copypoints[i][0] = ctrlpoints[i][0];
			copypoints[i][1] = ctrlpoints[i][1];
			copypoints[i][2] = 0;
		}
		break;
	case 3:
		for (int i = 0; i < 19; i++) {
			copypoints[i][0] = ctrlpoints[i][0];
			copypoints[i][1] = ctrlpoints[i][1];
			copypoints[i][2] = ctrlpoints[i][2];
		}
		break;

	}
	if (mode < 3) {
		glBegin(GL_POINTS);
		for (int i = 0; i < ctrlcount - 1; i++)
			glVertex3fv(&copypoints[i][0]);
		glEnd();

	
		
		for (int i = 0; i + 3 < ctrlcount;) {
			glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &copypoints[i][0]);
			glEnable(GL_MAP1_VERTEX_3);
			//glMapGrid1f(10.0, 0.0, 1.0); // 매개변수 0~1 사이를 10개로 나눔 
			//glEvalMesh1(GL_LINE, 0, 10);   // 선분으로 나눈 부분 0~10까지 선으로 그림
			//glDisable(GL_MAP1_VERTEX_3);
			// 제어점 사이의 곡선위의 점들을 계산한다.  제어점 사이를 10개로 나누어 그 점들을 연결한다. 곡선위의 점 계산 
			glBegin(GL_LINE_STRIP);
			for (int j = 0; j <= 10; j++)
				glEvalCoord1f((GLfloat)j / 10.0);
			glEnd();

			i = i + 3;
		}
	}
	else {
		glEnable(GL_DEPTH_TEST);

		for (int i = 0; i < 20; i++) {
			if (ctrlpoints[i][0] > 0) {
				modelPoint1[i][0] = ctrlpoints[i][0] + 10;
				modelPoint2[i][0] = ctrlpoints[i][0] - 10;
			}
			if (ctrlpoints[i][0] < 0) {
				modelPoint1[i][0] = ctrlpoints[i][0] - 10;
				modelPoint2[i][0] = ctrlpoints[i][0] + 10;
			}
			if (ctrlpoints[i][2] > 0) {
				modelPoint1[i][2] = ctrlpoints[i][2] + 10;
				modelPoint2[i][2] = ctrlpoints[i][2] - 10;
			}
			if (ctrlpoints[i][2] < 0) {
				modelPoint1[i][2] = ctrlpoints[i][2] - 10;
				modelPoint2[i][2] = ctrlpoints[i][2] + 10;
			}
			modelPoint1[i][1] = ctrlpoints[i][1];
			modelPoint2[i][1] = ctrlpoints[i][1];
		}


		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(-500, 0, -500);
		for (int i = 0; i < 4; i++) {
			glTranslated(200, 0, 0);
			for (int j = 0; j < 4; j++)
			{
				glTranslated(0, 0, 200);
				glPushMatrix();
				glTranslated(0, 100, 0);
				glColor3f(0, 1, 0);
				glutWireSphere(50, 15, 15);
				glTranslated(0, -70, 0);
				glScalef(1, 10, 1);
				glColor3f(0.5, 0.5, 0);
				glutSolidCube(10);
				glPopMatrix();
			}
			glTranslated(0, 0, -800);
		}
		glPopMatrix();

		glColor3d(1, 1, 1);
		for (int i = 0; i + 3 < ctrlcount;) {
			glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &copypoints[i][0]);
			glPushMatrix();
			glTranslatef(ctrlpoints[i][0], ctrlpoints[i][1] / 2.0, ctrlpoints[i][2]);
			glScalef(1, ctrlpoints[i][1] / 10.0, 1);
			glColor3f(1, 0, 0);
			glutSolidCube(10);
			glPopMatrix();
			glColor3d(1, 1, 1);
			glEnable(GL_MAP1_VERTEX_3);
			//glMapGrid1f(10.0, 0.0, 1.0); // 매개변수 0~1 사이를 10개로 나눔 
			//glEvalMesh1(GL_LINE, 0, 10);   // 선분으로 나눈 부분 0~10까지 선으로 그림
			//glDisable(GL_MAP1_VERTEX_3);
			// 제어점 사이의 곡선위의 점들을 계산한다.  제어점 사이를 10개로 나누어 그 점들을 연결한다. 곡선위의 점 계산 
			glBegin(GL_LINE_STRIP);
			for (int j = 0; j <= 10; j++)
				glEvalCoord1f((GLfloat)j / 10.0);
			glEnd();

			i = i + 3;
		}

		for (int i = 0; i + 3 < ctrlcount;) {
			glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &modelPoint1[i][0]);
			glEnable(GL_MAP1_VERTEX_3);
			//glMapGrid1f(10.0, 0.0, 1.0); // 매개변수 0~1 사이를 10개로 나눔 
			//glEvalMesh1(GL_LINE, 0, 10);   // 선분으로 나눈 부분 0~10까지 선으로 그림
			//glDisable(GL_MAP1_VERTEX_3);
			// 제어점 사이의 곡선위의 점들을 계산한다.  제어점 사이를 10개로 나누어 그 점들을 연결한다. 곡선위의 점 계산 
			glBegin(GL_LINE_STRIP);
			for (int j = 0; j <= 10; j++)
				glEvalCoord1f((GLfloat)j / 10.0);
			glEnd();

			i = i + 3;
		}

		for (int i = 0; i + 3 < ctrlcount;) {
			glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &modelPoint2[i][0]);
			glEnable(GL_MAP1_VERTEX_3);
			//glMapGrid1f(10.0, 0.0, 1.0); // 매개변수 0~1 사이를 10개로 나눔 
			//glEvalMesh1(GL_LINE, 0, 10);   // 선분으로 나눈 부분 0~10까지 선으로 그림
			//glDisable(GL_MAP1_VERTEX_3);
			// 제어점 사이의 곡선위의 점들을 계산한다.  제어점 사이를 10개로 나누어 그 점들을 연결한다. 곡선위의 점 계산 
			glBegin(GL_LINE_STRIP);
			for (int j = 0; j <= 10; j++)
				glEvalCoord1f((GLfloat)j / 10.0);
			glEnd();

			i = i + 3;
		}
		glColor3f(1, 1, 0);
		
		if (Devil >= 0) {
			glPushMatrix();
			glTranslatef(ctrlpoints[Devil][0] * pow(1 - t, 3) + 3 * ctrlpoints[Devil + 1][0] * t*pow(1 - t, 2) + 3 * ctrlpoints[Devil + 2][0] * pow(t, 2)*(1 - t) + ctrlpoints[Devil + 3][0] * pow(t, 3),
				ctrlpoints[Devil][1] * pow(1 - t, 3) + 3 * ctrlpoints[Devil + 1][1] * t*pow(1 - t, 2) + 3 * ctrlpoints[Devil + 2][1] * pow(t, 2)*(1 - t) + ctrlpoints[Devil + 3][1] * pow(t, 3),
				ctrlpoints[Devil][2] * pow(1 - t, 3) + 3 * ctrlpoints[Devil + 1][2] * t*pow(1 - t, 2) + 3 * ctrlpoints[Devil + 2][2] * pow(t, 2)*(1 - t) + ctrlpoints[Devil + 3][2] * pow(t, 3));
			glutSolidSphere(30,15,15);
			glPopMatrix();
		}
		else {
			glPushMatrix();
			glTranslatef((1 - t)*ctrlpoints[ctrlcount - 2][0] + t * ctrlpoints[0][0],
				(1 - t)*ctrlpoints[ctrlcount - 2][1] + t * ctrlpoints[0][1],
				(1 - t)*ctrlpoints[ctrlcount - 2][2] + t * ctrlpoints[0][2]);
			glutSolidSphere(30, 15, 15);
			glPopMatrix();
		}
		glColor3f(0, 1, 0);
		if (Devil2 >= 0) {
			glPushMatrix();
			glTranslatef(ctrlpoints[Devil2][0] * pow(1 - t2, 3) + 3 * ctrlpoints[Devil2 + 1][0] * t2*pow(1 - t2, 2) + 3 * ctrlpoints[Devil2 + 2][0] * pow(t2, 2)*(1 - t2) + ctrlpoints[Devil2 + 3][0] * pow(t2, 3),
				ctrlpoints[Devil2][1] * pow(1 - t2, 3) + 3 * ctrlpoints[Devil2 + 1][1] * t2*pow(1 - t2, 2) + 3 * ctrlpoints[Devil2 + 2][1] * pow(t2, 2)*(1 - t2) + ctrlpoints[Devil2 + 3][1] * pow(t2, 3),
				ctrlpoints[Devil2][2] * pow(1 - t2, 3) + 3 * ctrlpoints[Devil2 + 1][2] * t2*pow(1 - t2, 2) + 3 * ctrlpoints[Devil2 + 2][2] * pow(t2, 2)*(1 - t2) + ctrlpoints[Devil2 + 3][2] * pow(t2, 3));
			glutSolidSphere(30, 15, 15);
			glPopMatrix();
		}
		else {
			glPushMatrix();
			glTranslatef((1 - t2)*ctrlpoints[ctrlcount - 2][0] + t2 * ctrlpoints[0][0],
				(1 - t2)*ctrlpoints[ctrlcount - 2][1] + t2 * ctrlpoints[0][1],
				(1 - t2)*ctrlpoints[ctrlcount - 2][2] + t2 * ctrlpoints[0][2]);
			glutSolidSphere(30, 15, 15);
			glPopMatrix();
		}
		glColor3f(0, 1, 1);
		if (Devil3 >= 0) {
			glPushMatrix();
			glTranslatef(ctrlpoints[Devil3][0] * pow(1 - t3, 3) + 3 * ctrlpoints[Devil3 + 1][0] * t3*pow(1 - t3, 2) + 3 * ctrlpoints[Devil3 + 2][0] * pow(t3, 2)*(1 - t3) + ctrlpoints[Devil3 + 3][0] * pow(t3, 3),
				ctrlpoints[Devil3][1] * pow(1 - t3, 3) + 3 * ctrlpoints[Devil3 + 1][1] * t3*pow(1 - t3, 2) + 3 * ctrlpoints[Devil3 + 2][1] * pow(t3, 2)*(1 - t3) + ctrlpoints[Devil3 + 3][1] * pow(t3, 3),
				ctrlpoints[Devil3][2] * pow(1 - t3, 3) + 3 * ctrlpoints[Devil3 + 1][2] * t3*pow(1 - t3, 2) + 3 * ctrlpoints[Devil3 + 2][2] * pow(t3, 2)*(1 - t3) + ctrlpoints[Devil3 + 3][2] * pow(t3, 3));
			glutSolidSphere(30, 15, 15);
			glPopMatrix();
		}
		else {
			glPushMatrix();
			glTranslatef((1 - t3)*ctrlpoints[ctrlcount - 2][0] + t3 * ctrlpoints[0][0],
				(1 - t3)*ctrlpoints[ctrlcount - 2][1] + t3 * ctrlpoints[0][1],
				(1 - t3)*ctrlpoints[ctrlcount - 2][2] + t3 * ctrlpoints[0][2]);
			glutSolidSphere(30, 15, 15);
			glPopMatrix();
		}

		glColor3f(1, 1, 1);

		t += 0.01;
		t2 += 0.01;
		t3 += 0.01;
		if (t >= 1)
		{
			t = 0;
			if (Devil == -1)
				Devil = 0;
			else
				Devil += 3;
		}
		if (Devil >= ctrlcount - 2)
			Devil = -1;
		if (t2 >= 1)
		{
			t2 = 0;
			if (Devil2 == -1)
				Devil2 = 0;
			else
				Devil2 += 3;
		}
		if (Devil2 >= ctrlcount - 2)
			Devil2 = -1;
		if (t3 >= 1)
		{
			t3 = 0;
			if (Devil3 == -1)
				Devil3 = 0;
			else
				Devil3 += 3;
		}
		if (Devil3 >= ctrlcount - 2)
			Devil3 = -1;
	}

	glBegin(GL_LINES);
	glVertex3fv(&copypoints[ctrlcount-2][0]);
	glVertex3fv(&copypoints[0][0]);
	glEnd();
	if (mode > 2) {
		glBegin(GL_LINES);
		glVertex3fv(&modelPoint1[ctrlcount - 2][0]);
		glVertex3fv(&modelPoint1[0][0]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3fv(&modelPoint2[ctrlcount - 2][0]);
		glVertex3fv(&modelPoint2[0][0]);
		glEnd();
	}

	if(wether == 2)
	for (int i = 0; i < 34; i++) {
		glColor3f(1.0f, 1.0f, 1.0f);
		for (int j = 0; j < 34; j++) {
			if (snow[i][j] != 0) {
				glPushMatrix();
				glTranslatef(-515 + (i * 30) + 15, snow[i][j], -515 + (j * 30) + 15);
				glutSolidSphere(3, 5, 5);
				snow[i][j] -= 1;
				if (snow[i][j] < 0) snow[i][j] = 0;
				glPopMatrix();
			}

		}
	}
	if (wether == 3)
		for (int i = 0; i < 34; i++) {
			glColor3f(0.0f, 0.0f, 1.0f);
			for (int j = 0; j < 34; j++) {
				if (snow[i][j] != 0) {
					glPushMatrix();
					glTranslatef(-515 + (i * 30) + 15, snow[i][j], -515 + (j * 30) + 15);
					glScalef(1, 5, 1);
					glutSolidCube(3);
					snow[i][j] -= 5;
					if (snow[i][j] < 0) snow[i][j] = 0;
					glPopMatrix();
				}

			}
		}

	glPushMatrix();
	glTranslatef(0, 0, 500);
	glTranslatef(HumanX, 0, HumanZ);
	glRotatef(HumanRotate, 0, 1, 0);
	Robot();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(xHumanX_, 0, xHumanZ_);
	Robot2();
	glDisable(GL_DEPTH_TEST);
	glPopMatrix();


	

	glPopMatrix();

	

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h) {
	w_ = w;
	h_ = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (mode > 2)
		gluPerspective(60.0, 1.0, 1.0, 5000.0);
	else
		glOrtho(-500, 500, -500, 500, -500, 500);
	glMatrixMode(GL_MODELVIEW);
}

GLvoid Keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 'r':
		for (int i = 0; i < 19; i++) {
			ctrlpoints[i][0] = 0;
			ctrlpoints[i][1] = 0;
			ctrlpoints[i][2] = 0;
		}
		ctrlcount = 0;
		break;

	case '/':
		HumanRotate = -270;
		Humanmove++;
		HumanX += 5;
		break;
	case ',':
		HumanRotate = 270;
		Humanmove++;
		HumanX -= 5;
		break;
	case 'l':
		HumanRotate = 180;
		Humanmove++;
		HumanZ -= 5;
		break;
	case '.':
		HumanRotate = 0;
		Humanmove++;
		HumanZ += 5;
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
	case '=':
		Z_ += 5;
		break;
	case '+':
		Z_ -= 5;
		break;

	case '1':
		mode = 1;
		break;
	case '2':
		mode = 2;
		break;
	case '3':
		mode = 3;
		break;
	case '4':
		view = 1;
		break;
	case '5':
		view = 2;
		break;
	case '6':
		view = 3;
		break;
	case '$':
		wether = 1;
		break;
	case '%':
		wether = 2;
		break;
	case '^':
		wether = 3;
		break;





	}
	glutPostRedisplay();


}
bool right_button = false;
GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		ctrlcount = (ctrlcount >= 19 ? 20 : ctrlcount + 1);
		if (ctrlcount != 20) {
			ctrlpoints[ctrlcount - 1][0] = 500 - (1000 - x*2);
			ctrlpoints[ctrlcount - 1][1] = rand() % 200 + 100;
			ctrlpoints[ctrlcount - 1][2] = 500 - (1000 - y*2);
		}

	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		right_button = true;

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
		right_button = false;

}

void Motion(int x, int y) {
	if (right_button == true) {
		if (mode == 1)
			for (int i = 0; i < ctrlcount; i++) {
				if (abs((int)ctrlpoints[i][0] - (500 - (1000 - x * 2))) < 10 && abs((int)ctrlpoints[i][2] - (500 - (1000 - y * 2))) < 10) {
					ctrlpoints[i][0] = 500 - (1000 - x * 2);
					ctrlpoints[i][2] = 500 - (1000 - y * 2);
				}
			}
		else if (mode == 2)
			for (int i = 0; i < ctrlcount; i++) {
				if (abs((int)ctrlpoints[i][0] - (500 - (1000 - x * 2))) < 10 && abs((int)ctrlpoints[i][1] - (500 -  (y * 2))) < 10) {
					ctrlpoints[i][0] = 500 - (1000 - x * 2);
					ctrlpoints[i][1] = 500 - (y * 2);
				}
			}
	}
}


void Robot() {
	glColor3d(0, 0, 0);
	glPushMatrix();
	//왼다리
	glColor3d(1, 0, 0);
	glTranslatef(-20, 20, 0);
	glTranslated(0, 20, 0);
	glRotatef(HumanDG, 1, 0, 0);
	glTranslated(0, -20, 0);
	glScalef(1, 6, 1);
	glutSolidCube(7);
	glPopMatrix();

	glPushMatrix();
	//오른다리
	glTranslatef(20, 20, 0);
	glTranslated(0, 20, 0);
	glRotatef(-HumanDG, 1, 0, 0);
	glTranslated(0, -20, 0);
	glScalef(1, 6, 1);
	glutSolidCube(7);
	glPopMatrix();
	glTranslatef(0, 60, 0);

	glPushMatrix();
	//몸
	glColor3d(0, 1, 0);
	glScalef(5, 6, 4);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	//왼팔
	glColor3f(0.3, 0.7, 1.0);
	glTranslatef(30, 0, 0);
	glTranslated(0, 20, 0);
	glRotatef(HumanDG, 1, 0, 0);
	glTranslated(0, -20, 0);
	glScalef(1, 6, 1);
	glutSolidCube(7);
	glPopMatrix();

	glPushMatrix();
	//오른팔
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
}

void Robot2() {
	glScalef(0.7, 0.7, 0.7);
	glColor3d(0, 0, 0);
	glPushMatrix();
	//왼다리
	glColor3d(0, 0, 0);
	glTranslatef(-20, 20, 0);
	glTranslated(0, 20, 0);
	glRotatef(xHumanDG, 1, 0, 0);
	glTranslated(0, -20, 0);
	glScalef(1, 6, 1);
	glutSolidCube(7);
	glPopMatrix();

	glPushMatrix();
	//오른다리
	glTranslatef(20, 20, 0);
	glTranslated(0, 20, 0);
	glRotatef(-xHumanDG, 1, 0, 0);
	glTranslated(0, -20, 0);
	glScalef(1, 6, 1);
	glutSolidCube(7);
	glPopMatrix();
	glTranslatef(0, 60, 0);

	glPushMatrix();
	//몸
	glColor3d(0, 0, 0);
	glScalef(5, 6, 4);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	//왼팔
	glTranslatef(30, 0, 0);
	glTranslated(0, 20, 0);
	glRotatef(xHumanDG, 1, 0, 0);
	glTranslated(0, -20, 0);
	glScalef(1, 6, 1);
	glutSolidCube(7);
	glPopMatrix();

	glPushMatrix();
	//오른팔
	glTranslatef(-30, 0, 0);
	glTranslated(0, 20, 0);
	glRotatef(-xHumanDG, 1, 0, 0);
	glTranslated(0, -20, 0);
	glScalef(1, 6, 1);
	glutSolidCube(7);
	glPopMatrix();

	glTranslatef(0, 40, 0);
	glutSolidCube(25);
	glTranslatef(0, 0, 5);
	glutSolidCone(7, 15, 15, 15);
}

void iscolide() {
	int x = -500, z = -500;
	for (int i = 0; i < 4; i++) {
		x += 200;
		for (int j = 0; j < 4; j++)
		{
			z += 200;
			if (abs((int)(xHumanX_ - x)) < 45 && abs((int)(xHumanZ_ - z)) < 45) {
				xHumanX *= -1 + (rand() % 2 * 2);
				xHumanZ *= -1 + (rand() % 2 * 2);
			}
		}
		z -= 800;
	}
	if (xHumanX_ < -500 || xHumanX_ > 500)
		xHumanX *= -1;
	if (xHumanZ_ < -500 || xHumanZ_ > 500)
		xHumanZ *= -1;

	if (abs((int)(xHumanX_ - HumanX)) < 45 && abs((int)(xHumanZ_ - (500 + HumanZ))) < 45 && Grap == 0) {
		Grap = 1;
	}


}