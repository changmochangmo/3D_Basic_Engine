#include "EngineStdafx.h"
#include "EmptyObject.h"

USING(Engine)
_uint CEmptyObject::m_s_uniqueID = 0;

CEmptyObject::CEmptyObject()
{
}


CEmptyObject::~CEmptyObject()
{
}

SP(CEmptyObject) CEmptyObject::Create(_bool isStatic)
{
	SP(CEmptyObject) spBasicObject(new CEmptyObject, SmartDeleter<CEmptyObject>);
	spBasicObject->SetIsStatic(isStatic);
	spBasicObject->Awake();

	return spBasicObject;
}

SP(Engine::CObject) CEmptyObject::MakeClone(void)
{
	SP(CEmptyObject) spClone(new CEmptyObject, SmartDeleter<CEmptyObject>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<CTransformC>();

	return spClone;
}

void CEmptyObject::Awake(void)
{
	__super::Awake();
}

void CEmptyObject::Start(void)
{
	__super::Start();
}

void CEmptyObject::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CEmptyObject::Update(void)
{
	__super::Update();
}

void CEmptyObject::LateUpdate(void)
{
	__super::LateUpdate();
}

void CEmptyObject::OnDestroy(void)
{
	__super::OnDestroy();
}

void CEmptyObject::OnEnable(void)
{
	__super::OnEnable();
}

void CEmptyObject::OnDisable(void)
{
	__super::OnDisable();
}

void CEmptyObject::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CEmptyObject::OnCollisionEnter(Engine::_CollisionInfo ci)
{
	//if (ci.pOtherCollider->GetOwner()->GetCollisionID() == 0)
	//	ci.pOtherCollider->GetOwner()->GetTransform()->AddPosition(ci.normal * ci.penetLength);
}

void CEmptyObject::OnCollisionStay(Engine::_CollisionInfo ci)
{
	//if (ci.pOtherCollider->GetOwner()->GetCollisionID() == 0)
	//	ci.pOtherCollider->GetOwner()->GetTransform()->AddPosition(ci.normal * ci.penetLength);
}

void CEmptyObject::OnCollisionExit(Engine::_CollisionInfo ci)
{
}
