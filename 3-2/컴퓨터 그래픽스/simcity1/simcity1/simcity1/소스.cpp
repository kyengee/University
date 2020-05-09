#include<gl/freeglut.h>
#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

class planet {
public:
	int r = 200;
	int degree = 0;
	int speed = 1;
	planet(int r1, int degree1, int speed1) {
		r = r1;
		degree = degree1;
		speed = speed1;

	}

};

GLvoid DrawPlanet(planet* a) {
	GLUquadric* obj = gluNewQuadric();
	gluDisk(obj, 199.0, 200.0, 100, 3);
	glTranslatef(a->r*sin(a->degree / 180.0*3.14592), a->r*cos(a->degree / 180.0*3.14592), 0);
	glutSolidSphere(20, 15, 15);
	if (a->degree >= 360)
		a->degree = 0;
}

void DrawScene();
void Reshape(int, int);
void Keyboard(unsigned char, int, int);
void Timerfunction(int);

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
void setTexture(int);

//좌표변수
float rotateX, rotateY, rotateZ = 0;
int moveR, moveL, moveU, moveD, moveFront, moveBack = 0;
float standardY = -200;

GLUquadricObj *p = gluNewQuadric();

GLuint textureObject[26];
//GLuint textureObject1[10];
GLubyte *pBytes;
BITMAPINFO *info;
//일반변수 
float block2_[10] = { 0.11,0.43,0.09,0.25,0.02,0.19,0.01,0.30,0.05,0.13 };
float block2_flag[10] = { 0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01 };
extern float block4_rota = 0;
int block7_high = 0;
int block7_high_flag = 1;
planet* a = new planet(200, 30, 1);
planet* b = new planet(200, 0, 3);
planet* c = new planet(200, 20, 5);

float block8_AirDG = 0;
float block8_smoge = 0;
float block8_smogeflag = 2;
float block8_Propel = 0;

extern GLfloat Block8_ctrlpoints[3][3][3] = { {{30,20,100},{50,10,90},{90,0,80}},
								{{30,60,0}, {50,40,0}, {90,0,0}},
								{{30,20,-30}, {50,10,-30}, {90,0,-30}} };
//일반변수
bool texture = false;
int craneMove;
float white[] = { 0,0,0,1 };
float block13_smoke[3];
float block13_smoke_move;

int ballX = 0;
int ballZ = 0;

float water;
bool waterBoom;

float ufoMove;
bool ufoUp = true;

float leg_rotate;
bool legUp;
int move;

int humanMove;

//객체함수
void human();
//조명
void initLight()
{
	GLfloat ambientLight[] = { 0.6,0.6,0.6,1.0 };
	GLfloat diffuseLight[] = { 0.5,0.5,1,0.5,1.0 };
	GLfloat specularLight[] = { 0.3,0.3,0.3,1.0 };
	GLfloat lightPos[] = { -200.0,400.0,300.0,1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHTING);
}

//텍스처 기본
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	if ((*info = (BITMAPINFO*)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0*abs((*info)->bmiHeader.biHeight);
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info);
		free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}

