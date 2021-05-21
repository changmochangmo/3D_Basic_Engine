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
	case (_int)EColliderType::Ray:
	{
		CRayCollider* pRayCollider = dynamic_cast<CRayCollider*>(m_pCollider);
		m_spMesh->AddMeshData(L"Cube");

		m_spTransform->SetSize(0.01f, 0.01f, pRayCollider->GetLength());
		m_spTransform->SetForward(pRayCollider->GetDirection());
		break;
	}

	case (_int)EColliderType::Sphere:
	{
		m_spMesh->AddMeshData(L"Sphere");

		_float radius = dynamic_cast<CSphereCollider*>(m_pCollider)->GetRadius();
		m_spTransform->SetSize(_float3(radius * 2.f, radius * 2.f, radius * 2.f));
		break;
	}

	case (_int)EColliderType::AABB:
	{
		m_spMesh->AddMeshData(L"Cube");
		m_spTransform->SetSize(dynamic_cast<CAabbCollider*>(m_pCollider)->GetSize());
		break;
	}

	case (_int)EColliderType::OBB:
	{
		m_spMesh->AddMeshData(L"Cube");
		m_spTransform->SetSize(dynamic_cast<CObbCollider*>(m_pCollider)->GetSize());
		m_spTransform->SetForward(dynamic_cast<CObbCollider*>(m_pCollider)->GetForward());
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
	m_spTransform->SetPosition(m_pOwner->GetTransform()->GetPosition() + m_pCollider->GetOffset());
	m_spTransform->SetRotation(m_pCollider->GetOwner()->GetTransform()->GetRotation());
	switch (m_pCollider->GetColliderType())
	{
	case (_int)EColliderType::Ray:
	{
		CRayCollider* pRay = static_cast<CRayCollider*>(m_pCollider);
		m_spTransform->AddPosition(pRay->GetDirection() * pRay->GetLength() / 2.f);
		m_spTransform->SetForward(pRay->GetDirection());
		m_spTransform->SetSize(0.01f, 0.01f, pRay->GetLength());
		break;
	}

	case (_int)EColliderType::OBB:
	{
		m_spTransform->SetForward(static_cast<CObbCollider*>(m_pCollider)->GetForward());
		break;
	}

	default:
		break;
	}

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
