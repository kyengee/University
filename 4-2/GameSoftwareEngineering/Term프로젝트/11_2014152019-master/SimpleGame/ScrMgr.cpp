#include "stdafx.h"
#include "ScrMgr.h"
#include "Dependencies\freeglut.h"

int g_bg[7];
int g_bgm[7];
int g_char[7];
int bullet;
int g_count = 0;

ScrMgr::ScrMgr() {

	// Initialize Renderer
	m_Renderer = new Renderer(500, 500);
	m_physics = new Physics();
	m_sound = new Sound();
	if (!m_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	for (int i = 0; i < MAX_OBJECT_SIZE; i++) {
		m_Object[i] = NULL;
	}
	g_bg[0] = m_Renderer->GenPngTexture("./startbg.png");
	g_bg[1] = m_Renderer->GenPngTexture("./gitaddbg.png");
	g_bg[2] = m_Renderer->GenPngTexture("./gitapplybg.png");
	g_bg[3] = m_Renderer->GenPngTexture("./gitcommitbg.png");
	g_bg[4] = m_Renderer->GenPngTexture("./gitmergebg.png");
	g_bg[5] = m_Renderer->GenPngTexture("./gitpushbg.png");
	g_bg[6] = m_Renderer->GenPngTexture("./endingbg.png");

	g_bgm[0] = m_sound->CreateBGSound("./Sound/start.mp3");
	g_bgm[1] = m_sound->CreateBGSound("./Sound/gitadd.mp3");
	g_bgm[2] = m_sound->CreateBGSound("./Sound/gitapply.mp3");
	g_bgm[3] = m_sound->CreateBGSound("./Sound/gitcommit.mp3");
	g_bgm[4] = m_sound->CreateBGSound("./Sound/gitmerge.mp3");
	g_bgm[5] = m_sound->CreateBGSound("./Sound/ending.mp3");

	g_char[0] = m_Renderer->GenPngTexture("./b.txt.png");
	g_char[1] = m_Renderer->GenPngTexture("./c.txt.png");
	g_char[2] = m_Renderer->GenPngTexture("./d.txt.png");
	g_char[3] = m_Renderer->GenPngTexture("./conflict.png");
	g_char[4] = m_Renderer->GenPngTexture("./modified.png");
	g_char[5] = m_Renderer->GenPngTexture("./untracked.png");

	bullet = m_Renderer->GenPngTexture("./rm.png");

	m_Object[HERO_ID] = new Object();
	m_Object[HERO_ID]->SetPosition(0,0,0);
	m_Object[HERO_ID]->SetVolume(0.5,0.5,0.3);
	m_Object[HERO_ID]->SetVelocity(0,0,0);
	m_Object[HERO_ID]->SetColor(1,1,1,1);
	m_Object[HERO_ID]->SetMass(1);
	m_Object[HERO_ID]->SetFricCoef(0.7);
	m_Object[HERO_ID]->SetType(OBJ_NORMAL);
	m_Object[HERO_ID]->SetHP(1000);
	m_Object[HERO_ID]->SetMaxHP(1000);
	m_Object[HERO_ID]->SetTexID(m_Renderer->GenPngTexture("./player.png"));

	//m_Object[HERO_ID]->SetTexID(g_testTex);

	m_sound->PlayBGSound(g_bgm[0], true, 1.f);
}

ScrMgr::~ScrMgr() {

	if (m_Renderer != NULL) {
		delete m_Renderer;
		m_Renderer = NULL;
	}

	if (m_physics != NULL) {
		delete m_physics;
		m_physics = NULL;
	}
}

void ScrMgr::AddMonster(int texture, float speed, float health) {
	float px, py, pz;
	m_Object[HERO_ID]->GetPosition(&px, &py, &pz);
	float mx, my;
	float pm;
	mx = rand() % 5 - 2.5;
	my = rand() % 5 - 2.5;
	pm = rand() % 2;
	if (pm == 1)
		pm = 1;
	else
		pm = -1;
	if (mx < my)
		mx = 2.4f * pm;
	else
		my = 2.4f * pm;
	int mvx, mvy;
	mvx = (px - mx)/fabs(px - mx)*speed;
	mvy = (py - my)/fabs(py - my)*speed;
	 int index = AddObject(mx, my, 0,
		0.8f, 0.4f, 0.3f,
		mvx, mvy, 0,
		1, 0, OBJ_MONSTER,
		1, 1, 1, 1, health);
	m_Object[index]->SetTexID(texture);
	m_Object[index]->SetMaxHP(health);
}

void ScrMgr::RenderScene() {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	m_Renderer->DrawGround(0, 0, 0, 500, 500, 1, 1, 1, 1, 1, g_bg[paze + 1]);

	for (int i = 0; i < MAX_OBJECT_SIZE; i++) {
		if (m_Object[i] != NULL) {
			float x, y, z = 0;//location
			float sx, sy, sz = 0;//size
			float r, g, b, a = 0;//color
			m_Object[i]->GetPosition(&x, &y, &z);
			m_Object[i]->GetVolume(&sx, &sy, &sz);
			m_Object[i]->GetColor(&r, &g, &b, &a);
			//1 meter == 100 cm == 100pixels
			//코드에서의 1은 미터단위이므로 그릴때는 픽셀단위로 바꿔준다
			x = x * 100.f;
			y = y * 100.f;
			z = z * 100.f;
			sx = sx * 100.f;
			sy = sy * 100.f;
			sz = sz * 100.f;

			// m_Renderer->DrawSolidRect(x, y, z, sx, r, g, b, a);

			int texID = -1;
			m_Object[i]->GetTexID(&texID);
			int type;
			m_Object[i]->GetType(&type);
			if (type != OBJ_BULLET) {
				float maxhp, hp;
				m_Object[i]->GetMaxHP(&maxhp);
				m_Object[i]->GetHP(&hp);
				m_Renderer->DrawSolidRectGauge(
					x, y, z,
					0, sy / 2, 0,
					sx, 5, 0,
					1, 0, 0, 1,
					100*hp/maxhp);
			}
			/*if (i == HERO_ID) {
				static int temp = 0;
				int iX = temp % 5;
				int iY = 0;//(int)((float)temp / (float)5);
				m_Renderer->DrawTextureRectAnim(
					 x,  y,  z,
					 sx,  sy,  sz,
					 r,  g,  b,  a,
					texID,
					 5,
					 1,
					 iX,
					 0);
				temp++;
				if (temp == 5)
					temp = 0;
			}*/
			
			m_Renderer->DrawTextureRect(x, y, z,
				sx, sy, sz,
				r, g, b, a,
				texID);
			
		}
	}
}

void ScrMgr::DoGabageCollection() {
	for (int i = 0; i < MAX_OBJECT_SIZE; i++) {
		if (m_Object[i] == NULL)
			continue;

		int type = -1;
		m_Object[i]->GetType(&type);

		if (type == OBJ_BULLET) {
			float vx, vy, vz;
			m_Object[i]->GetVelocity(&vx, &vy, &vz);
			float vsize = sqrtf(vx * vx + vy * vy + vz * vz);
			if (vsize < 0.0000001f) {
				DeleteObject(i);
				continue;
			}

		}
		float hp;
		m_Object[i]->GetHP(&hp);
		if (hp < 0.0000001f)
			if (i != HERO_ID)
				DeleteObject(i);
	}
}

void ScrMgr::Update(float elapsedTimeInSec) {

	if (paze != -1)
		gametime += elapsedTimeInSec;
	float playerhp;
	m_Object[HERO_ID]->GetHP(&playerhp);
	if (playerhp < 0.00001f) {
		m_sound->StopBGSound(g_bgm[paze + 1]);
		paze = -1;
		m_sound->PlayBGSound(g_bgm[0], true, 1.f);
		m_Object[HERO_ID]->SetHP(1000);
		for (int i = 1; i < MAX_OBJECT_SIZE; i++)
			if(m_Object[i] != NULL)
				DeleteObject(i);
		gametime = 0;
		g_count = 0;
	}
	//git add
	if (gametime > 30 && paze < 1) {
		paze = 1;
		m_sound->StopBGSound(g_bgm[1]);
		m_sound->PlayBGSound(g_bgm[2], true, 1.f);
	}
	//git apply
	if (gametime > 60 && paze < 2) {
		paze = 2;
		m_sound->StopBGSound(g_bgm[2]);
		m_sound->PlayBGSound(g_bgm[3], true, 1.f);
	}
	//git commit
	if (gametime > 90 && paze < 3) {
		paze = 3;
		m_sound->StopBGSound(g_bgm[3]);
		m_sound->PlayBGSound(g_bgm[4], true, 1.f);
	}
	//git merge
	if (gametime > 150 && paze < 4) {
		paze = 4;
		m_sound->StopBGSound(g_bgm[4]);
	}
	//git push
	if (gametime > 160 && paze < 5) {
		for (int i = 1; i < MAX_OBJECT_SIZE; i++)
			if(m_Object[i] != NULL)
				DeleteObject(i);
		paze = 5;
		m_sound->PlayBGSound(g_bgm[5], true, 1.f);
	}
	//git end
	if (gametime > 190 && paze < 6) {
	}

	if (g_count < (int)(gametime / 10)) {
		g_count++;
		switch (paze)
		{
		case 0:
			AddMonster(g_char[0], 1, 100);
			AddMonster(g_char[1], 1, 100);
			AddMonster(g_char[2], 1, 100);
			break;
		case 1:
			AddMonster(g_char[3], 1, 150);
			AddMonster(g_char[3], 1, 150);
			AddMonster(g_char[3], 1, 150);
			AddMonster(g_char[3], 1, 150);
			break;
		case 2:
			AddMonster(g_char[4], 1, 170);
			AddMonster(g_char[5], 1, 170);
			AddMonster(g_char[4], 1, 170);
			AddMonster(g_char[5], 1, 170);
			break;
		case 3:
			AddMonster(g_char[4], 1, 170);
			AddMonster(g_char[5], 1, 170);
			AddMonster(g_char[3], 1, 150);
			AddMonster(g_char[3], 1, 150);
			AddMonster(g_char[0], 1, 100);
			AddMonster(g_char[1], 1, 100);
			AddMonster(g_char[2], 1, 100);
			break;

		default:
			break;
		}
	}
	
	//charactor control : hero
	//std::cout << "w: " << m_KeyW << ", a: " << m_KeyA << ", s: " << m_KeyS << ", d: " << m_KeyD << "\n";
	//std::cout << "Left: " << m_KeyLeft << ", Right: " << m_KeyRight << ", Up: " << m_KeyUp << ", Down: " << m_KeyDown << "\n";
	float Fx, Fy, Fz;
	Fx = Fy = Fz = 0.f;
	float Famount = 20.f;
	if (m_KeyW) {
		Fy += 1.f;
	}
	if (m_KeyA) {
		Fx -= 1.f;
	}
	if (m_KeyS) {
		Fy -= 1.f;
	}
	if (m_KeyD) {
		Fx += 1.f;
	}
	if (m_KeySP) {
		Fz += 1.f;
	}
	//add control force to hero
	float fsize = sqrtf(Fx * Fx + Fy * Fy);
	if (fsize > 0.0000001) {
		Fx /= fsize;
		Fy /= fsize;
		Fx *= Famount;
		Fy *= Famount;

	}
	m_Object[HERO_ID]->AddForce(Fx, Fy, 0.f, elapsedTimeInSec);

	if (Fz > 0.000000001) {
		float x, y, z;
		m_Object[HERO_ID]->GetPosition(&x, &y, &z);
		if (z < 0.000001) {
			Fz *= Famount*20.f;
			m_Object[HERO_ID]->AddForce(0.f, 0.f, Fz, elapsedTimeInSec);
		}
	}
	//fire bullets
	if(m_Object[HERO_ID]->CanShootBullet())
	if (m_KeyUp || m_KeyDown || m_KeyLeft || m_KeyRight) {
		float bulletVel = 7.f;
		float BulletVelX, BulletVelY, BulletVelZ;
		BulletVelX = BulletVelY = BulletVelZ = 0.f;
		if (m_KeyUp) BulletVelY += 1.f;
		if (m_KeyDown) BulletVelY -= 1.f;
		if (m_KeyLeft) BulletVelX -= 1.f;
		if (m_KeyRight) BulletVelX += 1.f;

		float BulletVelSize = sqrtf(BulletVelX * BulletVelX + BulletVelY * BulletVelY + BulletVelZ * BulletVelZ);
		if (BulletVelSize > 0.0001f) {
			//create bullet
			BulletVelX /= BulletVelSize;
			BulletVelY /= BulletVelSize;
			BulletVelZ /= BulletVelSize;
			BulletVelX *= bulletVel;
			BulletVelY *= bulletVel;
			BulletVelZ *= bulletVel;

			float hx, hy, hz;
			float hvx, hvy, hvz;
			m_Object[HERO_ID]->GetPosition(&hx, &hy, &hz);
			m_Object[HERO_ID]->GetVelocity(&hvx, &hvy, &hvz);

			BulletVelX += hvx;
			BulletVelY += hvy;
			BulletVelZ += hvz;
			int index = 0;
			index = AddObject(hx, hy, hz,
				0.3f, 0.15f, 0.05f,
				BulletVelX, BulletVelY, BulletVelZ,
				1.f, 0.7f, OBJ_BULLET,
				1.f, 0.f, 0.f, 1.f, 20.f);
			m_Object[index]->SetParent(m_Object[HERO_ID]);
			m_Object[index]->SetTexID(bullet);
		}

		m_Object[HERO_ID]->ResetBulletCooltime();
	}

	//overlapTest
	for (int src = 0; src < MAX_OBJECT_SIZE; src++) {
		for (int dst = src+1; dst < MAX_OBJECT_SIZE; dst++) {
			if (m_Object[src] != NULL && m_Object[dst] != NULL && m_Object[src] != m_Object[dst]) {
				if (m_physics->IsOverlap(m_Object[src], m_Object[dst]))
				{
					std::cout << "collision : " << src << ", " << dst << "\n";
					if (!m_Object[src]->IsAncester(m_Object[dst]) && !m_Object[dst]->IsAncester(m_Object[src])) {
						m_physics->processCollision(m_Object[src], m_Object[dst]);

						int srctype,dsttype;
						m_Object[src]->GetType(&srctype);
						m_Object[dst]->GetType(&dsttype);

						if (!(OBJ_MONSTER == srctype && OBJ_MONSTER == dsttype)) {
							float srcHP, dstHP;
							m_Object[src]->GetHP(&srcHP);
							m_Object[dst]->GetHP(&dstHP);
							m_Object[src]->damage(dstHP);
							m_Object[dst]->damage(srcHP);
						}
					}
				}

			}
		}
	}

	for (int i = 0; i < MAX_OBJECT_SIZE; i++) {
		if (m_Object[i] != NULL) {
			m_Object[i]->Update(elapsedTimeInSec);
		}
	}

}

void ScrMgr::KeyDownInput(unsigned char key, int x, int y)
{
	if (key == 'w' || key == 'W')
	{
		m_KeyW = true;
	}
	if (key == 'a' || key == 'A')
	{
		m_KeyA = true;
	}
	if (key == 's' || key == 'S')
	{
		m_KeyS = true;
	}
	if (key == 'd' || key == 'D')
	{
		m_KeyD = true;
	}
	if (key == ' ')
	{
		if (paze == -1) {
			paze = 0;
			m_sound->StopBGSound(g_bgm[0]);
			m_sound->PlayBGSound(g_bgm[1], true, 1.f);
		}
		m_KeySP = true;
	}
}

void ScrMgr::KeyUpInput(unsigned char key, int x, int y)
{
	if (key == 'w' || key == 'W')
	{
		m_KeyW = false;
	}
	if (key == 'a' || key == 'A')
	{
		m_KeyA = false;
	}
	if (key == 's' || key == 'S')
	{
		m_KeyS = false;
	}
	if (key == 'd' || key == 'D')
	{
		m_KeyD = false;
	}
	if (key == ' ')
	{
		m_KeySP = false;
	}
}

void ScrMgr::SpecialKeyDownInput(int key, int x, int y)
{
	if (GLUT_KEY_DOWN == key)
	{
		m_KeyDown = true;
	}
	if (GLUT_KEY_UP == key)
	{
		m_KeyUp = true;
	}
	if (GLUT_KEY_RIGHT == key)
	{
		m_KeyRight = true;
	}
	if (GLUT_KEY_LEFT == key)
	{
		m_KeyLeft = true;
	}
}

void ScrMgr::SpecialKeyUpInput(int key, int x, int y)
{
	if (GLUT_KEY_DOWN == key)
	{
		m_KeyDown = false;
	}
	if (GLUT_KEY_UP == key)
	{
		m_KeyUp = false;
	}
	if (GLUT_KEY_RIGHT == key)
	{
		m_KeyRight = false;
	}
	if (GLUT_KEY_LEFT == key)
	{
		m_KeyLeft = false;
	}
}

int ScrMgr::AddObject(float x, float y, float z,
	float sx, float sy, float sz,
	float vx, float vy, float vz,
	float mass, float fricCoef, int type,
	float r, float g, float b, float a, float hp) {

	int index = -1;

	for (int i = 0; i < MAX_OBJECT_SIZE; i++) {
		if (m_Object[i] == NULL) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		std::cout << "no more obj slot /n";
		return -1;
	}

	m_Object[index] = new Object();
	m_Object[index]->SetPosition(x, y, z);
	m_Object[index]->SetVolume(sx, sy, sz);
	m_Object[index]->SetVelocity(vx, vy, vz);
	m_Object[index]->SetMass(mass);
	m_Object[index]->SetFricCoef(fricCoef);
	m_Object[index]->SetColor(r, g, b, a);
	m_Object[index]->SetType(type);
	m_Object[index]->SetHP(hp);

	return index;
}

void ScrMgr::DeleteObject(int index) {
	if (index < 0) {
		std::cout << "input index is negative : " << index << "\n";
		return;
	}
	if (index >= MAX_OBJECT_SIZE) {
		std::cout << "input index is upper than MAX_OBJECT_SIZE" << index << "\n";
		return;
	}
	if (m_Object[index] == NULL) {
		//NULL을 없애려고 하면 거기에는 실제로 의미있는 정보가 있기 때문에 프로그램을 죽여버린다.
		std::cout << "m_Object[" << index << "] is null.\n";
		return;
	}

	delete m_Object[index];
	m_Object[index] = NULL;
}