void setTexture(int n)
{
	//n개의 이미지 텍스쳐 매핑을 한다.
	glGenTextures(n, textureObject);
	//텍스처와 객체를 결합한다 -- (1)
	glBindTexture(GL_TEXTURE_2D, textureObject[0]);
	//이미지 로딩을 한다 -- (2)
	pBytes = LoadDIBitmap("skyscrapper1.bmp", &info);
	//텍스처 설정 정의 -- (3)
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	//glTexImage2D(GL_TEXTURE_2D, 0, 4, 600, 700, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	//텍스처 파라미터 설정 -- (4)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//텍스처모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//나머지 n-1개의 텍스처에도 (1)~(4) 까지의 과정을 진행하여 텍스처를 설정
	glBindTexture(GL_TEXTURE_2D, textureObject[1]);
	pBytes = LoadDIBitmap("park.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textureObject[2]);
	pBytes = LoadDIBitmap("skyscrapper2_root.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//축구장잔디
	glBindTexture(GL_TEXTURE_2D, textureObject[3]);
	pBytes = LoadDIBitmap("football_ground.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//관중
	glBindTexture(GL_TEXTURE_2D, textureObject[4]);
	pBytes = LoadDIBitmap("spectator1.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//공장
	glBindTexture(GL_TEXTURE_2D, textureObject[5]);
	pBytes = LoadDIBitmap("ground15.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//공장 담
	glBindTexture(GL_TEXTURE_2D, textureObject[6]);
	pBytes = LoadDIBitmap("factory.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textureObject[7]);
	pBytes = LoadDIBitmap("factory_wall.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textureObject[8]);
	pBytes = LoadDIBitmap("block10.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textureObject[9]);
	pBytes = LoadDIBitmap("roof1.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textureObject[10]);
	pBytes = LoadDIBitmap("roof2.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	glBindTexture(GL_TEXTURE_2D, textureObject[12]);
	pBytes = LoadDIBitmap("villa2.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textureObject[13]);
	pBytes = LoadDIBitmap("roof4.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textureObject[14]);
	pBytes = LoadDIBitmap("roof3.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textureObject[15]);
	pBytes = LoadDIBitmap("house1.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	


	glBindTexture(GL_TEXTURE_2D, textureObject[18]);
	pBytes = LoadDIBitmap("house4.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textureObject[19]);
	pBytes = LoadDIBitmap("villa1.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textureObject[21]);
	pBytes = LoadDIBitmap("cityhall.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textureObject[22]);
	pBytes = LoadDIBitmap("block12.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textureObject[23]);
	pBytes = LoadDIBitmap("ground14.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textureObject[24]);
	pBytes = LoadDIBitmap("ground9.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

}


void BaseGround()
{
	glEnable(GL_LIGHTING);

	float gray[] = { 0.3,0.3,0.3,1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, gray);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, gray);

	glBegin(GL_POLYGON);
	glVertex3f(-500, standardY, -500);
	glVertex3f(500, standardY, -500);
	glVertex3f(500, standardY, 500);
	glVertex3f(-500, standardY, 500);
	glEnd();

	glDisable(GL_LIGHTING);
}

void Road()
{
	glEnable(GL_LIGHTING);
	//아스팔트
	glPushMatrix();
	float black[] = { 0.1,0.1,0.1,1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, black);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glMaterialfv(GL_FRONT, GL_SPECULAR, black);

	for (int i = -270; i < 280; i += 270) {
		glBegin(GL_POLYGON);
		glVertex3f(-500, standardY + 0.2, i + 10);
		glVertex3f(500, standardY + 0.2, i + 10);
		glVertex3f(500, standardY + 0.2, i - 10);
		glVertex3f(-500, standardY + 0.2, i - 10);
		glEnd();
	}
	for (int i = -270; i < 280; i += 270) {
		glBegin(GL_POLYGON);
		glVertex3f(i - 10, standardY + 0.2, 500);
		glVertex3f(i + 10, standardY + 0.2, 500);
		glVertex3f(i + 10, standardY + 0.2, -500);
		glVertex3f(i - 10, standardY + 0.2, -500);
		glEnd();
	}

	glBegin(GL_POLYGON);
	glVertex3f(-260, standardY + 0.2, 445);
	glVertex3f(10, standardY + 0.2, 445);
	glVertex3f(10, standardY + 0.2, 455);
	glVertex3f(-260, standardY + 0.2, 455);
	glEnd();

	glPopMatrix();

	//중앙선
	glPushMatrix();
	float yellow[] = { 1.0,1.0,0,1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, yellow);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);

	for (int i = -270; i < 280; i += 270) {
		glBegin(GL_LINES);
		glVertex3f(-500, standardY + 0.3, i);
		glVertex3f(500, standardY + 0.3, i);
		glEnd();
	}
	for (int i = -270; i < 280; i += 270) {
		glBegin(GL_LINES);
		glVertex3f(i, standardY + 0.3, -500);
		glVertex3f(i, standardY + 0.3, 500);
		glEnd();
	}
	glDisable(GL_LIGHTING);
}

void block11()
{
	glEnable(GL_LIGHTING);

	float blue[] = { 0.4,0.4,0.8,1.0 };
	float white[] = { 1,1,1,1 };
	float red[] = { 0.8,0.3,0.3,1.0 };

	glEnable(GL_NORMALIZE);
	glNormal3f(0, 1, 0);


	glMaterialfv(GL_FRONT, GL_AMBIENT, white);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);


	glBindTexture(GL_TEXTURE_2D, textureObject[0]);
	glBegin(GL_QUADS);
	//glNormal3f(1, 0, 0);
	glTexCoord2f(0, 0);
	glVertex3f(30, standardY, 30);
	glTexCoord2f(0, 1);
	glVertex3f(30, standardY + 300, 30);
	glTexCoord2f(1, 1);
	glVertex3f(130, standardY + 300, 30);
	glTexCoord2f(1, 0);
	glVertex3f(130, standardY, 30);

	glTexCoord2f(0, 0);
	glVertex3f(130, standardY, 30);
	glTexCoord2f(0, 1);
	glVertex3f(130, standardY + 300, 30);
	glTexCoord2f(1, 1);
	glVertex3f(130, standardY + 300, 130);
	glTexCoord2f(1, 0);
	glVertex3f(130, standardY, 130);

	glTexCoord2f(0, 0);
	glVertex3f(130, standardY, 130);
	glTexCoord2f(0, 1);
	glVertex3f(130, standardY + 300, 130);
	glTexCoord2f(1, 1);
	glVertex3f(30, standardY + 300, 130);
	glTexCoord2f(1, 0);
	glVertex3f(30, standardY, 130);

	glTexCoord2f(0, 0);
	glVertex3f(30, standardY, 130);
	glTexCoord2f(0, 1);
	glVertex3f(30, standardY + 300, 130);
	glTexCoord2f(1, 1);
	glVertex3f(30, standardY + 300, 30);
	glTexCoord2f(1, 0);
	glVertex3f(30, standardY, 30);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureObject[2]);
	glBegin(GL_QUADS);
	{
		//glNormal3f(0, 1, 0);
		glVertex3f(30, 100, 30);
		glVertex3f(130, 100, 30);
		glVertex3f(130, 150, 130);
		glVertex3f(30, 150, 130);

		glTexCoord2f(0, 1);
		glVertex3f(30, 150, 130);
		glTexCoord2f(1, 1);
		glVertex3f(130, 150, 130);
		glTexCoord2f(0, 0);
		glVertex3f(130, 100, 130);
		glTexCoord2f(1, 0);
		glVertex3f(30, 100, 130);
	}glEnd();

	//glBindTexture(GL_TEXTURE_2D, textureObject[2]);
	glBegin(GL_TRIANGLES);
	{
		glTexCoord2d(0, 0);
		glVertex3f(30, 100, 30);
		glTexCoord2d(1, 1);
		glVertex3f(30, 150, 130);
		glTexCoord2d(1, 0);
		glVertex3f(30, 100, 130);

		glTexCoord2d(0, 0);
		glVertex3f(130, 100, 30);
		glTexCoord2d(1, 1);
		glVertex3f(130, 150, 130);
		glTexCoord2d(1, 0);
		glVertex3f(130, 100, 130);
	}glEnd();



	glPopMatrix();
	//glPopMatrix();

	//------------------------------
	//중간건물--------------
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, textureObject[0]);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 1);
		glVertex3f(30, standardY + 350, 150);
		glTexCoord2d(0, 0);
		glVertex3f(30, standardY, 150);
		glTexCoord2d(1, 0);
		glVertex3f(30, standardY, 250);
		glTexCoord2d(1, 1);
		glVertex3f(30, standardY + 350, 250);


		glTexCoord2d(0, 1);
		glVertex3f(130, standardY + 350, 250);
		glTexCoord2d(0, 0);
		glVertex3f(130, standardY, 250);
		glTexCoord2d(1, 0);
		glVertex3f(130, standardY, 150);
		glTexCoord2d(1, 1);
		glVertex3f(130, standardY + 350, 150);

		glTexCoord2d(0, 1);
		glVertex3f(130, standardY + 350, 150);
		glTexCoord2d(0, 0);
		glVertex3f(130, standardY, 150);
		glTexCoord2d(1, 0);
		glVertex3f(130, standardY, 150);
		glTexCoord2d(1, 1);
		glVertex3f(130, standardY + 350, 150);

		glTexCoord2d(0, 1);
		glVertex3f(30, standardY + 350, 250);
		glTexCoord2d(0, 0);
		glVertex3f(30, standardY, 250);
		glTexCoord2d(1, 0);
		glVertex3f(130, standardY, 250);
		glTexCoord2d(1, 1);
		glVertex3f(130, standardY + 350, 250);
	}glEnd();

	glBindTexture(GL_TEXTURE_2D, textureObject[2]);
	glBegin(GL_QUADS);
	{
		//glColor3f(1, 1, 0);
		glTexCoord2d(1, 1);
		glVertex3f(30, 150, 150);
		glTexCoord2d(0, 1);
		glVertex3f(30, 150, 250);
		glTexCoord2d(0, 0);
		glVertex3f(130, 200, 250);
		glTexCoord2d(1, 0);
		glVertex3f(130, 200, 150);

		glTexCoord2d(1, 1);
		glVertex3f(130, 200, 150);
		glTexCoord2d(0, 1);
		glVertex3f(130, 200, 250);
		glTexCoord2d(0, 0);
		glVertex3f(130, 150, 250);
		glTexCoord2d(1, 0);
		glVertex3f(130, 150, 150);
	}glEnd();
	glBegin(GL_TRIANGLES);
	{
		glTexCoord2d(0, 0);
		glVertex3f(30, standardY + 350, 250);
		glTexCoord2d(1, 0);
		glVertex3f(130, standardY + 350, 250);
		glTexCoord2d(1, 1);
		glVertex3f(130, standardY + 400, 250);

		glTexCoord2d(0, 0);
		glVertex3f(30, standardY + 350, 150);
		glTexCoord2d(1, 0);
		glVertex3f(130, standardY + 350, 150);
		glTexCoord2d(1, 1);
		glVertex3f(130, standardY + 400, 150);
	}
	glPopMatrix();
	//큰건물--------------------
	glPushMatrix();

	glBegin(GL_QUADS);
	glVertex3f(150, standardY, 150);
	glVertex3f(150, standardY, 250);
	glVertex3f(250, standardY, 250);
	glVertex3f(250, standardY, 150);
	glEnd();

	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, textureObject[0]);

	glPushMatrix();

	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 1);
		glVertex3f(150, standardY, 250);
		glTexCoord2d(0, 0);
		glVertex3f(150, standardY + 400, 250);
		glTexCoord2d(1, 0);
		glVertex3f(250, standardY + 400, 250);
		glTexCoord2d(1, 1);
		glVertex3f(250, standardY, 250);

		glTexCoord2d(0, 1);
		glVertex3f(250, standardY + 400, 250);
		glTexCoord2d(0, 0);
		glVertex3f(250, standardY, 250);
		glTexCoord2d(1, 0);
		glVertex3f(250, standardY, 150);
		glTexCoord2d(1, 1);
		glVertex3f(250, standardY + 400, 150);

		glTexCoord2d(0, 1);
		glVertex3f(250, standardY + 400, 150);
		glTexCoord2d(0, 0);
		glVertex3f(250, standardY, 150);
		glTexCoord2d(1, 0);
		glVertex3f(150, standardY, 150);
		glTexCoord2d(1, 1);
		glVertex3f(150, standardY + 400, 150);

		glTexCoord2d(0, 1);
		glVertex3f(150, standardY + 400, 150);
		glTexCoord2d(0, 0);
		glVertex3f(150, standardY, 150);
		glTexCoord2d(1, 0);
		glVertex3f(150, standardY, 250);
		glTexCoord2d(1, 1);
		glVertex3f(150, standardY + 400, 250);

	}glEnd();

	glBindTexture(GL_TEXTURE_2D, textureObject[2]);
	glBegin(GL_QUADS);
	//glColor3f(1, 1, 0);,
	glVertex3f(150, 200, 250);
	glVertex3f(250, 200, 250);
	glVertex3f(250, 250, 150);
	glVertex3f(150, 250, 150);

	glVertex3f(250, 250, 150);
	glVertex3f(150, 250, 150);
	glVertex3f(150, 200, 150);
	glVertex3f(250, 200, 150);
	glEnd();

	glBegin(GL_TRIANGLES);
	{
		glTexCoord2d(0, 0);
		glVertex3f(250, 200, 250);
		glTexCoord2f(1, 0);
		glVertex3f(250, 200, 150);
		glTexCoord2f(1, 1);
		glVertex3f(250, 250, 150);

		glTexCoord2f(0, 0);
		glVertex3f(150, 200, 250);
		glTexCoord2f(1, 0);
		glVertex3f(150, 200, 150);
		glTexCoord2f(1, 1);
		glVertex3f(150, 250, 150);
	}glEnd();

	glPopMatrix();

	//제일 큰건물--------------
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, textureObject[0]);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 1);
		glVertex3f(150, standardY + 450, 130);
		glTexCoord2d(0, 0);
		glVertex3f(150, standardY, 130);
		glTexCoord2d(1, 0);
		glVertex3f(250, standardY, 130);
		glTexCoord2d(1, 1);
		glVertex3f(250, standardY + 450, 130);

		glTexCoord2d(0, 1);
		glVertex3f(250, standardY + 450, 130);
		glTexCoord2d(0, 0);
		glVertex3f(250, standardY, 130);
		glTexCoord2d(1, 0);
		glVertex3f(250, standardY, 30);
		glTexCoord2d(1, 1);
		glVertex3f(250, standardY + 450, 30);

		glTexCoord2d(0, 1);
		glVertex3f(250, standardY + 450, 30);
		glTexCoord2d(0, 0);
		glVertex3f(250, standardY, 30);
		glTexCoord2d(1, 0);
		glVertex3f(150, standardY, 30);
		glTexCoord2d(1, 1);
		glVertex3f(150, standardY + 450, 30);

		glTexCoord2d(0, 1);
		glVertex3f(150, standardY + 450, 30);
		glTexCoord2d(0, 0);
		glVertex3f(150, standardY, 30);
		glTexCoord2d(1, 0);
		glVertex3f(150, standardY, 130);
		glTexCoord2d(1, 1);
		glVertex3f(150, standardY + 450, 130);
	}glEnd();


	glBegin(GL_QUAD_STRIP);
	//glColor3f(1, 1, 0);
	glVertex3f(250, 250, 30);
	glVertex3f(250, 250, 130);
	glVertex3f(150, 300, 30);
	glVertex3f(150, 300, 130);
	glVertex3f(150, 250, 30);
	glVertex3f(150, 250, 130);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
}

void block10()
{
	glEnable(GL_LIGHTING);
	/*-----공원-----*/
	//잔디
	float grass[] = { 0.1,1,0.1,1,1 };
	float treeBody[] = { 0.3,0.2,0.2,1 };
	float treeLeaf[] = { 0,0.2,0 ,1 };
	float crane[] = { 0.8,0.8,0,1 };
	float black[] = { 0.3,0.3,0.3,1 };


	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textureObject[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3f(-190, standardY + 0.1, 160);
	glTexCoord2f(1, 1);
	glVertex3f(-70, standardY + 0.1, 160);
	glTexCoord2f(1, 0);
	glVertex3f(-70, standardY + 0.1, 370);
	glTexCoord2f(0, 0);
	glVertex3f(-190, standardY + 0.1, 370);
	glEnd();

	glPopMatrix();

	//펜스

	glPushMatrix();


	glBindTexture(GL_TEXTURE_2D, textureObject[8]);
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 1);
	glVertex3f(-250, standardY, 20);
	glTexCoord2d(1, 1);
	glVertex3f(-250, standardY + 50, 20);
	glTexCoord2d(1, 0);
	glVertex3f(-20, standardY + 50, 20);
	glTexCoord2d(0, 0);
	glVertex3f(-20, standardY, 20);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(0, 1);
	glVertex3f(-20, standardY, 20);
	glTexCoord2d(1, 1);
	glVertex3f(-20, standardY + 50, 20);
	glTexCoord2d(1, 0);
	glVertex3f(-20, standardY + 50, 130);
	glTexCoord2d(0, 0);
	glVertex3f(-20, standardY, 130);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(0, 1);
	glVertex3f(-20, standardY, 130);
	glTexCoord2d(1, 1);
	glVertex3f(-20, standardY + 50, 130);
	glTexCoord2d(1, 0);
	glVertex3f(-250, standardY + 50, 130);
	glTexCoord2d(0, 0);
	glVertex3f(-250, standardY, 130);
	glEnd();
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 1);
	glVertex3f(-250, standardY, 130);
	glTexCoord2d(1, 1);
	glVertex3f(-250, standardY + 50, 130);
	glTexCoord2d(1, 0);
	glVertex3f(-250, standardY + 50, 20);
	glTexCoord2d(0, 0);
	glVertex3f(-250, standardY, 20);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//나무
	for (int i = 0; i < 100; i += 10) {
		glPushMatrix();

		glMaterialfv(GL_FRONT, GL_AMBIENT, treeBody);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeBody);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeBody);

		glTranslatef(-185, standardY, 162 + i);
		glScalef(3, 30, 3);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, treeLeaf);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeLeaf);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeLeaf);
		glTranslatef(-185, standardY + 13, 162 + i);
		glutSolidSphere(5, 10, 10);
		glPopMatrix();
	}
	for (int i = 0; i < 100; i += 10) {
		glPushMatrix();

		glMaterialfv(GL_FRONT, GL_AMBIENT, treeBody);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeBody);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeBody);

		glTranslatef(-75, standardY, 162 + i);
		glScalef(3, 30, 3);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, treeLeaf);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeLeaf);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeLeaf);
		glTranslatef(-75, standardY + 13, 162 + i);
		glutSolidSphere(5, 10, 10);
		glPopMatrix();
	}
	for (int i = 0; i < 90; i += 9) {
		glPushMatrix();

		glMaterialfv(GL_FRONT, GL_AMBIENT, treeBody);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeBody);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeBody);

		glTranslatef(-75, standardY, 285 + i);
		glScalef(3, 30, 3);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, treeLeaf);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeLeaf);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeLeaf);
		glTranslatef(-75, standardY + 13, 285 + i);
		glutSolidSphere(5, 10, 10);
		glPopMatrix();
	}
	for (int i = 0; i < 90; i += 9) {
		glPushMatrix();

		glMaterialfv(GL_FRONT, GL_AMBIENT, treeBody);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeBody);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeBody);

		glTranslatef(-185, standardY, 285 + i);
		glScalef(3, 30, 3);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, treeLeaf);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeLeaf);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeLeaf);
		glTranslatef(-185, standardY + 13, 285 + i);
		glutSolidSphere(5, 10, 10);
		glPopMatrix();
	}
	for (int i = 0; i < 40; i += 8) {
		glPushMatrix();

		glMaterialfv(GL_FRONT, GL_AMBIENT, treeBody);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeBody);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeBody);

		glTranslatef(-185 + i, standardY, 162);
		glScalef(3, 30, 3);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, treeLeaf);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeLeaf);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeLeaf);
		glTranslatef(-185 + i, standardY + 13, 162);
		glutSolidSphere(5, 10, 10);
		glPopMatrix();
	}
	for (int i = 0; i > -40; i -= 8) {
		glPushMatrix();

		glMaterialfv(GL_FRONT, GL_AMBIENT, treeBody);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeBody);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeBody);

		glTranslatef(-75 + i, standardY, 162);
		glScalef(3, 30, 3);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, treeLeaf);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeLeaf);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeLeaf);
		glTranslatef(-75 + i, standardY + 13, 162);
		glutSolidSphere(5, 10, 10);
		glPopMatrix();
	}
	for (int i = 0; i > -40; i -= 8) {
		glPushMatrix();

		glMaterialfv(GL_FRONT, GL_AMBIENT, treeBody);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeBody);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeBody);

		glTranslatef(-75 + i, standardY, 365);
		glScalef(3, 30, 3);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, treeLeaf);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeLeaf);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeLeaf);
		glTranslatef(-75 + i, standardY + 13, 365);
		glutSolidSphere(5, 10, 10);
		glPopMatrix();
	}
	for (int i = 0; i < 40; i += 8) {
		glPushMatrix();

		glMaterialfv(GL_FRONT, GL_AMBIENT, treeBody);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeBody);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeBody);

		glTranslatef(-185 + i, standardY, 365);
		glScalef(3, 30, 3);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, treeLeaf);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeLeaf);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeLeaf);
		glTranslatef(-185 + i, standardY + 13, 365);
		glutSolidSphere(5, 10, 10);
		glPopMatrix();
	}

	//크레인
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, crane);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, crane);
	glMaterialfv(GL_FRONT, GL_SPECULAR, crane);

	glPushMatrix();
	glPushMatrix();
	glTranslatef(-220 - 10, standardY + 100, 70);
	glScalef(10, 200, 10);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-220 - 10, standardY + 180, 70);
	glRotatef(craneMove, 0, 1, 0);
	glPushMatrix();
	glTranslatef(30 - 10, 0, 0);
	glScalef(100, 7, 7);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glPushMatrix();
	glTranslatef(-70 + 10, standardY + 50, 80 + 10);
	glScalef(10, 170, 10);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-70 + 10, standardY + 120, 90);
	glRotatef(craneMove, 0, 1, 0);
	glPushMatrix();
	glTranslatef(0, 0, 20);
	glScalef(7, 7, 100);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();



	//지어지고 있는 건물
	float gray[] = { 0.6,0.6,0.6,1 };

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, gray);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, gray);

	glPushMatrix();  //건물1

	glTranslatef(-190, standardY + 50, 80);
	glScalef(60, 80, 60);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, black);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glMaterialfv(GL_FRONT, GL_SPECULAR, black);
	for (int i = 0; i < 50; i += 10) {
		glPushMatrix();
		glTranslatef(-215 + i, standardY + 50, 60);
		glScalef(2, 100, 2);
		glutSolidCube(1);
		glPopMatrix();
	}glPopMatrix();
	for (int i = 0; i < 60; i += 12) {
		glPushMatrix();
		glTranslatef(-215 + i, standardY + 50, 60 + 10);
		glScalef(2, 100, 2);
		glutSolidCube(1);
		glPopMatrix();

		for (int i = 0; i < 60; i += 12) {
			glPushMatrix();
			glTranslatef(-216 + i, standardY + 50, 60 + 20);
			glScalef(2, 100, 2);
			glutSolidCube(1);
			glPopMatrix();
		}
		for (int i = 0; i < 60; i += 12) {
			glPushMatrix();
			glTranslatef(-215 + i, standardY + 50, 60 + 30);
			glScalef(2, 100, 2);
			glutSolidCube(1);
			glPopMatrix();
		}
		for (int i = 0; i < 60; i += 12) {
			glPushMatrix();
			glTranslatef(-215 + i, standardY + 50, 60 + 40);
			glScalef(2, 100, 2);
			glutSolidCube(1);
			glPopMatrix();
		}

		glPushMatrix();
		glTranslatef(-100, standardY + 30, 90);
		glScalef(60, 80, 60);
		glutSolidCube(1);
		glPopMatrix();

		//육교
		float bridge[] = { 0.8,0.8,0.4,1 };
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, bridge);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, bridge);
		glMaterialfv(GL_FRONT, GL_SPECULAR, bridge);
		glTranslatef(-130, standardY + 1, 270);
		glScalef(3, 0.7, 3);
		glRotatef(90, 0, 1, 0);
		glutSolidTorus(3, 11, 10, 10);
		glPopMatrix();

		//주유소
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-230, standardY + 13, 190);
		glScalef(30, 6, 60);
		glutSolidCube(1);
		glPopMatrix();
		for (int i = 0; i < 21; i += 20) {
			glPushMatrix();
			glTranslatef(-240 + i, standardY + 5, 170);
			glScalef(4, 10, 4);
			glutSolidCube(1);
			glPopMatrix();
		}
		for (int i = 0; i < 21; i += 20) {
			glPushMatrix();
			glTranslatef(-240 + i, standardY + 5, 210);
			glScalef(4, 10, 4);
			glutSolidCube(1);
			glPopMatrix();
		}
		//glPushMatrix();
		glPushMatrix();
		glTranslatef(-230, standardY + 10, 235);
		glScalef(40, 30, 20);
		glutSolidCube(1);
		glPopMatrix();

		//glPopMatrix();

	}
	glDisable(GL_LIGHTING);
}

