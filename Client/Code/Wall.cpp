#include "stdafx.h"
#include "Wall.h"


_uint CWall::m_s_uniqueID = 0;

CWall::CWall()
{
}


CWall::~CWall()
{
	OnDestroy();
}

SP(CWall) CWall::Create(_bool isStatic)
{
	SP(CWall) spInstance(new CWall, Engine::SmartDeleter<CWall>);
	spInstance->SetIsStatic(isStatic);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CWall::MakeClone(void)
{
	SP(CWall) spClone(new CWall, Engine::SmartDeleter<CWall>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spCollision	= spClone->GetComponent<Engine::CCollisionC>();
	return spClone;
}

void CWall::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Map;
	m_dataID	= (_int)EDataID::Scene;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
	m_spCollision	= AddComponent<Engine::CCollisionC>();

	//m_spTransform->SetSize(1, 7, 10);
}

void CWall::Start(void)
{
	__super::Start();
}

void CWall::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CWall::Update(void)
{
	__super::Update();
	
}

void CWall::LateUpdate(void)
{
	__super::LateUpdate();
	
}

void CWall::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CWall::OnEnable(void)
{
	__super::OnEnable();
	
}

void CWall::OnDisable(void)
{
	__super::OnDisable();
	
}

void CWall::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CWall::OnCollisionEnter(Engine::_CollisionInfo ci)
{
}

void CWall::OnCollisionStay(Engine::_CollisionInfo ci)
{
}

void CWall::OnCollisionExit(Engine::_CollisionInfo ci)
{
}
