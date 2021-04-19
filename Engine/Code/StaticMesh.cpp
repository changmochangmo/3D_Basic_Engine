#include "EngineStdafx.h"
#include "StaticMesh.h"
#include "DeviceManager.h"

USING(Engine)
CStaticMesh::CStaticMesh()
{
}


CStaticMesh::~CStaticMesh()
{
}

CMesh* CStaticMesh::MakeClone(void)
{
	CStaticMesh* pClone = new CStaticMesh;
	pClone->m_pMesh			= m_pMesh;
	pClone->m_pAdjacency	= m_pAdjacency;
	pClone->m_pSubset		= m_pSubset;
	pClone->m_pMtrl			= m_pMtrl;
	pClone->m_subsetCount	= m_subsetCount;
	pClone->m_meshType		= m_meshType;

	return pClone;
}

void CStaticMesh::FreeClone(void)
{
	OnDestory();
}

void CStaticMesh::Awake(std::wstring const& filePath, std::wstring const& fileName)
{
	m_meshType = (_int)EMeshType::Static;

	if (FAILED(D3DXLoadMeshFromX((filePath + L"\\" + fileName).c_str(),
								 D3DXMESH_MANAGED,
								 GET_DEVICE,
								 &m_pAdjacency,
								 &m_pSubset,
								 NULL,
								 &m_subsetCount,
								 &m_pMesh)))
	{
		MSG_BOX(__FILE__, L"Load X-Mesh Failed in CStaticMash::Awake");
		ABORT;
	}
	
	m_pMtrl = (D3DXMATERIAL*)m_pSubset->GetBufferPointer();
}

void CStaticMesh::Start(void)
{
}

void CStaticMesh::Update(void)
{
}

void CStaticMesh::OnDestory(void)
{
	delete this;
}

CStaticMesh * CStaticMesh::Create(std::wstring const & filePath, std::wstring const & fileName)
{
	CStaticMesh* pStaticMesh = new CStaticMesh;
	pStaticMesh->Awake(filePath, fileName);

	return pStaticMesh;
}

void CStaticMesh::Free(void)
{
	m_pAdjacency->Release();
	m_pSubset->Release();
	m_pMesh->Release();
	OnDestory();
}