void block14()
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureObject[23]);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1);
	glVertex3f(-250, standardY + 0.1, 260);
	glTexCoord2d(1, 1);
	glVertex3f(-10, standardY + 0.1, 260);
	glTexCoord2d(1, 0);
	glVertex3f(-10, standardY + 0.1, 500);
	glTexCoord2d(0, 0);
	glVertex3f(-250, standardY + 0.1, 500);
	glEnd();
	glPopMatrix();

	//구멍난 건물(좌)
	glPushMatrix();

	glPushMatrix();

	glTranslatef(-225, standardY + 15, 295);
	glScalef(35, 40, 15);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-225, standardY + 15, 370);
	glScalef(35, 40, 15);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-210, standardY + 15, 333);
	glScalef(15, 40, 90);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-240, standardY + 15, 333);
	glScalef(15, 40, 90);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();


	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureObject[19]);

	glBegin(GL_QUADS);
	glTexCoord2d(0, 1);
	glVertex3f(-248, standardY + 35, 287);
	glTexCoord2d(1, 1);
	glVertex3f(-202, standardY + 35, 287);
	glTexCoord2d(1, 0);
	glVertex3f(-202, standardY, 287);
	glTexCoord2d(0, 0);
	glVertex3f(-248, standardY, 287);

	glTexCoord2d(0, 1);
	glVertex3f(-248, standardY + 35, 379);
	glTexCoord2d(1, 1);
	glVertex3f(-202, standardY + 35, 379);
	glTexCoord2d(1, 0);
	glVertex3f(-202, standardY, 379);
	glTexCoord2d(0, 0);
	glVertex3f(-248, standardY, 379);

	glTexCoord2d(0, 1);
	glVertex3f(-248, standardY + 35, 287);
	glTexCoord2d(1, 1);
	glVertex3f(-248, standardY + 35, 379);
	glTexCoord2d(1, 0);
	glVertex3f(-248, standardY, 379);
	glTexCoord2d(0, 0);
	glVertex3f(-248, standardY, 287);

	glTexCoord2d(0, 1);
	glVertex3f(-202, standardY + 35, 379);
	glTexCoord2d(1, 1);
	glVertex3f(-202, standardY + 35, 287);
	glTexCoord2d(1, 0);
	glVertex3f(-202, standardY, 287);
	glTexCoord2d(0, 0);
	glVertex3f(-202, standardY, 379);
	glEnd();
	glPopMatrix();
	//구멍난 건물(우)
	glPushMatrix();
	
	glTranslatef(-40, standardY + 15, 295);
	glScalef(35, 40, 15);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-40, standardY + 15, 370);
	glScalef(35, 40, 15);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-25, standardY + 15, 333);
	glScalef(15, 40, 90);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-55, standardY + 15, 333);
	glScalef(15, 40, 90);
	glutSolidCube(1);
	
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureObject[19]);
	glBegin(GL_QUADS);

	glTexCoord2d(0, 1);
	glVertex3f(-63, standardY + 35, 287);
	glTexCoord2d(1, 1);
	glVertex3f(-17, standardY + 35, 287);
	glTexCoord2d(1, 0);
	glVertex3f(-17, standardY, 287);
	glTexCoord2d(0, 0);
	glVertex3f(-63, standardY, 287);

	glTexCoord2d(0, 1);
	glVertex3f(-63, standardY + 35, 379);
	glTexCoord2d(1, 1);
	glVertex3f(-17, standardY + 35, 379);
	glTexCoord2d(1, 0);
	glVertex3f(-17, standardY, 379);
	glTexCoord2d(0, 0);
	glVertex3f(-63, standardY, 379);

	glTexCoord2d(0, 1);
	glVertex3f(-63, standardY + 35, 287);
	glTexCoord2d(1, 1);
	glVertex3f(-63, standardY + 35, 379);
	glTexCoord2d(1, 0);
	glVertex3f(-63, standardY, 379);
	glTexCoord2d(0, 0);
	glVertex3f(-63, standardY, 287);

	glTexCoord2d(0, 1);
	glVertex3f(-17, standardY + 35, 379);
	glTexCoord2d(1, 1);
	glVertex3f(-17, standardY + 35, 287);
	glTexCoord2d(1, 0);
	glVertex3f(-17, standardY, 287);
	glTexCoord2d(0, 0);
	glVertex3f(-17, standardY, 379);
	glEnd();
	glPopMatrix();

	glPushMatrix();

	//집1~3
	glPushMatrix();
	for (int i = 0; i < 120; i += 40) {
		glBindTexture(GL_TEXTURE_2D, textureObject[18]);
		glBegin(GL_QUADS);
		{
			glTexCoord2d(0, 1);
			glVertex3f(-245 + i, standardY + 20, 410);
			glTexCoord2d(1, 1);
			glVertex3f(-245 + i, standardY, 410);
			glTexCoord2d(1, 0);
			glVertex3f(-225 + i, standardY, 410);
			glTexCoord2d(0, 0);
			glVertex3f(-225 + i, standardY + 20, 410);

			glTexCoord2d(0, 1);
			glVertex3f(-225 + i, standardY + 20, 410);
			glTexCoord2d(1, 1);
			glVertex3f(-225 + i, standardY, 410);
			glTexCoord2d(1, 0);
			glVertex3f(-225 + i, standardY, 435);
			glTexCoord2d(0, 0);
			glVertex3f(-225 + i, standardY + 20, 435);

			glTexCoord2d(0, 1);
			glVertex3f(-225 + i, standardY + 20, 435);
			glTexCoord2d(1, 1);
			glVertex3f(-225 + i, standardY, 435);
			glTexCoord2d(1, 0);
			glVertex3f(-245 + i, standardY, 435);
			glTexCoord2d(0, 0);
			glVertex3f(-245 + i, standardY + 20, 435);

			glTexCoord2d(0, 1);
			glVertex3f(-245 + i, standardY + 20, 435);
			glTexCoord2d(1, 1);
			glVertex3f(-245 + i, standardY, 435);
			glTexCoord2d(1, 0);
			glVertex3f(-245 + i, standardY, 410);
			glTexCoord2d(0, 0);
			glVertex3f(-245 + i, standardY + 20, 410);
		}glEnd();
	}
	for (int i = 0; i < 120; i += 40) {
		glBindTexture(GL_TEXTURE_2D, textureObject[9]);
		glBegin(GL_QUADS);
		{
			glTexCoord2d(0, 1);
			glVertex3f(-250 + i, standardY + 17, 405);
			glTexCoord2d(1, 1);
			glVertex3f(-235 + i, standardY + 27, 405);
			glTexCoord2d(1, 0);
			glVertex3f(-235 + i, standardY + 27, 440);
			glTexCoord2d(0, 0);
			glVertex3f(-250 + i, standardY + 17, 440);

			glTexCoord2d(1, 1);
			glVertex3f(-235 + i, standardY + 27, 405);
			glTexCoord2d(0, 1);
			glVertex3f(-220 + i, standardY + 17, 405);
			glTexCoord2d(0, 0);
			glVertex3f(-220 + i, standardY + 17, 440);
			glTexCoord2d(1, 0);
			glVertex3f(-235 + i, standardY + 27, 440);

		}glEnd();
	}
	glPopMatrix();

	//집 4~6
	glPushMatrix();
	for (int i = 120; i < 240; i += 40) {
		glBindTexture(GL_TEXTURE_2D, textureObject[15]);
		glBegin(GL_QUADS);
		{
			glTexCoord2d(0, 1);
			glVertex3f(-245 + i, standardY + 20, 410);
			glTexCoord2d(1, 1);
			glVertex3f(-245 + i, standardY, 410);
			glTexCoord2d(1, 0);
			glVertex3f(-225 + i, standardY, 410);
			glTexCoord2d(0, 0);
			glVertex3f(-225 + i, standardY + 20, 410);

			glTexCoord2d(0, 1);
			glVertex3f(-225 + i, standardY + 20, 410);
			glTexCoord2d(1, 1);
			glVertex3f(-225 + i, standardY, 410);
			glTexCoord2d(1, 0);
			glVertex3f(-225 + i, standardY, 435);
			glTexCoord2d(0, 0);
			glVertex3f(-225 + i, standardY + 20, 435);

			glTexCoord2d(0, 1);
			glVertex3f(-225 + i, standardY + 20, 435);
			glTexCoord2d(1, 1);
			glVertex3f(-225 + i, standardY, 435);
			glTexCoord2d(1, 0);
			glVertex3f(-245 + i, standardY, 435);
			glTexCoord2d(0, 0);
			glVertex3f(-245 + i, standardY + 20, 435);

			glTexCoord2d(0, 1);
			glVertex3f(-245 + i, standardY + 20, 435);
			glTexCoord2d(1, 1);
			glVertex3f(-245 + i, standardY, 435);
			glTexCoord2d(1, 0);
			glVertex3f(-245 + i, standardY, 410);
			glTexCoord2d(0, 0);
			glVertex3f(-245 + i, standardY + 20, 410);
		}glEnd();
	}
	for (int i = 120; i < 240; i += 40) {
		glBindTexture(GL_TEXTURE_2D, textureObject[10]);
		glBegin(GL_QUADS);
		{
			glTexCoord2d(0, 1);
			glVertex3f(-250 + i, standardY + 17, 405);
			glTexCoord2d(1, 1);
			glVertex3f(-235 + i, standardY + 27, 405);
			glTexCoord2d(1, 0);
			glVertex3f(-235 + i, standardY + 27, 440);
			glTexCoord2d(0, 0);
			glVertex3f(-250 + i, standardY + 17, 440);

			glTexCoord2d(1, 1);
			glVertex3f(-235 + i, standardY + 27, 405);
			glTexCoord2d(0, 1);
			glVertex3f(-220 + i, standardY + 17, 405);
			glTexCoord2d(0, 0);
			glVertex3f(-220 + i, standardY + 17, 440);
			glTexCoord2d(1, 0);
			glVertex3f(-235 + i, standardY + 27, 440);

		}glEnd();
	}

	glPopMatrix();

	//집 6-7
	glPushMatrix();
	for (int i = 0; i < 120; i += 40) {
		glBindTexture(GL_TEXTURE_2D, textureObject[15]);
		glBegin(GL_QUADS);
		{
			glTexCoord2d(0, 1);
			glVertex3f(-245 + i, standardY + 20, 460);
			glTexCoord2d(1, 1);
			glVertex3f(-245 + i, standardY, 460);
			glTexCoord2d(1, 0);
			glVertex3f(-225 + i, standardY, 460);
			glTexCoord2d(0, 0);
			glVertex3f(-225 + i, standardY + 20, 460);

			glTexCoord2d(0, 1);
			glVertex3f(-225 + i, standardY + 20, 460);
			glTexCoord2d(1, 1);
			glVertex3f(-225 + i, standardY, 460);
			glTexCoord2d(1, 0);
			glVertex3f(-225 + i, standardY, 485);
			glTexCoord2d(0, 0);
			glVertex3f(-225 + i, standardY + 20, 485);

			glTexCoord2d(0, 1);
			glVertex3f(-225 + i, standardY + 20, 485);
			glTexCoord2d(1, 1);
			glVertex3f(-225 + i, standardY, 485);
			glTexCoord2d(1, 0);
			glVertex3f(-245 + i, standardY, 485);
			glTexCoord2d(0, 0);
			glVertex3f(-245 + i, standardY + 20, 485);

			glTexCoord2d(0, 1);
			glVertex3f(-245 + i, standardY + 20, 485);
			glTexCoord2d(1, 1);
			glVertex3f(-245 + i, standardY, 485);
			glTexCoord2d(1, 0);
			glVertex3f(-245 + i, standardY, 460);
			glTexCoord2d(0, 0);
			glVertex3f(-245 + i, standardY + 20, 460);
		}glEnd();
	}
	for (int i = 0; i < 120; i += 40) {
		glBindTexture(GL_TEXTURE_2D, textureObject[14]);
		glBegin(GL_QUADS);
		{
			glTexCoord2d(0, 1);
			glVertex3f(-250 + i, standardY + 17, 455);
			glTexCoord2d(1, 1);
			glVertex3f(-235 + i, standardY + 27, 455);
			glTexCoord2d(1, 0);
			glVertex3f(-235 + i, standardY + 27, 490);
			glTexCoord2d(0, 0);
			glVertex3f(-250 + i, standardY + 17, 490);

			glTexCoord2d(1, 1);
			glVertex3f(-235 + i, standardY + 27, 455);
			glTexCoord2d(0, 1);
			glVertex3f(-220 + i, standardY + 17, 455);
			glTexCoord2d(0, 0);
			glVertex3f(-220 + i, standardY + 17, 490);
			glTexCoord2d(1, 0);
			glVertex3f(-235 + i, standardY + 27, 490);

		}glEnd();
	}glPopMatrix();

	//8-10
	glPushMatrix();
	for (int i = 120; i < 240; i += 40) {
		glBindTexture(GL_TEXTURE_2D, textureObject[18]);
		glBegin(GL_QUADS);
		{
			glTexCoord2d(0, 1);
			glVertex3f(-245 + i, standardY + 20, 460);
			glTexCoord2d(1, 1);
			glVertex3f(-245 + i, standardY, 460);
			glTexCoord2d(1, 0);
			glVertex3f(-225 + i, standardY, 460);
			glTexCoord2d(0, 0);
			glVertex3f(-225 + i, standardY + 20, 460);

			glTexCoord2d(0, 1);
			glVertex3f(-225 + i, standardY + 20, 460);
			glTexCoord2d(1, 1);
			glVertex3f(-225 + i, standardY, 460);
			glTexCoord2d(1, 0);
			glVertex3f(-225 + i, standardY, 485);
			glTexCoord2d(0, 0);
			glVertex3f(-225 + i, standardY + 20, 485);

			glTexCoord2d(0, 1);
			glVertex3f(-225 + i, standardY + 20, 485);
			glTexCoord2d(1, 1);
			glVertex3f(-225 + i, standardY, 485);
			glTexCoord2d(1, 0);
			glVertex3f(-245 + i, standardY, 485);
			glTexCoord2d(0, 0);
			glVertex3f(-245 + i, standardY + 20, 485);

			glTexCoord2d(0, 1);
			glVertex3f(-245 + i, standardY + 20, 485);
			glTexCoord2d(1, 1);
			glVertex3f(-245 + i, standardY, 485);
			glTexCoord2d(1, 0);
			glVertex3f(-245 + i, standardY, 460);
			glTexCoord2d(0, 0);
			glVertex3f(-245 + i, standardY + 20, 460);
		}glEnd();
	}
	for (int i = 120; i < 240; i += 40) {
		glBindTexture(GL_TEXTURE_2D, textureObject[13]);
		glBegin(GL_QUADS);
		{
			glTexCoord2d(0, 1);
			glVertex3f(-250 + i, standardY + 17, 455);
			glTexCoord2d(1, 1);
			glVertex3f(-235 + i, standardY + 27, 455);
			glTexCoord2d(1, 0);
			glVertex3f(-235 + i, standardY + 27, 490);
			glTexCoord2d(0, 0);
			glVertex3f(-250 + i, standardY + 17, 490);

			glTexCoord2d(1, 1);
			glVertex3f(-235 + i, standardY + 27, 455);
			glTexCoord2d(0, 1);
			glVertex3f(-220 + i, standardY + 17, 455);
			glTexCoord2d(0, 0);
			glVertex3f(-220 + i, standardY + 17, 490);
			glTexCoord2d(1, 0);
			glVertex3f(-235 + i, standardY + 27, 490);

		}glEnd();

	}glPopMatrix();
	glPopMatrix();

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void block13()
{
	//공장
	glPushMatrix();
	//공장1
	glEnable(GL_TEXTURE_2D);



	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureObject[6]);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 1);
		glVertex3f(-480, standardY + 80, 480);
		glTexCoord2d(1, 1);
		glVertex3f(-380, standardY + 80, 480);
		glTexCoord2d(1, 0);
		glVertex3f(-380, standardY, 480);
		glTexCoord2d(0, 0);
		glVertex3f(-480, standardY, 480);

		glTexCoord2d(0, 1);
		glVertex3f(-480, standardY + 80, 430);
		glTexCoord2d(1, 1);
		glVertex3f(-380, standardY + 80, 430);
		glTexCoord2d(1, 0);
		glVertex3f(-380, standardY, 430);
		glTexCoord2d(0, 0);
		glVertex3f(-480, standardY, 430);

		glTexCoord2d(0, 1);
		glVertex3f(-380, standardY + 80, 480);
		glTexCoord2d(1, 1);
		glVertex3f(-380, standardY + 80, 430);
		glTexCoord2d(1, 0);
		glVertex3f(-380, standardY, 430);
		glTexCoord2d(0, 0);
		glVertex3f(-380, standardY, 480);

		glTexCoord2d(0, 1);
		glVertex3f(-480, standardY + 80, 430);
		glTexCoord2d(1, 1);
		glVertex3f(-480, standardY + 80, 480);
		glTexCoord2d(1, 0);
		glVertex3f(-480, standardY, 480);
		glTexCoord2d(0, 0);
		glVertex3f(-480, standardY, 430);

		glTexCoord2d(0, 1);
		glVertex3f(-480, standardY + 80, 430);
		glTexCoord2d(1, 1);
		glVertex3f(-445, standardY + 100, 430);
		glTexCoord2d(1, 0);
		glVertex3f(-445, standardY + 100, 480);
		glTexCoord2d(1, 1);
		glVertex3f(-480, standardY + 80, 480);

		glTexCoord2d(0, 1);
		glVertex3f(-445, standardY + 80, 430);
		glTexCoord2d(1, 1);
		glVertex3f(-410, standardY + 100, 430);
		glTexCoord2d(1, 0);
		glVertex3f(-410, standardY + 100, 480);
		glTexCoord2d(0, 0);
		glVertex3f(-445, standardY + 80, 480);

		glTexCoord2d(0, 1);
		glVertex3f(-410, standardY + 80, 430);
		glTexCoord2d(1, 1);
		glVertex3f(-380, standardY + 100, 430);
		glTexCoord2d(1, 0);
		glVertex3f(-380, standardY + 100, 480);
		glTexCoord2d(1, 1);
		glVertex3f(-410, standardY + 80, 480);

		glTexCoord2d(0, 1);
		glVertex3f(-380, standardY + 100, 480);
		glTexCoord2d(1, 1);
		glVertex3f(-380, standardY + 100, 430);
		glTexCoord2d(1, 0);
		glVertex3f(-380, standardY + 80, 430);
		glTexCoord2d(1, 1);
		glVertex3f(-380, standardY + 80, 480);
	}glEnd();

	for (int i = 0; i < 96; i += 32) {
		glBegin(GL_TRIANGLES);
		glTexCoord2d(0, 0);
		glVertex3f(-480 + i, standardY + 80, 480);
		glTexCoord2d(0, 1);
		glVertex3f(-445 + i, standardY + 100, 480);
		glTexCoord2d(1, 0);
		glVertex3f(-445 + i, standardY + 80, 480);
		glEnd();
		glBegin(GL_TRIANGLES);
		glTexCoord2d(0, 0);
		glVertex3f(-480 + i, standardY + 80, 430);
		glTexCoord2d(0, 1);
		glVertex3f(-445 + i, standardY + 100, 430);
		glTexCoord2d(1, 0);
		glVertex3f(-445 + i, standardY + 80, 430);
		glEnd();
	}
	glPopMatrix();

	//공장2
	glPushMatrix();
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 1);
		glVertex3f(-480, standardY + 80, 400);
		glTexCoord2d(1, 1);
		glVertex3f(-380, standardY + 80, 400);
		glTexCoord2d(1, 0);
		glVertex3f(-380, standardY, 400);
		glTexCoord2d(0, 0);
		glVertex3f(-480, standardY, 400);

		glTexCoord2d(0, 1);
		glVertex3f(-480, standardY + 80, 350);
		glTexCoord2d(1, 1);
		glVertex3f(-380, standardY + 80, 350);
		glTexCoord2d(1, 0);
		glVertex3f(-380, standardY, 350);
		glTexCoord2d(0, 0);
		glVertex3f(-480, standardY, 350);

		glTexCoord2d(0, 1);
		glVertex3f(-380, standardY + 80, 400);
		glTexCoord2d(1, 1);
		glVertex3f(-380, standardY + 80, 350);
		glTexCoord2d(1, 0);
		glVertex3f(-380, standardY, 350);
		glTexCoord2d(0, 0);
		glVertex3f(-380, standardY, 400);

		glTexCoord2d(0, 1);
		glVertex3f(-480, standardY + 80, 400);
		glTexCoord2d(1, 1);
		glVertex3f(-480, standardY + 80, 350);
		glTexCoord2d(1, 0);
		glVertex3f(-480, standardY, 350);
		glTexCoord2d(0, 0);
		glVertex3f(-480, standardY, 400);

		glTexCoord2d(0, 1);
		glVertex3f(-480, standardY + 80, 350);
		glTexCoord2d(1, 1);
		glVertex3f(-445, standardY + 100, 350);
		glTexCoord2d(1, 0);
		glVertex3f(-445, standardY + 100, 400);
		glTexCoord2d(0, 0);
		glVertex3f(-480, standardY + 80, 400);

		glTexCoord2d(0, 1);
		glVertex3f(-445, standardY + 80, 350);
		glTexCoord2d(1, 1);
		glVertex3f(-410, standardY + 100, 350);
		glTexCoord2d(1, 0);
		glVertex3f(-410, standardY + 100, 400);
		glTexCoord2d(0, 0);
		glVertex3f(-445, standardY + 80, 400);

		glTexCoord2d(0, 1);
		glVertex3f(-410, standardY + 80, 350);
		glTexCoord2d(1, 1);
		glVertex3f(-380, standardY + 100, 350);
		glTexCoord2d(1, 0);
		glVertex3f(-380, standardY + 100, 400);
		glTexCoord2d(0, 0);
		glVertex3f(-410, standardY + 80, 400);

		glTexCoord2d(0, 1);
		glVertex3f(-380, standardY + 100, 350);
		glTexCoord2d(1, 1);
		glVertex3f(-380, standardY + 100, 400);
		glTexCoord2d(1, 0);
		glVertex3f(-380, standardY + 80, 400);
		glTexCoord2d(0, 0);
		glVertex3f(-380, standardY + 80, 350);
	}glEnd();

	for (int i = 0; i < 96; i += 32) {
		glBegin(GL_TRIANGLES);
		glTexCoord2d(0, 0);
		glVertex3f(-480 + i, standardY + 80, 400);
		glTexCoord2d(0, 1);
		glVertex3f(-445 + i, standardY + 100, 400);
		glTexCoord2d(1, 0);
		glVertex3f(-445 + i, standardY + 80, 400);
		glEnd();
		glBegin(GL_TRIANGLES);
		glTexCoord2d(0, 0);
		glVertex3f(-480 + i, standardY + 80, 350);
		glTexCoord2d(0, 1);
		glVertex3f(-445 + i, standardY + 100, 350);
		glTexCoord2d(1, 0);
		glVertex3f(-445 + i, standardY + 80, 350);
		glEnd();
	}
	glPopMatrix();

	glPopMatrix();

	//담

	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, textureObject[7]);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 1);
		glVertex3f(-290, standardY + 10, 500);
		glTexCoord2d(1, 1);
		glVertex3f(-290, standardY + 10, 280);
		glTexCoord2d(1, 0);
		glVertex3f(-290, standardY, 280);
		glTexCoord2d(0, 0);
		glVertex3f(-290, standardY, 500);
	}glEnd();
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 1);
		glVertex3f(-500, standardY + 10, 280);
		glTexCoord2d(1, 1);
		glVertex3f(-290, standardY + 10, 280);
		glTexCoord2d(1, 0);
		glVertex3f(-290, standardY, 280);
		glTexCoord2d(0, 0);
		glVertex3f(-500, standardY, 280);
	}glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	//굴뚝1
	glPushMatrix();
	glTranslatef(-442, standardY + 110, 455);
	glRotatef(90, 1, 0, 0);
	gluCylinder(p, 7, 7, 30, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-408, standardY + 110, 455);
	glRotatef(90, 1, 0, 0);
	gluCylinder(p, 7, 7, 30, 20, 20);
	glPopMatrix();

	//굴뚝2
	glPushMatrix();
	glTranslatef(-442, standardY + 110, 375);
	glRotatef(90, 1, 0, 0);
	gluCylinder(p, 7, 7, 30, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-408, standardY + 110, 375);
	glRotatef(90, 1, 0, 0);
	gluCylinder(p, 7, 7, 30, 20, 20);
	glPopMatrix();


	//창고
	glPushMatrix();
	glTranslatef(-380, standardY + 10, 310);
	glScalef(100, 30, 30);
	glutSolidCube(1);
	glPopMatrix();
	float roof[] = { 0.0,0.0,1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, roof);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, roof);
	glMaterialfv(GL_FRONT, GL_SPECULAR, roof);
	glPushMatrix();
	glTranslatef(-380, standardY + 30, 300);
	glRotatef(-35, 1, 0, 0);
	glScalef(120, 1, 23);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-380, standardY + 30, 320);
	glRotatef(35, 1, 0, 0);
	glScalef(120, 1, 24);
	glutSolidCube(1);
	glPopMatrix();

	float gray[] = { 0.4,0.4,0.4 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, gray);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, gray);

	//원통1
	glPushMatrix();
	glTranslatef(-330, standardY + 40, 460);
	glRotatef(90, 1, 0, 0);
	gluCylinder(p, 20, 20, 40, 20, 40);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-330, standardY + 40, 460);
	glRotatef(90, 1, 0, 0);
	glutSolidCone(20, 3, 20, 20);
	glPopMatrix();

	//원통2
	glPushMatrix();
	glTranslatef(-330, standardY + 40, 390);
	glRotatef(90, 1, 0, 0);
	gluCylinder(p, 20, 20, 40, 20, 40);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-330, standardY + 40, 390);
	glRotatef(90, 1, 0, 0);
	glutSolidCone(20, 3, 20, 20);
	glPopMatrix();



	glDisable(GL_LIGHTING);
}

