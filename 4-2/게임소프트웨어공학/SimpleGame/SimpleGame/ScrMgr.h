#include "Renderer.h"
#pragma once
class ScrMgr
{
public:
	ScrMgr();
	~ScrMgr();

	void RenderScene();

private:
	Renderer* m_Renderer = NULL;
};

