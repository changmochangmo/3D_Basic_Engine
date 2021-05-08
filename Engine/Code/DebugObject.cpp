#include "EngineStdafx.h"
#include "DebugObject.h"


USING(Engine)
CDebugObject::CDebugObject()
{
}


CDebugObject::~CDebugObject()
{
}

void CDebugObject::Awake(void)
{
	__super::Awake();
	m_dataID = (_int)EDataID::DebugObject;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
}

void CDebugObject::Start(void)
{
	__super::Start();

	m_spMesh		= GetComponent<Engine::CMeshC>();
	m_spGraphics	= GetComponent<Engine::CGraphicsC>();
}

void CDebugObject::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CDebugObject::Update(void)
{
	__super::Update();
}

void CDebugObject::LateUpdate(void)
{
	__super::LateUpdate();
}

void CDebugObject::OnDestroy(void)
{
	__super::OnDestroy();
}

void CDebugObject::OnEnable(void)
{
	__super::OnEnable();
}

void CDebugObject::OnDisable(void)
{
	__super::OnDisable();
}