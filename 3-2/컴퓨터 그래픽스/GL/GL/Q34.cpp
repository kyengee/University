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
GLvoid PPraticle();

void DoTimer(int value);
void Robot();


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

int x_ = 45, y_ = 30, Z_ = 0;
int moon = 0;
bool Enable1 = false, Enable2 = false;
int Rotate_ = 0, autoRotate_ = 0;
float Diffuse_light = 0;
float Specular_light = 0;
float Ambient_light = 0;
float HumanDG = 0;
float HumanX = 0;
float HumanY = 0;
float HumanZ = 0;
float HumanDG_flag = 1;
float HumanRotate = 0;
int Humanmove = 0;
float Parti = 0;

int normal = 0;
float ambientList[34][34] = { 0, };
float snow[34][34] = { 0, };
float sport = 40.0f;
GLfloat ambientLight[] = { 1.0f, 0.1f, 0.1f, 1.0f };
GLfloat DiffuseLight[] = { 1.0f, 0.6f, 0.6f, 1.0f };
GLfloat SpecularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat ambientLight1[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat DiffuseLight1[] = { 0.3, 0.1, 0.1, 1.0f };
GLfloat SpecularLight1[] = { 0.3f, 0.3f, 0.3f, 0.3f };
GLfloat lightPos1[] = { -800.0, 600.0, 0.0,1.0 };

GLfloat ambientLight2[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat DiffuseLight2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat SpecularLight2[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat lightPos2[] = { 0.0f, 200.0f, 0.0f,1.0f };

void DoTimer(int value)

{
	if (Humanmove > 0) {
		HumanDG += HumanDG_flag = (HumanDG >= 60 ? -3 : (HumanDG <= -60 ? 3 : HumanDG_flag));
		Humanmove--;
		
	}
	else
		HumanDG = 0;
	if (snow[rand() % 34][rand() % 34] == 0)
		snow[rand() % 34][rand() % 34] = 500;
	moon = (moon >= 360 ? 0 : moon + 3);
	if (Diffuse_light == 1) {
		DiffuseLight1[0] += 0.05f;
		DiffuseLight2[2] += 0.05f;
		Diffuse_light = 0;
	}
	if (Diffuse_light == -1) {
		DiffuseLight1[0] -= 0.05f;
		DiffuseLight2[2] -= 0.05f;
		Diffuse_light = 0;
	}
	if (Specular_light == 1) {
		for (int i = 0; i < 3; i++) {
			SpecularLight1[i] += 0.05f;
			SpecularLight2[i] += 0.05f;
		}
		Specular_light = 0;
	}
	if (Specular_light == -1) {
		for (int i = 0; i < 3; i++) {
			SpecularLight1[i] -= 0.05f;
			SpecularLight2[i] -= 0.05f;
		}
		Specular_light = 0;
	}
	if (Ambient_light == 1) {
		for (int i = 0; i < 3; i++) {
			ambientLight1[i] += 0.05f;
			ambientLight2[i] += 0.05f;
		}
		Ambient_light = 0;
	}
	if (Ambient_light == -1) {
		for (int i = 0; i < 3; i++) {
			ambientLight1[i] -= 0.05f;
			ambientLight2[i] -= 0.05f;
		}
		Ambient_light = 0;
	}
	autoRotate_++;
	if (Rotate_ >= 360)
		Rotate_ = 0;
	if (autoRotate_ >= 360)
		autoRotate_ = 0;

	glutTimerFunc(30, DoTimer, 1);
	glutPostRedisplay();
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glFrontFace(GL_CCW);

	ambientLight[0] = 0.1f;
	ambientLight[1] = 0.1f;
	ambientLight[2] = 0.1f;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight1);


	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight2);
	GLfloat GG[] = { 0.0f,-1.0f,0.0f,1.0f };
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60.0f);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, sport);


	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientLight);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DiffuseLight);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SpecularLight);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 64);


	glPushMatrix();
	gluLookAt((1000 + Z_)*cos(y_ / 180.0*pi)*cos(x_ / 180.0*pi), (1000 + Z_)*sin(y_ / 180.0*pi), (1000 + Z_)*cos(y_ / 180.0*pi)*sin(x_ / 180.0*pi), 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);



	glPushMatrix();
	glTranslatef(0, 180, 0);
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glRotatef(90 * (i + 1), 0, 1, 0);
		glRotatef(30, 1, 0, 0);
		glBegin(GL_TRIANGLES);
		if (normal == 1)glNormal3f(0.0, 1.0, 0.0);
		else glNormal3f(0.0, -1.0, 0.0);
		glVertex2f(0, 0);
		glVertex2f(100, -200);
		glVertex2f(-100, -200);
		glEnd();
		glPopMatrix();
	}

	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glTranslatef(400, 0, 400);
		glRotatef(90 * (i + 1), 0, 1, 0);
		glRotatef(30, 1, 0, 0);
		glBegin(GL_TRIANGLES);
		glVertex2f(0, 0);
		glVertex2f(100, -200);
		glVertex2f(-100, -200);
		glEnd();
		glPopMatrix();
	}
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glTranslatef(-400, 0, 400);
		glRotatef(90 * (i + 1), 0, 1, 0);
		glRotatef(30, 1, 0, 0);
		glBegin(GL_TRIANGLES);
		glVertex2f(0, 0);
		glVertex2f(100, -200);
		glVertex2f(-100, -200);
		glEnd();
		glPopMatrix();
	}
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glTranslatef(400, 0, -400);
		glRotatef(90 * (i + 1), 0, 1, 0);
		glRotatef(30, 1, 0, 0);
		glBegin(GL_TRIANGLES);
		glVertex2f(0, 0);
		glVertex2f(100, -200);
		glVertex2f(-100, -200);
		glEnd();
		glPopMatrix();
	}
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glTranslatef(-400, 0, -400);
		glRotatef(90 * (i + 1), 0, 1, 0);
		glRotatef(30, 1, 0, 0);
		glBegin(GL_TRIANGLES);
		glVertex2f(0, 0);
		glVertex2f(100, -200);
		glVertex2f(-100, -200);
		glEnd();
		glPopMatrix();
	}

	glTranslatef(0, 100, 0);
	glRotatef(moon, 0, 1, 0);
	glTranslatef(100, 0, 0);
	glutSolidSphere(100, 40, 40);
	glPopMatrix();



	glPushMatrix();
	glRotatef(Rotate_ + autoRotate_, 0, 1, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
	glTranslatef(500.0, 500.0, 0.0);
	glutSolidCone(5, 10, 15, 15);
	glTranslatef(-1000.0, 0.0, 0.0);
	glutSolidCone(5, 10, 15, 15);

	if (Enable1 == true)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);
	glPopMatrix();

	if (HumanX < 100 && HumanZ < 100)
		PPraticle();
	else
		Parti = 0;

	glPushMatrix();
	glTranslatef(HumanX, 0, HumanZ);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, GG);
	if (Enable2 == true)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);
	glRotatef(HumanRotate, 0, 1, 0);
	Robot();
	glPopMatrix();


	glPushMatrix();

	for (int i = 0; i < 34; i++) {
		for (int j = 0; j < 34; j++) {
			ambientLight[0] = ambientList[i][j];
			ambientLight[1] = ambientList[i][j];
			ambientLight[2] = ambientList[i][j];
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
			glBegin(GL_POLYGON);
			glVertex3f(-515 + (i * 30), 0, -515 + (j * 30));
			glVertex3f(-515 + (i * 30), 0, -515 + (j * 30) + 30);
			glVertex3f(-515 + (i * 30) + 30, 0, -515 + (j * 30) + 30);
			glVertex3f(-515 + (i * 30) + 30, 0, -515 + (j * 30));
			glEnd();

			if (snow[i][j] != 0) {
				glPushMatrix();
				ambientLight[0] = 1.0f;
				ambientLight[1] = 1.0f;
				ambientLight[2] = 1.0f;
				glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
				glColor3f(1.0f, 1.0f, 1.0f);
				glTranslatef(-515 + (i * 30) + 15, snow[i][j], -515 + (j * 30) + 15);
				glutSolidSphere(3, 5, 5);
				if (snow[i][j] == 1)
					ambientList[i][j] += 0.05f;
				snow[i][j] -= 1;
				glPopMatrix();
			}

		}
	}
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 5000.0);
	glMatrixMode(GL_MODELVIEW);
}

