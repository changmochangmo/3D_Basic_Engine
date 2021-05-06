#include "EngineStdafx.h"
#include "MeshData.h"


USING(Engine)
CMeshData::CMeshData()
{
}


CMeshData::~CMeshData()
{
}

void CMeshData::Awake(std::wstring const & filePath, std::wstring const & fileName)
{
	m_meshKey = RemoveExtension(fileName);
}

void CMeshData::AddTexNameToList(std::wstring texName)
{
	m_vTexList.emplace_back(texName);
}
