#include "EngineStdafx.h"
#include "GraphicsManager.h"
#include "MeshStore.h"
#include "DataStore.h"
#include "GameObject.h"

USING(Engine)
CMeshC::CMeshC(void)  
{
}


CMeshC::~CMeshC(void)
{
	OnDestroy();
}

SP(CComponent) CMeshC::MakeClone(CGameObject* pObject)
{
	SP(CMeshC) spClone(new CMeshC);
	__super::InitClone(spClone, pObject);

	spClone->SetMeshKey(m_meshKey);
	spClone->SetMeshData(m_pMeshData);

	return spClone;
}

void CMeshC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;;
}

void CMeshC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	_bool isStatic = m_pOwner->GetIsStatic();
	_int ownerDataID = m_pOwner->GetDataID();
	std::wstring objectKey = m_pOwner->GetObjectKey();

	if ((GET_VALUE(isStatic, ownerDataID, objectKey, L"meshKey", m_meshKey) == false) && m_meshKey == L"")
		m_meshKey = L"Cube";

	m_pMeshData = CMeshStore::GetInstance()->GetMeshData(m_meshKey);
}

void CMeshC::FixedUpdate(SP(CComponent) spThis)
{
}

void CMeshC::Update(SP(CComponent) spThis)
{
}

void CMeshC::LateUpdate(SP(CComponent) spThis)
{
}

void CMeshC::OnDestroy(void)
{
}

void CMeshC::OnEnable(void)
{
}

void CMeshC::OnDisable(void)
{
}
