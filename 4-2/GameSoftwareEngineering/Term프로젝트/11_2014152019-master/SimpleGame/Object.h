#pragma once
class Object
{
public:
	Object();
	~Object();

	void SetMass(float m);
	void GetMass(float* m);
	void SetPosition(float x, float y, float z);
	void GetPosition(float *x, float *y, float *z);
	void SetVelocity(float vx, float vy, float vz);
	void GetVelocity(float *vx, float *vy, float *vz);
	void SetVolume(float vx, float vy, float vz);
	void GetVolume(float *vx, float *vy, float *vz);
	void SetAcceleration(float ax, float ay, float az);
	void GetAcceleration(float* ax, float* ay, float* az);
	void SetColor(float r, float g, float b, float a);
	void GetColor(float *r, float *g, float *b, float *a);
	void Update(float elapsedTimeInSec);
	void SetFricCoef(float Friction);
	void GetFricCoef(float *Friction);

	void AddForce(float Fx, float Fy, float Fz, float elapsedTimeInSec);
	void initPhysics();

	void SetType(int type);
	void GetType(int* type);

	void SetTexID(int id);
	void GetTexID(int* id);

	bool CanShootBullet();
	void ResetBulletCooltime();
	void SetParent(Object* parent);
	Object* GetParent();
	bool IsAncester(Object* obj);
	void GetHP(float* hp);
	void SetHP(float hp);
	void GetMaxHP(float* hp);
	void SetMaxHP(float hp);
	void damage(float damage);


private:
	float m_mass = 0;
	float m_posX = 0, m_posY = 0, m_posZ = 0;
	float m_velX = 0, m_velY = 0, m_velZ = 0;
	float m_volX = 0, m_volY = 0, m_volZ = 0;
	float m_accX = 0, m_accY = 0, m_accZ = 0;
	float m_r = 0, m_g = 0, m_b = 0, m_a = 0;
	float m_FricCoef = 0; // friction
	float m_healthPoint = 0;
	float m_maxhealthPoint = 0;
	

	int m_type = 0;

	float m_remainingCooltime = 0.f;
	float m_CurruntCooltime = 0.1f;

	int m_texID;													// texID

	Object* m_parent;

};

