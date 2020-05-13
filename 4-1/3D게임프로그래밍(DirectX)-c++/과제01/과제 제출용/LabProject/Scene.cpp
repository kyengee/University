#include "stdafx.h"
#include "Scene.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
}

void CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
}

void CScene::BuildObjects()
{
}

void CScene::ReleaseObjects()
{
}

void CScene::CheckObjectByObjectCollisions()
{
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->m_pObjectCollided = NULL;
	for (int i = 0; i < m_nObjects; i++)
	{
		for (int j = (i + 1); j < m_nObjects; j++)
		{
			if (m_ppObjects[i]->m_xmOOBB.Intersects(m_ppObjects[j]->m_xmOOBB))
			{
				m_ppObjects[i]->m_pObjectCollided = m_ppObjects[j];
				m_ppObjects[j]->m_pObjectCollided = m_ppObjects[i];
			}
		}
	}
	for (int i = 0; i < m_nObjects; i++)
	{
		if (m_ppObjects[i]->m_pObjectCollided)
		{
			XMFLOAT3 xmf3MovingDirection = m_ppObjects[i]->m_xmf3MovingDirection;
			float fMovingSpeed = m_ppObjects[i]->m_fMovingSpeed;
			m_ppObjects[i]->m_xmf3MovingDirection = m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection;
			m_ppObjects[i]->m_fMovingSpeed = m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed;
			m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection = xmf3MovingDirection;
			m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed = fMovingSpeed;
			m_ppObjects[i]->m_pObjectCollided->m_pObjectCollided = NULL;
			m_ppObjects[i]->m_pObjectCollided = NULL;
		}
	}
}

void CScene::Animate(float fElapsedTime)
{
	if (m_pPlayer->timeslap > 0.05 && m_ppObjects[0] != NULL && m_nObjects != 1) 
	{
		m_pPlayer->Move(m_ppObjects[0]->GetLook(),false);
		m_pPlayer->timeslap = 0;
		if (m_pPlayer->count == 15) {
			for (int i = 0; i < m_nObjects; i++)
				m_ppObjects[i] = m_ppObjects[i + 1];
			m_nObjects--;
			m_pPlayer->count = 0;
				if (m_ppObjects[0]->type == 1) m_pPlayer->Rotate(-30, 0, 0);
				if (m_ppObjects[0]->type == 2) m_pPlayer->Rotate(0, -30, 0);
				if (m_ppObjects[0]->type == 3) m_pPlayer->Rotate(30, 0, 0);
				if (m_ppObjects[0]->type == 4) m_pPlayer->Rotate(0, 30, 0);
		}
		else m_pPlayer->count++;

	}
	else
		m_pPlayer->timeslap += fElapsedTime;
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->Animate(fElapsedTime);

	CheckObjectByObjectCollisions();
}

