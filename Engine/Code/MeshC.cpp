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

	for (auto& meshData : m_vMeshDatas)
		spClone->AddMeshData(meshData->MakeClone());

	spClone->m_minVertex = m_minVertex;
	spClone->m_maxVertex = m_maxVertex;
	spClone->m_meshSize  = m_meshSize;

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

		_int numOfMeshData;
		GET_VALUE(isStatic, dataID, objectKey, L"numOfMeshData", numOfMeshData);

		std::wstring meshKey;
		for (_int i = 0; i < numOfMeshData; ++i)
		{
			GET_VALUE(isStatic, dataID, objectKey, L"meshKey" + std::to_wstring(i), meshKey);
			m_vMeshDatas.emplace_back(CMeshStore::GetInstance()->GetMeshData(meshKey));
		}

		GenMinMaxVtx();
	}
}

void CMeshC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);

	for (auto& meshData : m_vMeshDatas)
		meshData->Start();
}

void CMeshC::FixedUpdate(SP(CComponent) spThis)
{
}

void CMeshC::Update(SP(CComponent) spThis)
{
	for (auto& meshData : m_vMeshDatas)
		meshData->Update();
}

void CMeshC::LateUpdate(SP(CComponent) spThis)
{
}

void CMeshC::OnDestroy(void)
{
	for (auto& meshData : m_vMeshDatas)
		meshData->FreeClone();
}

void CMeshC::OnEnable(void)
{
}

void CMeshC::OnDisable(void)
{
}

void CMeshC::AddMeshData(CMesh * pMeshData)
{
	m_vMeshDatas.emplace_back(pMeshData);
}

void CMeshC::ChangeMesh(std::wstring const & meshKey, _int index)
{
	_int numOfMeshData = (_int)m_vMeshDatas.size();
	if (index < 0 || index > numOfMeshData)
	{
		MSG_BOX(__FILE__, L"index is broken in ChangeMesh");
		ABORT;
	}
	else if (index == numOfMeshData)
		m_vMeshDatas.emplace_back(CMeshStore::GetInstance()->GetMeshData(meshKey));
	else
	{
		if (m_vMeshDatas[index] != nullptr)
			m_vMeshDatas[index]->FreeClone();

		m_vMeshDatas[index] = CMeshStore::GetInstance()->GetMeshData(meshKey);
	}

	GenMinMaxVtx();
}

void CMeshC::GenMinMaxVtx(void)
{
	m_minVertex = MAX_VECTOR;
	m_maxVertex = -MAX_VECTOR;
	for (auto& mesh : m_vMeshDatas)
	{
		_float3 minVtx = mesh->GetMinVertex();
		_float3 maxVtx = mesh->GetMaxVertex();

		if (minVtx.x < m_minVertex.x)
			m_minVertex.x = minVtx.x;
		if (minVtx.y < m_minVertex.y)
			m_minVertex.y = minVtx.y;
		if (minVtx.z < m_minVertex.z)
			m_minVertex.z = minVtx.z;

		if (maxVtx.x > m_maxVertex.x)
			m_maxVertex.x = maxVtx.x;
		if (maxVtx.y > m_maxVertex.y)
			m_maxVertex.y = maxVtx.y;
		if (maxVtx.z > m_maxVertex.z)
			m_maxVertex.z = maxVtx.z;
	}

	m_meshSize = m_maxVertex - m_minVertex;
}