void block16()
{
	glEnable(GL_TEXTURE_2D);
	//축구장(잔디)
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureObject[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3f(320, standardY + 0.2, 340);
	glTexCoord2f(1, 1);
	glVertex3f(450, standardY + 0.2, 340);
	glTexCoord2f(1, 0);
	glVertex3f(450, standardY + 0.2, 440);
	glTexCoord2f(0, 0);
	glVertex3f(320, standardY + 0.2, 440);
	glEnd();
	glPopMatrix();

	//관중석
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureObject[4]);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 1);
		glVertex3f(320, standardY, 440);
		glTexCoord2d(1, 1);
		glVertex3f(450, standardY, 440);
		glTexCoord2d(1, 0);
		glVertex3f(450, standardY + 40, 470);
		glTexCoord2d(0, 0);
		glVertex3f(320, standardY + 40, 470);

		glVertex3f(320, standardY + 40, 470);
		glVertex3f(450, standardY + 40, 470);
		glVertex3f(450, standardY, 470);
		glVertex3f(320, standardY, 470);

		glTexCoord2d(0, 1);
		glVertex3f(320, standardY + 40, 310);
		glTexCoord2d(1, 1);
		glVertex3f(450, standardY + 40, 310);
		glTexCoord2d(1, 0);
		glVertex3f(450, standardY, 340);
		glTexCoord2d(0, 0);
		glVertex3f(320, standardY, 340);

		glVertex3f(320, standardY + 40, 310);
		glVertex3f(450, standardY + 40, 310);
		glVertex3f(450, standardY, 310);
		glVertex3f(320, standardY, 310);

		glTexCoord2d(0, 1);
		glVertex3f(295, standardY + 40, 450);
		glTexCoord2d(1, 1);
		glVertex3f(295, standardY + 40, 330);
		glTexCoord2d(1, 0);
		glVertex3f(320, standardY, 330);
		glTexCoord2d(0, 0);
		glVertex3f(320, standardY, 450);

		glVertex3f(295, standardY + 40, 330);
		glVertex3f(295, standardY + 40, 450);
		glVertex3f(295, standardY, 450);
		glVertex3f(295, standardY, 330);

		glTexCoord2d(0, 1);
		glVertex3f(475, standardY + 40, 330);
		glTexCoord2d(1, 1);
		glVertex3f(475, standardY + 40, 450);
		glTexCoord2d(1, 0);
		glVertex3f(450, standardY, 450);
		glTexCoord2d(0, 0);
		glVertex3f(450, standardY, 330);

		glVertex3f(475, standardY + 40, 450);
		glVertex3f(475, standardY + 40, 330);
		glVertex3f(475, standardY, 330);
		glVertex3f(475, standardY, 450);

		glVertex3f(295, standardY + 40, 450);
		glVertex3f(320, standardY + 40, 470);
		glVertex3f(320, standardY, 470);
		glVertex3f(295, standardY, 450);

		glVertex3f(450, standardY + 40, 470);
		glVertex3f(475, standardY + 40, 450);
		glVertex3f(475, standardY, 450);
		glVertex3f(450, standardY, 470);

		glVertex3f(295, standardY + 40, 330);
		glVertex3f(320, standardY + 40, 310);
		glVertex3f(320, standardY, 310);
		glVertex3f(295, standardY, 330);

		glVertex3f(450, standardY + 40, 310);
		glVertex3f(475, standardY + 40, 330);
		glVertex3f(475, standardY, 330);
		glVertex3f(450, standardY, 310);
	}glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void block15()
{
	glEnable(GL_TEXTURE_2D);
	//ground
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureObject[5]);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1);
	glVertex3f(10, standardY + 0.1, 260);
	glTexCoord2d(1, 1);
	glVertex3f(260, standardY + 0.1, 260);
	glTexCoord2d(1, 0);
	glVertex3f(260, standardY + 0.1, 500);
	glTexCoord2d(0, 0);
	glVertex3f(10, standardY + 0.1, 500);
	glEnd();
	glPopMatrix();

	//국회의사당
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureObject[21]);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 1);
		glVertex3f(40, standardY + 60, 480);
		glTexCoord2d(1, 1);
		glVertex3f(220, standardY + 60, 480);
		glTexCoord2d(1, 0);
		glVertex3f(220, standardY, 480);
		glTexCoord2d(0, 0);
		glVertex3f(40, standardY, 480);

		glTexCoord2d(0, 1);
		glVertex3f(40, standardY + 60, 410);
		glTexCoord2d(1, 1);
		glVertex3f(220, standardY + 60, 410);
		glTexCoord2d(1, 0);
		glVertex3f(220, standardY, 410);
		glTexCoord2d(0, 0);
		glVertex3f(40, standardY, 410);

		glTexCoord2d(0, 1);
		glVertex3f(40, standardY + 60, 410);
		glTexCoord2d(1, 1);
		glVertex3f(40, standardY + 60, 480);
		glTexCoord2d(1, 0);
		glVertex3f(40, standardY, 480);
		glTexCoord2d(0, 0);
		glVertex3f(40, standardY, 410);

		glTexCoord2d(0, 1);
		glVertex3f(220, standardY + 60, 410);
		glTexCoord2d(1, 1);
		glVertex3f(220, standardY + 60, 480);
		glTexCoord2d(1, 0);
		glVertex3f(220, standardY, 480);
		glTexCoord2d(0, 0);
		glVertex3f(220, standardY, 410);
	}glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);

	float gray[] = { 0.5,0.5,0.5 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, gray);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, gray);

	glPushMatrix();
	glTranslatef(130, standardY + 60, 445);
	glScalef(200, 7, 90);
	glutSolidCube(1);
	glPopMatrix();

	for (int i = 0; i < 216; i += 27) {
		glPushMatrix();
		glTranslatef(37 + i, standardY + 30, 485);
		glScalef(3, 60, 3);
		glutSolidCube(1);
		glPopMatrix();
	}
	for (int i = 0; i < 216; i += 27) {
		glPushMatrix();
		glTranslatef(37 + i, standardY + 30, 405);
		glScalef(3, 60, 3);
		glutSolidCube(1);
		glPopMatrix();
	}
	for (int i = 0; i < 81; i += 27) {
		glPushMatrix();
		glTranslatef(35, standardY + 30, 405 + i);
		glScalef(3, 60, 3);
		glutSolidCube(1);
		glPopMatrix();
	}
	for (int i = 0; i < 81; i += 27) {
		glPushMatrix();
		glTranslatef(225, standardY + 30, 405 + i);
		glScalef(3, 60, 3);
		glutSolidCube(1);
		glPopMatrix();
	}
	glPushMatrix();
	float dome[] = { 0.4,0.6,1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, dome);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, dome);
	glMaterialfv(GL_FRONT, GL_SPECULAR, dome);
	glTranslatef(130, standardY + 65, 445);
	glutSolidSphere(35, 20, 20);
	glPopMatrix();

	glPushMatrix();
	float torus[] = { 0.3,0.3,0.3 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, torus);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, torus);
	glMaterialfv(GL_FRONT, GL_SPECULAR, torus);
	glTranslatef(130, standardY + 65, 445);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(3, 38, 20, 20);
	glPopMatrix();

	glPopMatrix();


	glDisable(GL_LIGHTING);
}


