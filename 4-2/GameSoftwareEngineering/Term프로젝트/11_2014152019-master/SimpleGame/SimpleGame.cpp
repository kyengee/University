/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "ScrMgr.h"

ScrMgr* g_ScrMgr = NULL;
int g_prevTime = 0;

void RenderScene(int temp)
{
	int currTime = glutGet(GLUT_ELAPSED_TIME);
	int elapsedTime = currTime - g_prevTime;
	float elapsedTimeInSec = (float)elapsedTime / 1000.0f;
	g_prevTime = currTime;

	//지난 시간을 milesecond단위로 출력
	//std::cout << "elapsedTime : " << elapsedTime << "\n";
	g_ScrMgr->Update(elapsedTimeInSec);
	g_ScrMgr->RenderScene();
	g_ScrMgr->DoGabageCollection();
	//glut에 관련된 함수는 이 파일에서만 사용하도록 함
	glutSwapBuffers();

	glutTimerFunc(10, RenderScene, 0);
}

void Display(void){}

void Idle(void)
{
}

void MouseInput(int button, int state, int x, int y)
{
}

void KeyDownInput(unsigned char key, int x, int y)
{
	g_ScrMgr->KeyDownInput(key, x, y);
}

void KeyUpInput(unsigned char key, int x, int y)
{
	g_ScrMgr->KeyUpInput(key, x, y);
}

void SpecialKeyDownInput(int key, int x, int y)
{
	g_ScrMgr->SpecialKeyDownInput(key, x, y);
}

void SpecialKeyUpInput(int key, int x, int y)
{
	g_ScrMgr->SpecialKeyUpInput(key, x, y);
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}
	//클래스에 glut관련 함수가 있기 때문에 glew초기화 이후 할당해야함
	g_ScrMgr = new ScrMgr();

	glutDisplayFunc(Display);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyDownInput);
	glutKeyboardUpFunc(KeyUpInput);
	glutSpecialFunc(SpecialKeyDownInput);
	glutSpecialUpFunc(SpecialKeyUpInput);
	glutMouseFunc(MouseInput);

	g_prevTime = glutGet(GLUT_ELAPSED_TIME);
	glutTimerFunc(10, RenderScene, 0);

	glutMainLoop();

	delete g_ScrMgr;

    return 0;
}

