#include "stdafx.h"
#include "Terrain.h"

_uint CTerrain::m_s_uniqueID = 0;

CTerrain::CTerrain()
{
}


CTerrain::~CTerrain()
{
}

SP(CTerrain) CTerrain::Create(_bool isStatic)
{
	SP(CTerrain) spTerrain(new CTerrain, Engine::SmartDeleter<CTerrain>);
	spTerrain->SetIsStarted(isStatic);
	spTerrain->Awake();

	return spTerrain;
}

SP(Engine::CObject) CTerrain::MakeClone(void)
{
	SP(CTerrain) spClone(new CTerrain, Engine::SmartDeleter<CTerrain>);
	__super::InitClone(spClone);

	return spClone;
}

void CTerrain::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Terrain;
	m_dataID	= (_int)EDataID::Terrain;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
	m_spDebug		= AddComponent<Engine::CDebugC>();
}

void CTerrain::Start(void)
{
	__super::Start();
	
	m_spMesh		= GetComponent<Engine::CMeshC>();
	m_spTexture		= GetComponent<Engine::CTextureC>();
	m_spGraphics	= GetComponent<Engine::CGraphicsC>();
	m_spDebug		= GetComponent<Engine::CDebugC>();
}

void CTerrain::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CTerrain::Update(void)
{
	__super::Update();
}

void CTerrain::LateUpdate(void)
{
	__super::LateUpdate();
}

void CTerrain::OnDestroy(void)
{
	__super::OnDestroy();
}

void CTerrain::OnEnable(void)
{
	__super::OnEnable();
}

void CTerrain::OnDisable(void)
{
	__super::OnDisable();
}

void CTerrain::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
