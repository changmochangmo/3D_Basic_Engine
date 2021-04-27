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
	pClone->m_vTexList		= m_vTexList;

	pClone->m_meshSize		= m_meshSize;
	pClone->m_minVertex		= m_minVertex;
	pClone->m_maxVertex		= m_maxVertex;
	
	pClone->m_pVertices		= m_pVertices;
	pClone->m_numOfVtx		= m_numOfVtx;
	pClone->m_stride		= m_stride;

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
	
	void* pVertices = nullptr;
	m_pMesh->LockVertexBuffer(0, &pVertices);

	D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE];
	ZeroMemory(decl, sizeof(D3DVERTEXELEMENT9) * MAX_FVF_DECL_SIZE);
	m_pMesh->GetDeclaration(decl);

	_ubyte byOffset = 0;
	for (_ulong i = 0; i < MAX_FVF_DECL_SIZE; ++i)
	{
		if (decl[i].Usage == D3DDECLUSAGE_POSITION)
		{
			byOffset = (_ubyte)decl[i].Offset;
			break;
		}
	}

	_ulong FVF = m_pMesh->GetFVF();
	m_stride = D3DXGetFVFVertexSize(FVF);
	m_numOfVtx = m_pMesh->GetNumVertices();

	m_pVertices = new _float3[m_numOfVtx];

	for (_ulong i = 0; i < m_numOfVtx; ++i)
	{
		m_pVertices[i] = *((_float3*)(((_ubyte*)pVertices) + (m_stride * i + byOffset)));
		if (m_pVertices[i].x > m_maxVertex.x)
			m_maxVertex.x = m_pVertices[i].x;
		if (m_pVertices[i].y > m_maxVertex.y)
			m_maxVertex.y = m_pVertices[i].y;
		if (m_pVertices[i].z > m_maxVertex.z)
			m_maxVertex.z = m_pVertices[i].z;

		if (m_pVertices[i].x < m_minVertex.x)
			m_minVertex.x = m_pVertices[i].x;
		if (m_pVertices[i].y < m_minVertex.y)
			m_minVertex.y = m_pVertices[i].y;
		if (m_pVertices[i].z < m_minVertex.z)
			m_minVertex.z = m_pVertices[i].z;
	}

	m_meshSize = m_maxVertex - m_minVertex;

	m_pMtrl = (D3DXMATERIAL*)m_pSubset->GetBufferPointer();
	for (_size i = 0; i < m_subsetCount; ++i)
	{
		if(m_pMtrl[i].pTextureFilename != nullptr)
			AddTexNameToList(StrToWStr(m_pMtrl[i].pTextureFilename));
	}
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
