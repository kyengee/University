#include "stdafx.h"
#include "Object.h"
#include "Global.h"
#include <math.h>

Object::Object() {}

Object::~Object() {}

void Object::SetPosition(float x, float y, float z) {
	m_posX = x;
	m_posY = y;
	m_posZ = z;
}
void Object::GetPosition(float* x, float* y, float* z) {
	*x = m_posX;
	*y = m_posY;
	*z = m_posZ;
}
void Object::SetMass(float m) {
	m_mass = m;
}
void Object::GetMass(float* m) {
	*m = m_mass;
}
void Object::SetVelocity(float vx, float vy, float vz) {
	m_velX = vx;
	m_velY = vy;
	m_velZ = vz;
}
void Object::GetVelocity(float* vx, float* vy, float* vz) {
	*vx = m_velX;
	*vy = m_velY;
	*vz = m_velZ;
}
void Object::SetVolume(float vx, float vy, float vz) {
	m_volX = vx;
	m_volY = vy;
	m_volZ = vz;
}
void Object::GetVolume(float* vx, float* vy, float* vz) {
	*vx = m_volX;
	*vy = m_volY;
	*vz = m_volZ;
}
void Object::SetAcceleration(float ax, float ay, float az) {
	m_accX = ax;
	m_accY = ay;
	m_accZ = az;
}
void Object::GetAcceleration(float* ax, float* ay, float* az) {
	*ax = m_accX;
	*ay = m_accY;
	*az = m_accZ;
}

void Object::SetColor(float r, float g, float b, float a) {
	m_r = r;
	m_g = g;
	m_b = b;
	m_a = a;
}

void Object::GetColor(float* r, float* g, float* b, float* a) {
	*r = m_r;
	*g = m_g;
	*b = m_b;
	*a = m_a;
}

void Object::Update(float elapsedTimeInSec) {

	//reduce remaining cooltime
	m_remainingCooltime -= elapsedTimeInSec;
	/////////Apply Friction///////////////////
	float normalForce = m_mass * GRAVITY; // scalar
	float fricForce = m_FricCoef * normalForce;//scalar
	float velsize = sqrtf(m_velX * m_velX + m_velY * m_velY + m_velZ*m_velZ);
	if (velsize > 0.f) {
		float FdirX = -1.f * m_velX / velsize;
		float FdirY = -1.f * m_velY / velsize;
		FdirX = FdirX * fricForce;
		FdirY = FdirY * fricForce;
		float fAccX = FdirX / m_mass;
		float fAccY = FdirY / m_mass;
		float NEWm_velX = m_velX + fAccX * elapsedTimeInSec;
		float NEWm_velY = m_velY + fAccY * elapsedTimeInSec;
		if (m_velX * NEWm_velX < 0.f) {
			m_velX = 0.f;
		}
		else {
			m_velX = NEWm_velX;
		}
		if (m_velY * NEWm_velY < 0.f) {
			m_velY = 0.f;
		}
		else {
			m_velY = NEWm_velY;
		}
		m_velZ = m_velZ - GRAVITY * elapsedTimeInSec;
	}
	//////////////////////////////////////////

	m_posX = m_posX + m_velX * elapsedTimeInSec;
	m_posY = m_posY + m_velY * elapsedTimeInSec;
	m_posZ = m_posZ + m_velZ * elapsedTimeInSec;
	if (m_posX > 2.5 || m_posX < -2.5) m_velX = m_velX * -1;
	if (m_posY > 2.5 || m_posY < -2.5) m_velY = m_velY * -1;

	if (m_posZ < 0.0000000001) {
		m_posZ = 0.f;
		m_velZ = 0.f;
	}
}

bool Object::CanShootBullet() {
	if (m_remainingCooltime < 0.0000001) {
		return true;
	}
	return false;
}
void Object::ResetBulletCooltime() {
	m_remainingCooltime = m_CurruntCooltime;
}

void Object::AddForce(float Fx, float Fy, float Fz, float elapsedTimeInSec) {
	float accX, accY, accZ;
	accX = accY = accZ = 0.f;

	accX = Fx / m_mass;
	accY = Fy / m_mass;
	accZ = Fz / m_mass;

	m_velX = m_velX + accX * elapsedTimeInSec;
	m_velY = m_velY + accY * elapsedTimeInSec;
	m_velZ = m_velZ + accZ * elapsedTimeInSec;

}

void Object::SetFricCoef(float Friction) {
	m_FricCoef = Friction;
}
void Object::GetFricCoef(float* Friction) {
	*Friction = m_FricCoef;
}

void Object::initPhysics() {
	m_mass = 0;
	m_posX = 0, m_posY = 0, m_posZ = 0;
	m_velX = 0, m_velY = 0, m_velZ = 0;
	m_volX = 0, m_volY = 0, m_volZ = 0;
	m_accX = 0, m_accY = 0, m_accZ = 0;
	m_r = 0, m_g = 0, m_b = 0, m_a = 0;
	m_FricCoef = 0; // friction
}

void Object::SetType(int type) {
	m_type = type;
}
void Object::GetType(int* type) {
	*type = m_type;
}

void Object::SetTexID(int id)
{
	m_texID = id;
}

void Object::GetTexID(int* id)
{
	*id = m_texID;
}

void Object::SetParent(Object* parent) {
	m_parent = parent;
}
Object* Object::GetParent() {
	return m_parent;
}
bool Object::IsAncester(Object* obj) {
	if (obj != NULL) {
		if (obj == m_parent) {
			return true;
		}
		return false;
	}
}

void Object::GetHP(float* hp) {
	*hp = m_healthPoint;
}
void Object::SetHP(float hp) {
	m_healthPoint = hp;
}
void Object::GetMaxHP(float* hp) {
	*hp = m_maxhealthPoint;
}
void Object::SetMaxHP(float hp) {
	m_maxhealthPoint = hp;
}
void Object::damage(float damage) {
	m_healthPoint -= damage;
}