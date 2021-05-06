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

CMeshData* CStaticMesh::MakeClone(void)
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

	pClone->m_meshKey		= m_meshKey;
	
	return pClone;
}

void CStaticMesh::FreeClone(void)
{
	OnDestory();
}

void CStaticMesh::Awake(std::wstring const& filePath, std::wstring const& fileName)
{
	__super::Awake(filePath, fileName);
	
	m_meshType = (_int)EMeshType::Static;

	if (FAILED(D3DXLoadMeshFromX((filePath + fileName).c_str(),
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

	_ulong FVF		= m_pMesh->GetFVF();
	_uint stride	= D3DXGetFVFVertexSize(FVF);
	_uint numOfVtx	= m_pMesh->GetNumVertices();


	for (_ulong i = 0; i < numOfVtx; ++i)
	{
		_float3 curPoint = *((_float3*)(((_ubyte*)pVertices) + (stride * i + byOffset)));
		if (curPoint.x > m_maxVertex.x)
			m_maxVertex.x = curPoint.x;
		if (curPoint.y > m_maxVertex.y)
			m_maxVertex.y = curPoint.y;
		if (curPoint.z > m_maxVertex.z)
			m_maxVertex.z = curPoint.z;

		if (curPoint.x < m_minVertex.x)
			m_minVertex.x = curPoint.x;
		if (curPoint.y < m_minVertex.y)
			m_minVertex.y = curPoint.y;
		if (curPoint.z < m_minVertex.z)
			m_minVertex.z = curPoint.z;
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
