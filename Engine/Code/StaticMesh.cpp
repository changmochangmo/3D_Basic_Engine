#include "EngineStdafx.h"
#include "StaticMesh.h"


USING(Engine)
CStaticMesh::CStaticMesh()
{
}


CStaticMesh::~CStaticMesh()
{
	OnDestory();
}

void CStaticMesh::Awake(void)
{
	m_meshType = (_int)EMeshType::Static;
}

void CStaticMesh::Start(void)
{
}

void CStaticMesh::OnDestory(void)
{
	m_pAdjacency->Release();
	m_pSubset->Release();
	m_pMesh->Release();
}

//void CStaticMesh::PreRender(void)
//{
//}
//
//void CStaticMesh::Render(void) const
//{
//	for (_ulong i = 0; i < m_subsetCount; ++i)
//		m_pMesh->DrawSubset(i);
//}
//
//void CStaticMesh::PostRender(void)
//{
//}
