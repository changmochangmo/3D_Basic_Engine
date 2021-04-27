#include "EngineStdafx.h"
#include "GraphicsManager.h"
#include "MeshStore.h"
#include "DataStore.h"
#include "Object.h"
#include "Mesh.h"

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

	spClone->SetMeshData(m_pMeshData->MakeClone());
	spClone->m_renderID = m_renderID;

	return spClone;
}

void CMeshC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;;

	if (m_pOwner->GetAddExtra() == false)
	{
		_bool isStatic			= m_pOwner->GetIsStatic();
		_int dataID				= m_pOwner->GetDataID();
		std::wstring objectKey	= m_pOwner->GetObjectKey();

		std::wstring meshKey;
		GET_VALUE(isStatic, dataID, objectKey, L"meshKey", meshKey);
		m_pMeshData = CMeshStore::GetInstance()->GetMeshData(meshKey);

		GET_VALUE(isStatic, dataID, objectKey, L"renderID", m_renderID);
	}
}

void CMeshC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	m_pMeshData->Start();
}

void CMeshC::FixedUpdate(SP(CComponent) spThis)
{
}

void CMeshC::Update(SP(CComponent) spThis)
{
	m_pMeshData->Update();
}

void CMeshC::LateUpdate(SP(CComponent) spThis)
{
}

void CMeshC::OnDestroy(void)
{
	m_pMeshData->FreeClone();
}

void CMeshC::OnEnable(void)
{
}

void CMeshC::OnDisable(void)
{
}

void CMeshC::ChangeMesh(std::wstring const & meshKey)
{
	if (m_pMeshData != nullptr)
		m_pMeshData->FreeClone();
	m_pMeshData = CMeshStore::GetInstance()->GetMeshData(meshKey);
}
