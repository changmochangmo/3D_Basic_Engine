#include "EngineStdafx.h"
#include "DebugC.h"
#include "Object.h"
#include "DataStore.h"
#include "MeshStore.h"
#include "Mesh.h"

USING(Engine)
CDebugC::CDebugC()
{
}


CDebugC::~CDebugC()
{
	OnDestroy();
}

SP(CComponent) CDebugC::MakeClone(CObject * pObject)
{
	SP(CDebugC) spClone(new CDebugC);
	__super::InitClone(spClone, pObject);
	spClone->m_vMeshDatas.resize((_int)EDebugMT::NumOfDebugMT);
	for (_int i = 0; i < (_int)EDebugMT::NumOfDebugMT; ++i)
	{
		if (m_vMeshDatas[i] != nullptr)
			spClone->m_vMeshDatas[i] = m_vMeshDatas[i]->MakeClone();
	}

	spClone->m_debugType	= m_debugType;
	spClone->m_renderID		= m_renderID;
	return spClone;
}

void CDebugC::Awake(void)
{
	__super::Awake();
	m_componentID	= (_int)m_s_componentID;
	m_renderID		= (_int)ERenderID::WireFrame;
	m_isEnabled		= true;

	m_vMeshDatas.resize((_int)EDebugMT::NumOfDebugMT);
	if (m_pOwner->GetAddExtra() == false)
	{
		_bool isStatic			= m_pOwner->GetIsStatic();
		_int dataID				= m_pOwner->GetDataID();
		std::wstring objectKey	= m_pOwner->GetObjectKey();

		std::wstring debugMeshKey;
		GET_VALUE(isStatic, dataID, objectKey, L"debugMeshKey", debugMeshKey);
		m_vMeshDatas[(_int)EDebugMT::BV] = CMeshStore::GetInstance()->GetMeshData(debugMeshKey);

		if (debugMeshKey == L"Sphere")
			m_debugType = (_int)EDebugBV::Sphere;
		else if (debugMeshKey == L"Cube")
			m_debugType = (_int)EDebugBV::AABB;
	}
}

void CDebugC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	for (_int i = 0; i < (_int)EDebugMT::NumOfDebugMT; ++i)
	{
		if (m_vMeshDatas[i] != nullptr)
			m_vMeshDatas[i]->Start();
	}

	m_spTransform	= m_pOwner->GetComponent<CTransformC>();
	m_spMesh		= m_pOwner->GetComponent<CMeshC>();
	//SetupBV();
}

void CDebugC::FixedUpdate(SP(CComponent) spThis)
{
}

void CDebugC::Update(SP(CComponent) spThis)
{
	for (_int i = 0; i < (_int)EDebugMT::NumOfDebugMT; ++i)
	{
		if (m_vMeshDatas[i] != nullptr)
			m_vMeshDatas[i]->Update();
	}
}

void CDebugC::LateUpdate(SP(CComponent) spThis)
{
}

void CDebugC::OnDestroy(void)
{
	for (_int i = 0; i < (_int)EDebugMT::NumOfDebugMT; ++i)
	{
		if (m_vMeshDatas[i] != nullptr)
			m_vMeshDatas[i]->FreeClone();
	}
}

void CDebugC::OnEnable(void)
{
}

void CDebugC::OnDisable(void)
{
}

void CDebugC::SetupBV(void)
{
	CMesh* pMesh = m_spMesh->GetMeshData();
	if (pMesh->GetMeshType() == (_int)EMeshType::Static)
	{
		_float3 minPoint = pMesh->GetMinVertex();
		_float3 maxPoint = pMesh->GetMaxVertex();

		m_offset	= (minPoint + maxPoint) / 2.f;
		m_size		= maxPoint - minPoint;
	}
}

void CDebugC::ChangeMesh(std::wstring const & meshKey)
{
	if (m_vMeshDatas[(_int)EDebugMT::Mesh] != nullptr)
		m_vMeshDatas[(_int)EDebugMT::Mesh]->FreeClone();

	m_vMeshDatas[(_int)EDebugMT::Mesh] = CMeshStore::GetInstance()->GetMeshData(meshKey);
}