void block12()
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, textureObject[22]);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1);
	glVertex3f(270, standardY+0.1, 10);
	glTexCoord2d(1, 1);
	glVertex3f(500, standardY+0.1, 10);
	glTexCoord2d(1, 0);
	glVertex3f(500, standardY+0.1, 255);
	glTexCoord2d(0, 0);
	glVertex3f(270, standardY+0.1, 255);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	
	glEnable(GL_LIGHTING);

	float brown[] = { 1,0.5,0 };
	float gray[] = { 0.6,0.6,0.6 };
	float blue[] = { 0,0,1 };

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, brown);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, brown);
	glMaterialfv(GL_FRONT, GL_SPECULAR, brown);
	glBegin(GL_QUADS);
	glVertex3f(270, standardY + 0.2, 120);
	glVertex3f(500, standardY + 0.2, 120);
	glVertex3f(500, standardY + 0.2, 130);
	glVertex3f(270, standardY + 0.2, 130);

	glVertex3f(375, standardY + 0.2, 10);
	glVertex3f(385, standardY + 0.2, 10);
	glVertex3f(385, standardY + 0.2, 250);
	glVertex3f(375, standardY + 0.2, 250);
	glEnd();
	glPopMatrix();

	//분수
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, gray);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, gray);
	glTranslatef(385, standardY, 120);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 1);
	glutSolidTorus(10, 20, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, blue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, blue);
		glPushMatrix();
		glTranslatef(385, standardY +water, 120);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(385, standardY + 8+water, 120);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(385, standardY + 16+water, 120);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(385, standardY + 24+water, 120);
		glutSolidSphere(3,5, 5);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(385, standardY + 32+water, 120);
		glutSolidSphere(3, 5,5);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(380, standardY + water, 120);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(378, standardY + 6 + water, 120);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(376, standardY + 12 + water, 120);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(374, standardY + 18 + water, 120);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(372, standardY + 24 + water, 120);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(390, standardY + water, 120);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(392, standardY + 6 + water, 120);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(394, standardY + 12 + water, 120);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(396, standardY + 18 + water, 120);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(398, standardY + 24 + water, 120);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(385, standardY + water, 110);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(385, standardY + 6 + water, 108);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(385, standardY + 12 + water, 106);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(385, standardY + 18 + water, 104);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(385, standardY + 24 + water, 102);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(385, standardY + water, 120);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(385, standardY + 6 + water, 122);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(385, standardY + 12 + water, 124);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(385 ,standardY + 18 + water, 124);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(385, standardY + 24 + water, 128);
		glutSolidSphere(3, 5, 5);
		glPopMatrix();
	glPopMatrix();

	

	glDisable(GL_LIGHTING);
}


