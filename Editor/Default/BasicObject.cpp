#include "stdafx.h"
#include "BasicObject.h"


_uint CBasicObject::m_s_uniqueID = 0;

CBasicObject::CBasicObject()
{
}


CBasicObject::~CBasicObject()
{
}

SP(CBasicObject) CBasicObject::Create(_bool isStatic)
{
	SP(CBasicObject) spBasicObject(new CBasicObject, Engine::SmartDeleter<CBasicObject>);
	spBasicObject->SetIsStatic(isStatic);
	spBasicObject->Awake();

	return spBasicObject;
}

SP(Engine::CObject) CBasicObject::MakeClone(void)
{
	SP(CBasicObject) spClone(new CBasicObject, Engine::SmartDeleter<CBasicObject>);
	__super::InitClone(spClone);


	return spClone;
}

void CBasicObject::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::BasicObject;
	m_dataID	= (_int)EDataID::BasicObject;
}

void CBasicObject::Start(void)
{
	__super::Start();
}

void CBasicObject::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CBasicObject::Update(void)
{
	__super::Update();
}

void CBasicObject::LateUpdate(void)
{
	__super::LateUpdate();
}

void CBasicObject::OnDestroy(void)
{
	__super::OnDestroy();
}

void CBasicObject::OnEnable(void)
{
	__super::OnEnable();
}

void CBasicObject::OnDisable(void)
{
	__super::OnDisable();
}

void CBasicObject::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
