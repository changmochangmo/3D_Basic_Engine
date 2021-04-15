#include "EngineStdafx.h"
#include "GraphicsManager.h"
#include "MeshStore.h"
#include "DataStore.h"
#include "Object.h"

USING(Engine)
CMeshC::CMeshC(void)  
{
}


CMeshC::~CMeshC(void)
{
	OnDestroy();
}

SP(CComponent) CMeshC::MakeClone(CObject* pObject)
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

	if (m_pOwner->GetAddExtra() == false)
	{
		_bool isStatic = m_pOwner->GetIsStatic();
		_int dataID = m_pOwner->GetDataID();
		std::wstring objectKey = m_pOwner->GetObjectKey();

		GET_VALUE(isStatic, dataID, objectKey, L"meshKey", m_meshKey);
		m_pMeshData = CMeshStore::GetInstance()->GetMeshData(m_meshKey);
	}
}

void CMeshC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
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

void CMeshC::ChangeMesh(std::wstring const & meshKey)
{
	m_meshKey	= meshKey;
	m_pMeshData = CMeshStore::GetInstance()->GetMeshData(m_meshKey);
}