void block9()
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureObject[24]);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1);
	glVertex3f(-500, standardY + 0.1, 10);
	glTexCoord2d(1, 1);
	glVertex3d(-260, standardY + 0.1, 10);
	glTexCoord2d(1, 0);
	glVertex3f(-260, standardY + 0.1, 250);
	glTexCoord2d(0, 0);
	glVertex3f(-500, standardY + 0.1, 250);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glPushMatrix();
	float ufo[] = { 0,0.4,0.6};

	glMaterialfv(GL_FRONT, GL_AMBIENT, ufo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ufo);
	glMaterialfv(GL_FRONT, GL_SPECULAR,ufo);
	glTranslatef(-390, standardY + 100 + ufoMove, 100);
	glScalef(1, 0.1, 1);
	glutSolidSphere(80, 20, 20);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-390, standardY + 100 + ufoMove, 100);
	glutSolidSphere(30, 20, 20);
	glPopMatrix();

	//사람
	glPushMatrix();
	glTranslatef(-390, standardY + 100 , 100);
	human();
	glPopMatrix();

	glDisable(GL_LIGHTING);

	//glColor4f(1, 1, 1, 1);
	glPushMatrix();
	/*float yellow[] = { 1,1,0,};

	glMaterialfv(GL_FRONT, GL_AMBIENT, yellow);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);*/

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);
	glColor4f(1, 1, 0.6, 0.7);
	glTranslatef(-390, standardY + 120 , 100);
	glRotatef(90, 1, 0, 0);
	
	gluCylinder(p, 15, 15, 200, 20, 1);
	glDisable(GL_BLEND);
	glPopMatrix();
	
	glColor4f(1, 1, 1, 1);
}


void human()
{
	glTranslatef(0, move, 0);
	glPushMatrix();
	glPushMatrix();
	glScalef(0.2, 0.8, 0.2);
	glTranslatef(0, -40, 0);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glRotatef(leg_rotate, 0, 0, 1);
	glTranslatef(0, -45, 0);
	glScalef(0.07, 1, 0.07);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-leg_rotate, 0, 0, 1);
	glTranslatef(0, -45, 0);
	glScalef(0.07, 1, 0.07);
	glutSolidCube(10);
	glPopMatrix();

	glPopMatrix();
}

void footballPlay()
{
	glPushMatrix();
	glEnable(GL_LIGHTING);
	float black[] = { 1,1,0.1,1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, black);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glMaterialfv(GL_FRONT, GL_SPECULAR, black);


	glTranslatef(350 + ballX, standardY, 370 + ballZ);
	glutSolidSphere(2, 10, 10);
	glPopMatrix();

	//glPushMatrix();

	glDisable(GL_LIGHTING);
}

