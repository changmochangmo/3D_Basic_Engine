#include "EngineStdafx.h"
#include "DebugCollider.h"

#include "AabbCollider.h"
#include "SphereCollider.h"

USING(Engine)
_uint CDebugCollider::m_s_uniqueID = 0;

CDebugCollider::CDebugCollider()
{
}


CDebugCollider::~CDebugCollider()
{
}

SP(CDebugCollider) CDebugCollider::Create(_bool isStatic)
{
	SP(CDebugCollider) spInstance(new CDebugCollider, Engine::SmartDeleter<CDebugCollider>);
	spInstance->SetIsStatic(true);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CDebugCollider::MakeClone(void)
{
	SP(CDebugCollider) spClone(new CDebugCollider, Engine::SmartDeleter<CDebugCollider>);
	CObject::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	return spClone;
}

void CDebugCollider::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)ELayerID::DebugCollision;
}

void CDebugCollider::Start(void)
{
	__super::Start();


	switch (m_pCollider->GetColliderType())
	{
	case (_int)EColliderType::AABB:
		m_spMesh->AddMeshData(L"Cube");
		m_spTransform->SetSize(dynamic_cast<CAabbCollider*>(m_pCollider)->GetSize());
		break;

	case (_int)EColliderType::Sphere:
	{
		m_spMesh->AddMeshData(L"Sphere");

		_float radius = dynamic_cast<CSphereCollider*>(m_pCollider)->GetRadius();
		m_spTransform->SetSize(_float3(radius, radius, radius));
		break;
	}

	default:
		break;
	}

	m_offset = m_pCollider->GetOffset();
}

void CDebugCollider::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CDebugCollider::Update(void)
{
	__super::Update();
}

void CDebugCollider::LateUpdate(void)
{
	__super::LateUpdate();
}

void CDebugCollider::OnDestroy(void)
{
	__super::OnDestroy();
}

void CDebugCollider::OnEnable(void)
{
	__super::OnEnable();
}

void CDebugCollider::OnDisable(void)
{
	__super::OnDisable();
}

void CDebugCollider::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
