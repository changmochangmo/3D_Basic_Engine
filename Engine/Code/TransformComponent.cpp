#include "EngineStdafx.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "DataStore.h"
#include "FRC.h"

USING(Engine)
CTransformComponent::CTransformComponent(void)  
{
}

CTransformComponent::~CTransformComponent(void)
{
}

SHARED(CComponent) CTransformComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CTransformComponent) spClone(new CTransformComponent);
	__super::InitClone(spClone, pObject);

	spClone->SetPosition(m_position);
	spClone->SetRotation(m_rotation);
	spClone->SetScale(m_scale);
	spClone->SetWorldMatrix(m_worldMat);

	return spClone;
}

void CTransformComponent::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;
}

void CTransformComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
	_bool isStatic = m_pOwner->GetIsStatic();
	_int ownerDataID = m_pOwner->GetDataID();
	std::wstring objectKey = m_pOwner->GetObjectKey();

	//GET_VALUE(isStatic, layerKey, objectKey, L"m_position", m_position);
}

_uint CTransformComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CTransformComponent::Update(SHARED(CComponent) spThis)
{
	UpdateWorldmMatrix();

	return NO_EVENT;
}

_uint CTransformComponent::LateUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

void CTransformComponent::OnDestroy(void)
{
}

void CTransformComponent::OnEnable(void)
{
	__super::OnEnable();
}

void CTransformComponent::OnDisable(void)
{
}




void CTransformComponent::UpdateWorldmMatrix(void)
{
	_mat rotateX, rotateY, rotateZ, scale, translation, result;

	D3DXMatrixRotationZ(&rotateZ, m_rotation.z);
    D3DXMatrixRotationY(&rotateY, m_rotation.y);
    D3DXMatrixRotationX(&rotateX, m_rotation.x);
    
    D3DXMatrixScaling(&scale, m_scale.x, 
                              m_scale.y,
                              m_scale.z);
    
    D3DXMatrixTranslation(&translation, m_position.x, 
                                        m_position.y,
                                        m_position.z);

	m_worldMat = scale * rotateX * rotateY * rotateZ * translation;
}