void CScene::Render(HDC hDCFrameBuffer, CCamera *pCamera)
{
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->Render(hDCFrameBuffer, pCamera);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CPlayerScene::CPlayerScene()
{
}

CPlayerScene::~CPlayerScene()
{
}

void CPlayerScene::BuildObjects()
{
	CCubeMesh *pObjectCubeMesh = new CCubeMesh(4.0f, 4.0f, 4.0f);
	pObjectCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	m_nObjects = 1;
	m_ppObjects = new CGameObject*[10];

	m_ppObjects[0] = new CGameObject();
	m_ppObjects[0]->SetMesh(pObjectCubeMesh);
	m_ppObjects[0]->SetColor(RGB(255, 0, 0));
	m_ppObjects[0]->SetPosition(0.0f, 0.0f, 0.0f);
	m_ppObjects[0]->SetRotationAxis(XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_ppObjects[0]->SetRotationSpeed(0.0f);
	m_ppObjects[0]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_ppObjects[0]->SetMovingSpeed(0.0f);
	
}

void CPlayerScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	CCubeMesh *pObjectCubeMesh = new CCubeMesh(4.0f, 4.0f, 4.0f);
	pObjectCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'W':
		{
			if (m_nObjects <= 10) m_nObjects++;
			m_ppObjects[m_nObjects -1] = new CGameObject();
			m_ppObjects[m_nObjects - 1]->SetMesh(pObjectCubeMesh);
			m_ppObjects[m_nObjects - 1]->SetColor(RGB(255, 0, 0));
			m_ppObjects[m_nObjects - 1]->SetPosition(m_ppObjects[m_nObjects - 2]->GetPosition());
			m_ppObjects[m_nObjects - 1]->SetRotationAxis(XMFLOAT3(0.0f, 0.0f, 0.0f));
			m_ppObjects[m_nObjects - 1]->SetRotationSpeed(0.0f);
			m_ppObjects[m_nObjects - 1]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 0.0f));
			m_ppObjects[m_nObjects - 1]->SetMovingSpeed(0.0f);
			m_ppObjects[m_nObjects - 1]->m_xmf4x4World = m_ppObjects[m_nObjects - 2]->m_xmf4x4World;
			m_ppObjects[m_nObjects - 1]->MoveForward(16);
			m_ppObjects[m_nObjects - 1]->Rotate(-30.0f, 0.0f, 0.0f);
			m_ppObjects[m_nObjects - 1]->type = 1;
			break;
		}
		case 'A':
		{
			if (m_nObjects <= 10) m_nObjects++;
			m_ppObjects[m_nObjects - 1] = new CGameObject();
			m_ppObjects[m_nObjects - 1]->SetMesh(pObjectCubeMesh);
			m_ppObjects[m_nObjects - 1]->SetColor(RGB(0, 255, 0));
			m_ppObjects[m_nObjects - 1]->SetPosition(m_ppObjects[m_nObjects - 2]->GetPosition());
			m_ppObjects[m_nObjects - 1]->SetRotationAxis(XMFLOAT3(0.0f, 0.0f, 0.0f));
			m_ppObjects[m_nObjects - 1]->SetRotationSpeed(0.0f);
			m_ppObjects[m_nObjects - 1]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 0.0f));
			m_ppObjects[m_nObjects - 1]->SetMovingSpeed(0.0f);
			m_ppObjects[m_nObjects - 1]->m_xmf4x4World = m_ppObjects[m_nObjects - 2]->m_xmf4x4World;
			m_ppObjects[m_nObjects - 1]->MoveForward(16);
			m_ppObjects[m_nObjects - 1]->Rotate(0.0f, -30.0f, 0.0f);
			m_ppObjects[m_nObjects - 1]->type = 2;
			break;
		}
		case 'S':
		{
			if (m_nObjects <= 10) m_nObjects++;
			m_ppObjects[m_nObjects - 1] = new CGameObject();
			m_ppObjects[m_nObjects - 1]->SetMesh(pObjectCubeMesh);
			m_ppObjects[m_nObjects - 1]->SetColor(RGB(0 ,0 ,255));
			m_ppObjects[m_nObjects - 1]->SetPosition(m_ppObjects[m_nObjects - 2]->GetPosition());
			m_ppObjects[m_nObjects - 1]->SetRotationAxis(XMFLOAT3(0.0f, 0.0f, 0.0f));
			m_ppObjects[m_nObjects - 1]->SetRotationSpeed(0.0f);
			m_ppObjects[m_nObjects - 1]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 0.0f));
			m_ppObjects[m_nObjects - 1]->SetMovingSpeed(0.0f);
			m_ppObjects[m_nObjects - 1]->m_xmf4x4World = m_ppObjects[m_nObjects - 2]->m_xmf4x4World;
			m_ppObjects[m_nObjects - 1]->MoveForward(16);
			m_ppObjects[m_nObjects - 1]->Rotate(30.0f, 0.0f, 0.0f);
			m_ppObjects[m_nObjects - 1]->type = 3;
			break;
		}
		case 'D':
		{
			if (m_nObjects <= 10) m_nObjects++;
			m_ppObjects[m_nObjects - 1] = new CGameObject();
			m_ppObjects[m_nObjects - 1]->SetMesh(pObjectCubeMesh);
			m_ppObjects[m_nObjects - 1]->SetColor(RGB(255, 0, 255));
			m_ppObjects[m_nObjects - 1]->SetPosition(m_ppObjects[m_nObjects - 2]->GetPosition());
			m_ppObjects[m_nObjects - 1]->SetRotationAxis(XMFLOAT3(0.0f, 0.0f, 0.0f));
			m_ppObjects[m_nObjects - 1]->SetRotationSpeed(0.0f);
			m_ppObjects[m_nObjects - 1]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 0.0f));
			m_ppObjects[m_nObjects - 1]->SetMovingSpeed(0.0f);
			m_ppObjects[m_nObjects - 1]->m_xmf4x4World = m_ppObjects[m_nObjects - 2]->m_xmf4x4World;
			m_ppObjects[m_nObjects - 1]->MoveForward(16);
			m_ppObjects[m_nObjects - 1]->Rotate(0.0f, 30.0f, 0.0f);
			m_ppObjects[m_nObjects - 1]->type = 4;
			break;
		}
		default:
			break;
		}
		break;
	default:
		break;
	}
}

