#include "EngineStdafx.h"
#include "MeshComponent.h"
#include "GraphicsManager.h"
#include "MeshStore.h"
#include "DataStore.h"
#include "GameObject.h"

USING(Engine)
CMeshComponent::CMeshComponent(void)  
{
}


CMeshComponent::~CMeshComponent(void)
{
}

SHARED(CComponent) CMeshComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CMeshComponent) spClone(new CMeshComponent);
	__super::InitClone(spClone, pObject);

	spClone->SetMeshKey(m_meshKey);
	spClone->SetMeshData(m_pMeshData);

	return spClone;
}

void CMeshComponent::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;;
}

void CMeshComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
	_bool isStatic = m_pOwner->GetIsStatic();
	_int ownerDataID = m_pOwner->GetDataID();
	std::wstring objectKey = m_pOwner->GetObjectKey();

	if (m_meshKey == L"" && (GET_VALUE(isStatic, ownerDataID, objectKey, L"meshKey", m_meshKey) == false))
		m_meshKey = L"Cube";

	m_pMeshData = CMeshStore::GetInstance()->GetMeshData(m_meshKey);
}

_uint CMeshComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CMeshComponent::Update(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CMeshComponent::LateUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

void CMeshComponent::OnDestroy(void)
{
}

void CMeshComponent::OnEnable(void)
{

}

void CMeshComponent::OnDisable(void)
{
}
