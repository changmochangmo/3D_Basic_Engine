#include "EngineStdafx.h"
#include "TriColorMesh.h"


USING(Engine)

void CTriColorMesh::InitPrototype(void)
{
	m_vertexSize = sizeof(VTX_COLOR);
	m_vertexCount = 3;
	m_FVF = FVF_COLOR;

	CMesh::InitPrototype();

	VTX_COLOR* pVertices = nullptr;
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].position	= _float3(-0.5, -0.5, 0);
	pVertices[0].color		= D3DCOLOR_ARGB(255, 255, 0, 0);

	pVertices[1].position	= _float3(0, 0.5, 0);
	pVertices[1].color		= D3DCOLOR_ARGB(255, 255, 0, 0);
			   
	pVertices[1].position	= _float3(0.5, -0.5, 0);
	pVertices[1].color		= D3DCOLOR_ARGB(255, 255, 0, 0);

	m_pVertexBuffer->Unlock();
}
void CTriColorMesh::Free(void)
{
}
CTriColorMesh * CTriColorMesh::Create(void)
{
	CTriColorMesh* pInstance;
	return nullptr;
}
CTriColorMesh::CTriColorMesh()
{
}


CTriColorMesh::~CTriColorMesh()
{
}
