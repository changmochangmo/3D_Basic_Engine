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

	spClone->m_pBV			= m_pBV->MakeClone();
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

	if (m_pOwner->GetAddExtra() == false)
	{
		_bool isStatic			= m_pOwner->GetIsStatic();
		_int dataID				= m_pOwner->GetDataID();
		std::wstring objectKey	= m_pOwner->GetObjectKey();

		std::wstring debugMeshKey;
		GET_VALUE(isStatic, dataID, objectKey, L"debugMeshKey", debugMeshKey);
		m_pBV = CMeshStore::GetInstance()->GetMeshData(debugMeshKey);

		if (debugMeshKey == L"Sphere")
			m_debugType = (_int)EDebugBV::Sphere;
		else if (debugMeshKey == L"Cube")
			m_debugType = (_int)EDebugBV::AABB;
	}
}

void CDebugC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	m_pBV->Start();

	m_spTransform	= m_pOwner->GetComponent<CTransformC>();
	m_spMesh		= m_pOwner->GetComponent<CMeshC>();
	SetupBV();
}

void CDebugC::FixedUpdate(SP(CComponent) spThis)
{
}

void CDebugC::Update(SP(CComponent) spThis)
{
	m_pBV->Update();
}

void CDebugC::LateUpdate(SP(CComponent) spThis)
{
}

void CDebugC::OnDestroy(void)
{
	m_pBV->FreeClone();
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
