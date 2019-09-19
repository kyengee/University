#include "stdafx.h"
#include "ScrMgr.h"

ScrMgr::ScrMgr() {

	// Initialize Renderer
	m_Renderer = new Renderer(500, 500);
	if (!m_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
}

ScrMgr::~ScrMgr() {

	if (m_Renderer != NULL) {
		delete m_Renderer;
		m_Renderer = NULL;
	}
}

void ScrMgr::RenderScene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	m_Renderer->DrawSolidRect(0, 0, 0, 4, 1, 0, 1, 1);
}