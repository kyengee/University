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