GLvoid Keyboard(unsigned char key, int x, int y) {

	switch (key) {
		/*case 'i':
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
			break;*/
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


	case '+':
		Z_ += 5;
		break;
	case '=':
		Z_ -= 5;
		break;

	case '1':
		Enable1 = (Enable1 == true ? false : true);
		break;

	case '2':
		Enable2 = (Enable2 == true ? false : true);
		break;

	case'y':
		Rotate_--;
		break;
	case'Y':
		Rotate_++;
		break;

	case'u':
		autoRotate_ = 1;
		break;

	case'U':
		autoRotate_ = 0;
		break;

	case 'g':
		Ambient_light++;
		break;
	case 'G':
		Ambient_light--;
		break;
	case'h':
		Diffuse_light++;
		break;
	case'H':
		Diffuse_light--;
		break;
	case'j':
		Specular_light++;
		break;
	case'J':
		Specular_light--;
		break;
	case'o':
		normal = 1;
		break;
	case'O':
		normal = 0;
		break;
	case '/':
		HumanRotate = -90;
		Humanmove++;
		HumanX--;
		break;
	case ',':
		HumanRotate = 90;
		Humanmove++;
		HumanX++;
		break;
	case 'l':
		HumanRotate = 0;
		Humanmove++;
		HumanZ++;
		break;
	case '.':
		HumanRotate = 180;
		Humanmove++;
		HumanZ--;
		break;
	case 'P':
		sport += 10.0f;
		break;
	case 'p':
		sport -= 10.0f;
		break;




	}
	glutPostRedisplay();


}

GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

	}



}

void Robot() {
	glColor3d(0, 0, 0);
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
}

GLvoid PPraticle() {
	glPushMatrix();
		glTranslatef(HumanX, 50, HumanZ);
	glColor3b(0, 1, 0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 360; i++)
		glVertex3f(Parti * cos(i / 180.0*pi), 0, Parti * sin(i / 180.0*pi));
	for (int i = 0; i < 360; i++)
		glVertex3f((Parti+30) * cos(i / 180.0*pi), 0, (Parti+30) * sin(i / 180.0*pi));
	glEnd();
	Parti+= 3;
	if (Parti > 100)
	Parti = 0;
	glPopMatrix();

}
