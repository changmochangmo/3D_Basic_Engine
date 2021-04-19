#include "EngineStdafx.h"
#include "MeshStore.h"
#include "DeviceManager.h"
#include "StaticMesh.h"
#include "DynamicMesh.h"


#include <fstream>
#include <algorithm>
#include <filesystem>

USING(Engine)
IMPLEMENT_SINGLETON(CMeshStore)

void CMeshStore::Awake(void)
{
	__super::Awake();
	m_fpResourceHandler = std::bind(&CMeshStore::ParsingMesh, this, std::placeholders::_1, std::placeholders::_2);
	m_resourcePath = L"..\\..\\Resource\\Mesh";
}

void CMeshStore::Start(void)
{
	__super::Start();
}

void CMeshStore::OnDestroy(void)
{
	for (auto& mesh : m_mStaticMeshData)
		mesh.second->Free();
	m_mStaticMeshData.clear();

	for (auto& mesh : m_mCurSceneMeshData)
		mesh.second->Free();
	m_mCurSceneMeshData.clear();
}

void CMeshStore::ClearCurResource(void)
{
	for (auto& mesh : m_mCurSceneMeshData)
		mesh.second->Free();
	m_mCurSceneMeshData.clear();
}

CMesh* CMeshStore::GetMeshData(std::wstring meshKey)
{
	auto iter_find_static = m_mStaticMeshData.find(meshKey);
	if (iter_find_static != m_mStaticMeshData.end())
		return iter_find_static->second->MakeClone();

	auto iter_find_cur = m_mCurSceneMeshData.find(meshKey);
	if (iter_find_cur != m_mCurSceneMeshData.end())
		return iter_find_cur->second->MakeClone();

	return nullptr;
}

void CMeshStore::InitMeshForScene(std::wstring curScene)
{
	InitResource(m_resourcePath + L"\\" + curScene);
}

void CMeshStore::InitResource(std::wstring sourcePath)
{
	__super::InitResource(sourcePath);
}

void CMeshStore::ParsingMesh(std::wstring filePath, std::wstring fileName)
{
	std::wstring fullFilePath = filePath + L"\\" + fileName;
	
	if (GetLastDirName(fullFilePath) == L"Static")
	{	
		if (m_isStatic)
			m_mStaticMeshData[RemoveExtension(fileName)] = CStaticMesh::Create(filePath, fileName);
		else
			m_mCurSceneMeshData[RemoveExtension(fileName)] = CStaticMesh::Create(filePath, fileName);
	}
	else if (GetLastDirName(fullFilePath) == L"Dynamic")//Dynamic Mesh
	{
		if (m_isStatic)
			m_mStaticMeshData[RemoveExtension(fileName)] = CDynamicMesh::Create(filePath, fileName);
		else
			m_mCurSceneMeshData[RemoveExtension(fileName)] = CDynamicMesh::Create(filePath, fileName);
	}

}