void factorySmoke()
{
	glEnable(GL_LIGHTING);

	float gray[] = { 0.5,0.5,0.5};

	glMaterialfv(GL_FRONT, GL_AMBIENT, gray);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, gray);

	//연기1
	glPushMatrix();
	glTranslatef(-442, standardY + 130 , 455);
	glutSolidSphere(block13_smoke[0], 5, 5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-442, standardY + 150 , 455);
	glutSolidSphere(block13_smoke[1], 5, 5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-442, standardY + 180, 455);
	glutSolidSphere(block13_smoke[2], 5, 5);
	glPopMatrix();

	//연기2
	glPushMatrix();
	glTranslatef(-408, standardY + 130, 455);
	glutSolidSphere(block13_smoke[0], 5, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-408, standardY + 150, 455);
	glutSolidSphere(block13_smoke[1], 5, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-408, standardY + 180, 455);
	glutSolidSphere(block13_smoke[2], 5, 5);
	glPopMatrix();
	//연기3
	glPushMatrix();
	glTranslatef(-442, standardY + 130, 375);
	glutSolidSphere(block13_smoke[0], 5, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-442, standardY + 150 , 375);
	glutSolidSphere(block13_smoke[1], 5, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-442, standardY + 180, 375);
	glutSolidSphere(block13_smoke[2], 5, 5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-408, standardY + 130 , 375);
	glutSolidSphere(block13_smoke[0], 5, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-408, standardY + 150 , 375);
	glutSolidSphere(block13_smoke[1], 5, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-408, standardY + 180, 375);
	glutSolidSphere(block13_smoke[2], 5, 5);
	glPopMatrix();

	glDisable(GL_LIGHTING);

}

float point[3][3][3] = { {{-4,0,4},{-2,4,4},{4,0,4}},{{-4,0,0},{-2,4,0}
					,{4,0,0}},{{-4,0,-4},{-2,4,-4},{4,0,-4}} };
void mountain()
{
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &point[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(10, 0, 1, 10, 0, 1);
	glEvalMesh2(GL_LINE, 0, 10, 0, 10);

	glPointSize(2.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			glVertex3fv(point[i][j]);
	glEnd();
}

void building() {
	glPushMatrix();
	for (int i = 0; i < 4; i++) {
		glRotatef(90, 0, 1, 0);
		glPushMatrix();
		glTranslatef(-75, 0, 75);
		for (int j = 0; j < 15; j++) {
			for (int k = 0; k < 5; k++) {
				glColor3f(0.3, 0.3, 0.9);
				glRectf(0, 0, 30, 30);
				glTranslatef(30, 0, 0);
			}
			glTranslatef(-150, 30, 0);
		}
		glPopMatrix();
	}
	glTranslatef(0, 450, 0);
	glBegin(GL_POLYGON);
	glVertex3f(-75, 0, -75);
	glVertex3f(-75, 0, 75);
	glVertex3f(75, 0, 75);
	glVertex3f(75, 0, -75);
	glEnd();
	glPopMatrix();


}

void block2() {
	//first line
	glPushMatrix();
	glTranslatef(-90, -200, 90);
	glPushMatrix();
	glScalef(0.3, 0.3 + block2_[0], 0.3);
	building();
	glPopMatrix();

	glTranslatef(50, 0, 0);
	glPushMatrix();
	glScalef(0.3, 0.5 + block2_[1], 0.3);
	building();
	glPopMatrix();

	glTranslatef(50, 0, 0);
	glPushMatrix();
	glScalef(0.5, 0.5 + block2_[2], 0.3);
	building();
	glPopMatrix();

	glTranslatef(70, 0, 0);
	glPushMatrix();
	glScalef(0.3, 0.7 + block2_[3], 0.3);
	building();
	glPopMatrix();

	glPopMatrix();

	//second line
	glPushMatrix();
	glTranslatef(-90, -200, 10);
	glPushMatrix();
	glScalef(0.3, 0.76 + block2_[4], 0.3);
	building();
	glPopMatrix();

	glTranslatef(90, 0, 0);
	glScalef(0.5, 1.2 + block2_[5], 0.5);
	glPushMatrix();
	for (int i = 0; i < 4; i++) {
		glRotatef(90, 0, 1, 0);
		glPushMatrix();
		glTranslatef(-75, 0, 75);
		for (int j = 0; j < 15; j++) {
			for (int k = 0; k < 5; k++) {
				glRectf(0, 0, 30, 30);
				glTranslatef(30, 0, 0);
			}
			glTranslatef(-150, 30, 0);
		}
		glPopMatrix();
	}
	glTranslatef(0, 450, 0);
	glBegin(GL_POLYGON);
	glVertex3f(-75, 0, -75);
	glVertex3f(-75, 0, 75);
	glVertex3f(75, 0, 75);
	glVertex3f(75, 0, -75);
	glEnd();
	glPopMatrix();

	glTranslatef(180, 0, 0);
	glPushMatrix();
	glScalef(0.4, 1.0 + block2_[6], 0.4);
	building();
	glPopMatrix();

	glPopMatrix();

	//third line
	glPushMatrix();
	glTranslatef(-90, -200, -70);
	glPushMatrix();
	glScalef(0.3, 0.3 + block2_[7], 0.3);
	building();
	glPopMatrix();

	glTranslatef(60, 0, 0);
	glPushMatrix();
	glScalef(0.3, 0.5 + block2_[8], 0.3);
	building();
	glPopMatrix();
	glTranslatef(50, 0, 0);
	glPushMatrix();
	glScalef(0.3, 0.4, 0.3);
	building();
	glPopMatrix();

	glTranslatef(60, 0, 0);
	glPushMatrix();
	glScalef(0.4, 0.7 + block2_[9], 0.4);
	building();
	glPopMatrix();

	glPopMatrix();


	for (int i = 0; i < 10; i++)
		block2_[i] += block2_flag[i] = (block2_[i] > 0.5 ? -0.01 : (block2_[i] < 0.0) ? 0.01 : block2_flag[i]);
}

void block6() {
	glPushMatrix();
	glTranslatef(80, -200, 80);

	glPushMatrix();
	glScalef(0.3, 0.7, 0.3);
	building();
	glPopMatrix();
	glTranslatef(-70, 0, 0);
	glPushMatrix();
	glScalef(0.3, 0.9, 0.3);
	building();
	glPopMatrix();
	glTranslatef(-70, 0, 0);
	glPushMatrix();
	glScalef(0.3, 1.4, 0.3);
	building();
	glPopMatrix();
	glTranslatef(140, 0, -70);

	glPushMatrix();
	glScalef(0.3, 0.7, 0.3);
	building();
	glPopMatrix();
	glTranslatef(-70, 0, 0);
	glPushMatrix();
	glScalef(0.3, 0.9, 0.3);
	building();
	glPopMatrix();
	glTranslatef(-70, 0, 0);
	glPushMatrix();
	glScalef(0.3, 1.3, 0.3);
	building();
	glPopMatrix();
	glTranslatef(140, 0, -70);

	glPushMatrix();
	glScalef(0.3, 1.5, 0.3);
	building();
	glPopMatrix();
	glTranslatef(-70, 0, 0);
	glPushMatrix();
	glScalef(0.3, 2.0, 0.3);
	building();
	glPopMatrix();
	glTranslatef(-70, 0, 0);
	glPushMatrix();
	glScalef(0.3, 1.5, 0.3);
	building();
	glPopMatrix();

	glPopMatrix();
}

void house() {
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(50, 50, 50);
	glScalef(1, 5, 1);
	glutSolidCube(10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 50, -30);
	glScalef(10, 5, 3);
	glutSolidCube(10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-50, 50, 10);
	glScalef(3, 5, 10);
	glutSolidCube(10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 100, 10);
	glScalef(12, 5, 10);
	glutSolidCube(11);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(65, 100, 40);
	glColor3f(0.3, 0.3, 0.7);
	glScalef(1, 5, 5);
	glutSolidCube(5);
	glTranslatef(0, 0, -5);
	glutSolidCube(5);
	glTranslatef(0, 0, -7);
	glutSolidCube(5);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(65, 100, 20);
	glScalef(1, 5, 5);
	glutSolidCube(5);
	glTranslatef(0, 0, -6);
	glutSolidCube(5);
	glTranslatef(0, 0, -6);
	glutSolidCube(5);
	glPopMatrix();
}

void block3() {
	glPushMatrix();
	glTranslatef(90, -200, 90);
	glPushMatrix();
	glRotatef(30, 0, 1, 0);
	glScalef(0.3, 0.3, 0.3);
	house();
	glPopMatrix();

	glTranslatef(-90, 0, 0);
	glPushMatrix();
	glRotatef(-30, 0, 1, 0);
	glScalef(0.3, 0.3, 0.3);
	house();
	glPopMatrix();

	glTranslatef(-90, 0, 0);
	glPushMatrix();
	glScalef(0.3, 0.3, 0.3);
	house();
	glPopMatrix();

	glTranslatef(180, 0, -90);
	glPushMatrix();
	glRotatef(-30, 0, 1, 0);
	glScalef(0.3, 0.3, 0.3);
	house();
	glPopMatrix();

	glTranslatef(-90, 0, 0);
	glPushMatrix();
	glRotatef(-60, 0, 1, 0);
	glScalef(0.3, 0.3, 0.3);
	house();
	glPopMatrix();

	glTranslatef(-90, 0, 0);
	glPushMatrix();
	glRotatef(0, 0, 1, 0);
	glScalef(0.3, 0.3, 0.3);
	house();
	glPopMatrix();

	glTranslatef(180, 0, -90);
	glPushMatrix();
	glRotatef(-60, 0, 1, 0);
	glScalef(0.3, 0.3, 0.3);
	house();
	glPopMatrix();

	glTranslatef(-90, 0, 0);
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glScalef(0.3, 0.3, 0.3);
	house();
	glPopMatrix();

	glTranslatef(-90, 0, 0);
	glPushMatrix();
	glRotatef(50, 0, 1, 0);
	glScalef(0.3, 0.3, 0.3);
	house();
	glPopMatrix();

	glPopMatrix();
}




void Big_Circle() {
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(0, 150, 0);
	glPointSize(5);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		glVertex3f(200 * cos(i / 180.0*3.141592), 200 * sin(i / 180.0*3.141592), 0);
	}
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glPushMatrix();
	glTranslatef(0, 0, 30);
	glScalef(1, 40, 1);
	glutSolidCube(10);
	glPopMatrix();
	glTranslatef(0, 150, 30);
	glPointSize(5);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		glVertex3f(200 * cos(i / 180.0*3.141592), 200 * sin(i / 180.0*3.141592), 0);
	}
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glPushMatrix();
	glTranslatef(0, 0, -30);
	glScalef(1, 40, 1);
	glutSolidCube(10);
	glPopMatrix();
	glTranslatef(0, 150, -30);
	glPointSize(5);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		glVertex3f(200 * cos(i / 180.0*3.141592), 200 * sin(i / 180.0*3.141592), 0);
	}
	glEnd();
	glPopMatrix();

	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(0, 150, 0);
	for (int i = 0; i < 360; i += 20) {
		glPushMatrix();
		glTranslatef(200 * cos((i + block4_rota) / 180.0*3.141592), 200 * sin((i + block4_rota) / 180.0*3.141592), 0);
		glutSolidSphere(30, 15, 15);
		glPopMatrix();
	}
	glPopMatrix();
	block4_rota = (block4_rota >= 360 ? 0 : block4_rota + 1);

}

void tree() {
	glColor3f(0.3, 0.3, 0);
	glPushMatrix();
	glTranslatef(0, 50, 0);
	glScalef(1, 10, 1);
	glutSolidCube(10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 100, 0);
	glColor3f(0, 0.6, 0);
	glutSolidSphere(50, 15, 15);
	glTranslatef(20, -20, 10);
	glutSolidSphere(40, 15, 15);
	glTranslatef(-40, 10, 0);
	glutSolidSphere(40, 15, 15);
	glTranslatef(20, -10, -20);
	glutSolidSphere(40, 15, 15);
	glPopMatrix();
}

