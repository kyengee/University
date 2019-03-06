#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
float pi = 3.141592;
float ani = 0;
GLuint texture_object[5];
GLubyte *pBytes; // 데이터를 가리킬 포인터 
BITMAPINFO *info; // 비트맵 헤더 저장할 변수

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	// 바이너리 읽기 모드로 파일을 연다
	if ((fopen_s(&fp, filename, "rb")) != 0)
		return NULL;

	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}

	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}

	// BITMAPINFOHEADER 위치로 간다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}

	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);

	// 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}

	fclose(fp);
	return bits;
}



GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);

void DoTimer(int value);


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
int normal = 0;
GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat DiffuseLight[] = { 0.6f, 0.6f, 0.6f, 1.0f };
GLfloat SpecularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat ambientLight1[] = { 0.1f, 0.1f, 0.1f, 1.1f };
GLfloat DiffuseLight1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat SpecularLight1[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lightPos1[] = { -500.0, 500.0, 0.0,1.0 };

GLfloat ambientLight2[] = { 0.0f, 0.0f, 0.1f, 1.1f };
GLfloat DiffuseLight2[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat SpecularLight2[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lightPos2[] = { 500.0, 500.0, 0.0,1.0 };
bool init = false;

void DoTimer(int value)

{
	ani += 0.2;
	if(ani > 4)
		ani = 0;
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
	if (Rotate_ >= 360)
		Rotate_ = 0;
	if (autoRotate_ >= 360)
		autoRotate_ = 0;

	if (init == false) {
		glGenTextures(5, texture_object);
		glBindTexture(GL_TEXTURE_2D, texture_object[0]);
		pBytes = LoadDIBitmap("./brick.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 271, 185, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glBindTexture(GL_TEXTURE_2D, texture_object[1]);
		pBytes = LoadDIBitmap("./desert.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 259, 193, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glBindTexture(GL_TEXTURE_2D, texture_object[2]);
		pBytes = LoadDIBitmap("./Sphere.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 215, 210, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glBindTexture(GL_TEXTURE_2D, texture_object[3]);
		pBytes = LoadDIBitmap("./sky.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 274, 184, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glBindTexture(GL_TEXTURE_2D, texture_object[4]);
		pBytes = LoadDIBitmap("./bird.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 415, 415, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
		glEnable(GL_TEXTURE_2D);
		init = true;
	}

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
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight1);


	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight2);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientLight);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DiffuseLight);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SpecularLight);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 64);

	glPushMatrix();
	gluLookAt((1000 + Z_)*cos(y_ / 180.0*pi)*cos(x_ / 180.0*pi), (1000 + Z_)*sin(y_ / 180.0*pi), (1000 + Z_)*cos(y_ / 180.0*pi)*sin(x_ / 180.0*pi), 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);





	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-500, 0, -500);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-500, 0, 500);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(500, 0, 500);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(500, 0, -500);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 180, 0);
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glRotatef(90 * (i + 1), 0, 1, 0);
		glRotatef(30, 1, 0, 0);
		glBindTexture(GL_TEXTURE_2D, texture_object[0]);
		glBegin(GL_TRIANGLES);
		if (normal == 1)glNormal3f(0.0, 1.0, 0.0);
		else glNormal3f(0.0, -1.0, 0.0);
		glTexCoord2f(0.5f, 1.0f);
		glVertex2f(0, 0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(100, -200);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(-100, -200);
		glEnd();
		glPopMatrix();
	}

	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glTranslatef(400, 0, 400);
		glRotatef(90 * (i + 1), 0, 1, 0);
		glRotatef(30, 1, 0, 0);
		glBindTexture(GL_TEXTURE_2D, texture_object[0]);
		glBegin(GL_TRIANGLES);
		glTexCoord2f(0.5f, 1.0f);
		glVertex2f(0, 0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(100, -200);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(-100, -200);
		glEnd();
		glPopMatrix();
	}
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glTranslatef(-400, 0, 400);
		glRotatef(90 * (i + 1), 0, 1, 0);
		glRotatef(30, 1, 0, 0);
		glBindTexture(GL_TEXTURE_2D, texture_object[0]);
		glBegin(GL_TRIANGLES);
		glTexCoord2f(0.5f, 1.0f);
		glVertex2f(0, 0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(100, -200);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(-100, -200);
		glEnd();
		glPopMatrix();
	}
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glTranslatef(400, 0, -400);
		glRotatef(90 * (i + 1), 0, 1, 0);
		glRotatef(30, 1, 0, 0);
		glBindTexture(GL_TEXTURE_2D, texture_object[0]);
		glBegin(GL_TRIANGLES);
		glTexCoord2f(0.5f, 1.0f);
		glVertex2f(0, 0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(100, -200);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(-100, -200);
		glEnd();
		glPopMatrix();
	}
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glTranslatef(-400, 0, -400);
		glRotatef(90 * (i + 1), 0, 1, 0);
		glRotatef(30, 1, 0, 0);
		glBindTexture(GL_TEXTURE_2D, texture_object[0]);
		glBegin(GL_TRIANGLES);
		glTexCoord2f(0.5f, 1.0f);
		glVertex2f(0, 0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(100, -200);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(-100, -200);
		glEnd();
		glPopMatrix();
	}
	// 자동 매핑 설정 
	glEnable (GL_TEXTURE_GEN_S); 
	glEnable (GL_TEXTURE_GEN_T);
	// 구 매핑 
	glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); 
	glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); 
	glBindTexture (GL_TEXTURE_2D, texture_object[2]);

	glTranslatef(0, 100, 0);
	glRotatef(moon, 0, 1, 0);
	glTranslatef(100, 0, 0);
	glutSolidSphere(100, 40, 40);
	glPopMatrix();
	// 자동 매핑 해제 
	glDisable (GL_TEXTURE_GEN_S); 
	glDisable (GL_TEXTURE_GEN_T);

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture_object[4]);
	if (ani < 1) {
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.5f);
		glVertex3f(200, 0, -100);
		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(200, 0, 100);
		glTexCoord2f(0.5f, 1.0f);
		glVertex3f(200, 200, 100);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(200, 200, -100);
		glEnd();
		
	}
	else if (ani < 2) {
		glBegin(GL_POLYGON);
		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(200, 0, -100);
		glTexCoord2f(1.0f, 0.5f);
		glVertex3f(200, 0, 100);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(200, 200, 100);
		glTexCoord2f(0.5f, 1.0f);
		glVertex3f(200, 200, -100);
		glEnd();
	}
	else if (ani < 3) {
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(200, 0, -100);
		glTexCoord2f(0.5f, 0.0f);
		glVertex3f(200, 0, 100);
		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(200, 200, 100);
		glTexCoord2f(0.0f, 0.5f);
		glVertex3f(200, 200, -100);
		glEnd();
	}
	else if (ani < 4) {
		glBegin(GL_POLYGON);
		glTexCoord2f(0.5f, 0.0f);
		glVertex3f(200, 0, -100);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(200, 0, 100);
		glTexCoord2f(1.0f, 0.5f);
		glVertex3f(200, 200, 100);
		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(200, 200, -100);
		glEnd();
	}

	

	glTranslatef(276, 100, 0);
	glScalef(5, 10, 5);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	// 자동 매핑 설정 
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	// 구 매핑 
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glBindTexture(GL_TEXTURE_2D, texture_object[3]);
	glFrontFace(GL_CW);

	glutSolidSphere(1000, 40, 40);
	glFrontFace(GL_CCW);
	// 자동 매핑 해제 
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glPopMatrix();
	



	glPushMatrix();
	glRotatef(Rotate_ + autoRotate_, 0, 1, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
	glTranslatef(500.0, 500.0, 0.0);
	glutSolidCone(5, 10, 15, 15);
	glTranslatef(-1000.0, 0.0, 0.0);
	glutSolidCone(5, 10, 15, 15);

	if (Enable1 == true)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);
	if (Enable2 == true)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);
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




	}
	glutPostRedisplay();


}

GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

	}



}


