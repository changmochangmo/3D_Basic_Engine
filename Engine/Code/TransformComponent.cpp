#include "EngineStdafx.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "DataStore.h"

USING(Engine)
CTransformComponent::CTransformComponent(void)  
{
}

CTransformComponent::~CTransformComponent(void)
{
}

SHARED(CComponent) CTransformComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CTransformComponent) pClone(new CTransformComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);

	pClone->SetPosition(m_position);
	pClone->SetRotation(m_rotation);
	pClone->SetScale(m_scale);

	return pClone;
}

void CTransformComponent::Awake(void)
{
	__super::Awake();
	m_componentID = (int)m_s_componentID;
}

void CTransformComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
	_bool isStatic = m_pOwner->GetIsStatic();
	std::wstring layerKey = m_pOwner->GetLayerKey();
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

void CTransformComponent::Translate(_float3 translation)
{
	_mat rotate;
	
	D3DXMatrixRotationYawPitchRoll(&rotate, D3DXToRadian(m_rotation.y), D3DXToRadian(m_rotation.x), D3DXToRadian(m_rotation.z));
	D3DXVec3TransformCoord(&translation, &translation, &rotate);
	m_position += translation * GET_DT;
}

void CTransformComponent::MoveTowards(_float3& thisPosition, _float3 targetPosition, _float speed)
{
}

void CTransformComponent::Lerp(_float3& thisPosition, _float3 targetPosition, _float speed)
{
	_float3 dir = targetPosition - thisPosition;
	D3DXVec3Normalize(&dir, &dir);
	
	if (Engine::Distance(targetPosition, thisPosition) >= 0.01f)
	{
		thisPosition += dir * speed * GET_DT;
	}
	else
	{
		thisPosition = targetPosition;
	}

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
