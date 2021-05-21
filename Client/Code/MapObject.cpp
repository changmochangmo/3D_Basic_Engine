#include "stdafx.h"
#include "MapObject.h"

_uint CMapObject::m_s_uniqueID = 0;

CMapObject::CMapObject(void)
{
}

CMapObject::~CMapObject(void)
{
}

SP(CMapObject) CMapObject::Create(void)
{
	SP(CMapObject) spInstance(new CMapObject, Engine::SmartDeleter<CMapObject>);
	spInstance->SetIsStatic(false);
	spInstance->SetAddExtra(true);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CMapObject::MakeClone(void)
{
	SP(CMapObject) spClone(new CMapObject, Engine::SmartDeleter<CMapObject>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();

	spClone->m_addExtra		= m_addExtra;
	return spClone;
}


void CMapObject::Awake(void)
{
	__super::Awake();
	m_layerID	= (_int)ELayerID::Map;
	m_dataID	= (_int)EDataID::Scene;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	m_spTransform->SetSize(_float3(0.01f, 0.01f, 0.01f));
}

void CMapObject::Start(void)
{
	__super::Start();
}

void CMapObject::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMapObject::Update(void)
{
	__super::Update();
}

void CMapObject::LateUpdate(void)
{
	__super::LateUpdate();
	
}

void CMapObject::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CMapObject::OnEnable(void)
{
	__super::OnEnable();
	
}

void CMapObject::OnDisable(void)
{
	__super::OnDisable();
	
}

void CMapObject::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CMapObject::OnCollisionEnter(Engine::_CollisionInfo ci)
{
	if (ci.pOtherCollider->GetOwner()->GetCollisionID() == (_int)EColliderID::PlayerRay)
		ci.pOtherCollider->GetOwner()->GetTransform()->AddPosition(ci.normal * ci.penetLength);
}

void CMapObject::OnCollisionStay(Engine::_CollisionInfo ci)
{
}

void CMapObject::OnCollisionExit(Engine::_CollisionInfo ci)
{
}
