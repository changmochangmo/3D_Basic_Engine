#include "stdafx.h"
#include "Decoration.h"


CDecoration::CDecoration()
{
}


CDecoration::~CDecoration()
{
}

void CDecoration::Awake(void)
{
	__super::Awake();
	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
}

void CDecoration::Start(void)
{
	__super::Start();
	m_spMesh		= GetComponent<Engine::CMeshC>();
	m_spTexture		= GetComponent<Engine::CTextureC>();
	m_spGraphics	= GetComponent<Engine::CGraphicsC>();
}

void CDecoration::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CDecoration::Update(void)
{
	__super::Update();
}

void CDecoration::LateUpdate(void)
{
	__super::LateUpdate();
}

void CDecoration::OnDestroy(void)
{
	__super::OnDestroy();
}

void CDecoration::OnEnable(void)
{
	__super::OnEnable();
}

void CDecoration::OnDisable(void)
{
	__super::OnDisable();
}
