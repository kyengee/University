#include "Global.h"
#include "Renderer.h"
#include "Object.h"
#include "Physics.h"
#include "Sound.h"

#pragma once
class ScrMgr
{
public:
	ScrMgr();
	~ScrMgr();

	void Update(float elapsedTimeInSec);
	void RenderScene();
	void DoGabageCollection();

	int AddObject(float x, float y, float z,
		float sx, float sy, float sz,
		float vx, float vy, float vz,
		float mass, float fricCoef, int type,
		float r, float g, float b, float a, float hp);
	void DeleteObject(int index);

	void AddMonster(int texture, float speed, float health);

	void KeyDownInput(unsigned char key, int x, int y);
	void KeyUpInput(unsigned char key, int x, int y);
	void SpecialKeyDownInput(int key, int x, int y);
	void SpecialKeyUpInput(int key, int x, int y);

private:
	Physics* m_physics = NULL;
	Sound* m_sound = NULL;
	Renderer* m_Renderer = NULL;
	Object* m_Object[MAX_OBJECT_SIZE] = { NULL, };

	//오브젝트의 인덱스를 기억하기 위한 배열
	int m_charterList[MAX_CHARACTER_SIZE] = { NULL, };

	bool m_KeyW = false;
	bool m_KeyA = false;
	bool m_KeyS = false;
	bool m_KeyD = false;
	bool m_KeySP = false;

	bool m_KeyUp = false;
	bool m_KeyDown = false;
	bool m_KeyLeft = false;
	bool m_KeyRight = false;

	float gametime = 0.f;
	int paze = -1;
};