void block4() {
	glPushMatrix();
	glTranslatef(100, -200, 100);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			glPushMatrix();
			glScalef(0.5, 0.5, 0.5);
			tree();
			glPopMatrix();
			glTranslatef(-40, 0, 0);

		}
		glTranslatef(200, 0, -40);
	}
	glPopMatrix();
	Big_Circle();
}


void solasystem() {
	glPushMatrix();

	glColor3f(0.5f, 1.0f, 0.5f);
	glutSolidSphere(100, 30, 15);

	glRotatef(90, 1.0, 0.0, 0.0);
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	DrawPlanet(a);
	glScalef(0.5, 0.5, 0.5);
	glColor3f(1.0, 0.0, 0.0);
	DrawPlanet(c);
	a->degree += a->speed;
	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	DrawPlanet(b);
	glScalef(0.5, 0.5, 0.5);
	glColor3f(1.0, 0.0, 1.0);
	DrawPlanet(a);
	b->degree += b->speed;
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0.0, 1.0, 0.0);
	glColor3f(1.0, 0.1, 0.5);
	DrawPlanet(c);
	glScalef(0.5, 0.5, 0.5);
	glColor3f(1.0, 0.6, 0.0);
	DrawPlanet(b);
	c->degree += c->speed;
	glPopMatrix();

	glPopMatrix();
}


void block7() {
	glPushMatrix();
	glTranslatef(0, -200, 0);

	glColor3f(0.8, 0.8, 0.8);
	glPushMatrix();
	glScalef(10, 1, 10);
	glutSolidCube(20);
	glTranslatef(0, 10, 0);
	glutSolidCube(15);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 70, 0);
	for (int i = 0; i < 4; i++) {
		glRotatef(90, 0, 1, 0);
		glPushMatrix();
		glTranslatef(80, 0, 80);
		glScalef(1, 10, 1);
		glutSolidCube(15);
		glTranslatef(-60, 0, 0);
		glutSolidCube(15);
		glTranslatef(-60, 0, 0);
		glutSolidCube(15);
		glPopMatrix();
	}
	glScalef(5, 8, 5);
	glutSolidCube(20);
	glPopMatrix();

	glTranslatef(0, 140, 0);
	glScalef(10, 1, 10);
	glutSolidCube(15);
	glTranslatef(0, 10, 0);
	glutSolidCube(20);
	glTranslatef(0, 10, 0);
	glutSolidCube(17);
	glTranslatef(0, 10, 0);
	glutSolidCube(15);

	glColor3f(0.5f, 1.0f, 0.5f);
	glTranslatef(0, 10 + block7_high, 0);
	glScalef(0.1, 1, 0.1);
	glutSolidSphere(70, 30, 30);

	if (block7_high > 200)
		solasystem();

	glPopMatrix();

	block7_high += block7_high_flag = (block7_high >= 300 ? block7_high_flag = -1 : (block7_high <= 0 ? block7_high_flag = 1 : block7_high_flag));
}



void Airplane() {
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glRotatef(-90, 0, 1, 0);
	glutSolidCone(30, 150, 15, 15);
	glPushMatrix();
	glColor3f(1, 0, 0);
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
	glTranslatef(0, 0, -80);
	glTranslatef(0, 0, -50);
	glTranslatef(0, 0, -40);
	glTranslatef(0, 0, -30);
	glPopMatrix();
}

void Draw_Airplane() {
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glRotatef(-90, 0, 1, 0);
	glutSolidCone(30, 150, 15, 15);
	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotatef(block8_Propel, 0, 0, 1);
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
	glutSolidSphere(40 + block8_smoge, 15, 15);
	glTranslatef(0, 0, -80);
	glutSolidSphere(20 - block8_smoge * 0.8, 15, 15);
	glTranslatef(0, 0, -50);
	glutSolidSphere(10 + block8_smoge * 0.7, 15, 15);
	glTranslatef(0, 0, -40);
	glutSolidSphere(5 - block8_smoge * 0.6, 15, 15);
	glTranslatef(0, 0, -30);
	glutSolidSphere(2 + block8_smoge * 0.5, 15, 15);
	glPopMatrix();
}


void block8() {
	glPushMatrix();
	glTranslatef(30, -200, 80);
	glScalef(1, 5, 1);
	glutSolidCube(7);
	glTranslatef(0, 0, -35);
	glScalef(1, 2, 1);
	glutSolidCube(7);
	glTranslatef(0, 0, -35);
	glutSolidCube(7);
	glTranslatef(0, 0, -35);
	glScalef(1, 0.5, 1);
	glutSolidCube(7);
	glPopMatrix();
	glPushMatrix();
	glColor3d(1, 1, 1);
	glFrontFace(GL_CW);
	glTranslatef(0, -200, 0);
	// 곡면 제어점 설정 
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &Block8_ctrlpoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	// 그리드를 이용한 곡면 드로잉 
	glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
	// 선을 이용하여 그리드 연결 
	glEvalMesh2(GL_FILL, 0, 10, 0, 10);
	glPointSize(2.0);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			glVertex3fv(Block8_ctrlpoints[i][j]);
	glEnd();
	glFrontFace(GL_CCW);
	glTranslatef(-80, 0, -80);
	glPushMatrix();
	glScalef(0.3, 0.3, 0.3);
	glRotatef(90, 0, 1, 0);
	Airplane();
	glPopMatrix();
	glTranslatef(80, 0, 0);
	glPushMatrix();
	glScalef(0.3, 0.3, 0.3);
	glRotatef(90, 0, 1, 0);
	Airplane();
	glPopMatrix();
	glTranslatef(80, 0, 0);
	glPushMatrix();
	glScalef(0.3, 0.3, 0.3);
	glRotatef(90, 0, 1, 0);
	Airplane();
	glPopMatrix();


	glPopMatrix();

	glTranslatef(0, -100, -100);
	glRotatef(20, 1, 0, 0);
	glRotated(-1 * block8_AirDG, 0, 1, 0);
	glTranslatef(0, 0, -200);
	glScalef(0.3, 0.3, 0.3);
	Draw_Airplane();

	block8_AirDG = (block8_AirDG >= 360 ? 0 : block8_AirDG + 1);
	block8_Propel = (block8_Propel >= 360 ? 0 : block8_Propel + 10);
	block8_smoge += block8_smogeflag = (block8_smoge > 5 ? -2 : (block8_smoge < -5) ? 2 : block8_smogeflag);
}

void main(int argc, char** argv) // 윈도우 출력하고 출력함수 설정  
{
	glutInit(&argc, argv); // glut 초기화  
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정  
	//glutInitWindowPosition(100, 100); // 윈도우의 위치 지정  
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정  

	glutCreateWindow("Tiles"); // 윈도우 생성 (윈도우 이름)  
	glutDisplayFunc(DrawScene); // 출력 함6수의 지정  
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정  
	glutTimerFunc(100, Timerfunction, 1);
	glutKeyboardFunc(Keyboard);	// 키보드 입력 받기 
	glutMainLoop(); // 이벤트 처리 시작  
}

void DrawScene()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5, 0.5, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);


	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//glEnable(GL_TEXTURE_2D);
	initLight();

	if (texture == false) {
		setTexture(24);
		texture = true;
	}

	


	glLoadIdentity();

	glTranslatef(0, 0, -700);
	//glRotatef(45, 1, 0, 0);
	//
	////조명---------------------------------------
	//float ambientLight[] = { 1.0,1.0,1.0,1.0 };
	//float diffuseLight[] = { 1.0,1.0,1.0,1.0 };
	//float specularLight[] = { 1.0,1.0,1.0,1.0 };
	//float lightPos[] = { 0.0,100.0,0.0,1.0 };

	//glEnable(GL_LIGHTING);

	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	//glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	//glEnable(GL_LIGHT0);
	////-----------------------------------
	//

	//좌표변환------------------
	glTranslatef(moveR, 0, 0);
	glTranslatef(moveL, 0, 0);
	glTranslatef(0, moveU, 0);
	glTranslatef(0, moveD, 0);
	glTranslatef(0, 0, moveFront);
	glTranslatef(0, 0, moveBack);

	//전체회전
	glRotatef(rotateX, 1, 0, 0.0);
	glRotatef(rotateY, 0, 1, 0);
	glRotatef(rotateZ, 0, 0, 1);
	//------------------------------

	BaseGround();

	Road();

	block11();

	block14();
	block10();

	block13();

	block16();
	footballPlay();

	block15();

	block12();

	block9();

	factorySmoke();

	glPushMatrix();
	glTranslatef(-125, 0, -375);
	block2();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(125, 0, -375);
	block3();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(375, 0, -375);
	block4();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-125, 0, -125);
	block6();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(125, 0, -125);
	block7();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(375, 0, -125);
	block8();
	glPopMatrix();

	//human();
	//mountain();
	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	gluPerspective(80.0, w / h, 1.0, 5000.0);
	glTranslatef(0.0, 0.0, -100.0);

	//glOrtho(0, 500.0, -0.0, 500.0, -1.00,1.00);

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'x':
		rotateX += 10;
		break;
	case 'y':
		rotateY += 10;
		break;
	case 'z':
		rotateZ += 10;
		break;
	case 's':
		moveU += 10;
		break;
	case 'w':
		moveD -= 10;
		break;
	case'a':
		moveR += 10;
		break;
	case'd':
		moveL -= 10;
		break;
	case'+':
		moveFront += 10;
		break;
	case'-':
		moveBack -= 10;
		break;

	case 'i':
		rotateX = 0;
		rotateY = 0;
		rotateZ = 0;
		moveR = 0;
		moveL = 0;
		moveU = 0;
		moveD = 0;
		moveFront = 0;
		moveBack = 0;
		break;

	case'q':	//프로그램 종료
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
		glutLeaveMainLoop();
		break;
	case'l':
		craneMove++;
		break;
	}

	glutPostRedisplay();
}

void Timerfunction(int val)
{
	//if (ballX < 420) {
		ballX += 2;
		ballZ += 1;
	//}
	if (ballX == 420)
		ballZ *=- 1;

	craneMove++;
	block13_smoke[0] +=0.5;
	if (block13_smoke[0] == 5.0)
		block13_smoke[0] = 0;

	block13_smoke[1] += 1;
	if (block13_smoke[1] == 9)
		block13_smoke[1] = 0;

	block13_smoke[2] += 1;
	if (block13_smoke[2] == 14)
		block13_smoke[2] = 0;
	
	if (legUp) {
		leg_rotate += 1;
			if (leg_rotate > 5)
				legUp = false;
	}
	else {
		leg_rotate -= 1;
		if (leg_rotate < -5)
			legUp = true;
	}
	water += 1;
	if (water == 10)
		water = 0;

	if (ufoUp) {
		ufoMove += 5;
		if (ufoMove == 50)
			ufoUp = false;
	}
	else {
		ufoMove -= 5;
		if (ufoMove == 0)
			ufoUp = true;
	}

	move -= 5;
	if (move == -100)
		move = 0;

	glutPostRedisplay();
	glutTimerFunc(100, Timerfunction, 1);
}