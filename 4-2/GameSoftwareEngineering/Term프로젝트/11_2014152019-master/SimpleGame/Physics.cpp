#include "stdafx.h"
#include "Physics.h"
#include "math.h"


bool Physics::IsOverlap(Object* A, Object* B, int method){

	switch (method)
	{
	case 0:
		return BBOverlapTest(A, B);
		break;

	default:
		break;
	}

	return false;
}

bool Physics::BBOverlapTest(Object* A, Object* B) {
	//A Object
	float aX, aY, aZ;
	float aSX, aSY, aSZ;
	float aMinX, aMinY, aMinZ;
	float aMaxX, aMaxY, aMaxZ;
	A->GetPosition(&aX, &aY, &aZ);
	A->GetVolume(&aSX, &aSY, &aSZ);
	aMinX = aX - aSX / 2.f; aMaxX = aX + aSX / 2.f;
	aMinY = aY - aSY / 2.f; aMaxY = aY + aSY / 2.f;
	aMinZ = aZ - aSZ / 2.f; aMaxZ = aZ + aSZ / 2.f;

	//B Object
	float bX, bY, bZ;
	float bSX, bSY, bSZ;
	float bMinX, bMinY, bMinZ;
	float bMaxX, bMaxY, bMaxZ;
	B->GetPosition(&bX, &bY, &bZ);
	B->GetVolume(&bSX, &bSY, &bSZ);
	bMinX = bX - bSX / 2.f; bMaxX = bX + bSX / 2.f;
	bMinY = bY - bSY / 2.f; bMaxY = bY + bSY / 2.f;
	bMinZ = bZ - bSZ / 2.f; bMaxZ = bZ + bSZ / 2.f;

	if (aMinX > bMaxX)
		return false;
	if (aMaxX < bMinX)
		return false;

	if (aMinY > bMaxY)
		return false;
	if (aMaxY < bMinY)
		return false;

	if (aMinZ > bMaxZ)
		return false;
	if (aMaxZ < bMinZ)
		return false;

	return true;

}

void Physics::processCollision(Object* A, Object* B) {
	//A Object
	float aMass, aVX, aVY, aVZ;
	A->GetMass(&aMass);
	A->GetVelocity(&aVX, &aVY, &aVZ);
	float afVX, afVY, afVZ;

	//B Object
	float bMass, bVX, bVY, bVZ;
	B->GetMass(&bMass);
	B->GetVelocity(&bVX, &bVY, &bVZ);
	float bfVX, bfVY, bfVZ;

	afVX = ((aMass - bMass) / (aMass + bMass)) * aVX
		+ bMass * 2.f / (aMass + bMass) * bVX;
	afVY = ((aMass - bMass) / (aMass + bMass)) * aVY
		+ bMass * 2.f / (aMass + bMass) * bVY;
	afVZ = ((aMass - bMass) / (aMass + bMass)) * aVZ
		+ bMass * 2.f / (aMass + bMass) * bVZ;

	bfVX = aMass * 2.f / (aMass + bMass) * aVX
		+ ((bMass - aMass) / (aMass + bMass)) * bVX;
	bfVY = aMass * 2.f / (aMass + bMass) * aVY
		+ ((bMass - aMass) / (aMass + bMass)) * bVY;
	bfVZ = aMass * 2.f / (aMass + bMass) * aVZ
		+ ((bMass - aMass) / (aMass + bMass)) * bVZ;

	A->SetVelocity(afVX, afVY, afVZ);
	B->SetVelocity(bfVX, bfVY, bfVZ);

}

