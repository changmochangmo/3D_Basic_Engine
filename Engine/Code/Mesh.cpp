#include "EngineStdafx.h"
#include "Mesh.h"


USING(Engine)
CMesh::CMesh()
{
}


CMesh::~CMesh()
{
}

void CMesh::AddTexNameToList(std::wstring texName)
{
	m_vTexList.emplace_back(texName);
}
