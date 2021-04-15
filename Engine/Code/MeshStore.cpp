#include "EngineStdafx.h"
#include "MeshStore.h"
#include "DeviceManager.h"
#include "StaticMesh.h"

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
		delete mesh.second;
	m_mStaticMeshData.clear();

	for (auto& mesh : m_mCurSceneMeshData)
		delete mesh.second;
	m_mCurSceneMeshData.clear();
}

void CMeshStore::ClearCurResource(void)
{
	for (auto& mesh : m_mCurSceneMeshData)
		delete mesh.second;
	m_mCurSceneMeshData.clear();
}

const CMesh* CMeshStore::GetMeshData(std::wstring meshKey)
{
	auto iter_find_static = m_mStaticMeshData.find(meshKey);
	if (iter_find_static != m_mStaticMeshData.end())
		return iter_find_static->second;

	auto iter_find_cur = m_mCurSceneMeshData.find(meshKey);
	if (iter_find_cur != m_mCurSceneMeshData.end())
		return iter_find_cur->second;

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
		CStaticMesh* pStaticMesh = new CStaticMesh;
		pStaticMesh->Awake();

		if (FAILED(D3DXLoadMeshFromX(fullFilePath.c_str(),
									 D3DXMESH_MANAGED,
									 GET_DEVICE,
									 &pStaticMesh->m_pAdjacency,
									 &pStaticMesh->m_pSubset,
									 NULL,
									 &pStaticMesh->m_subsetCount,
									 &pStaticMesh->m_pMesh)))
		{
			MSG_BOX(__FILE__, L"Load X-Mesh Failed Parsing Mesh");
			ABORT;
		}

		pStaticMesh->m_pMtrl = (D3DXMATERIAL*)pStaticMesh->m_pSubset->GetBufferPointer();

		if (m_isStatic)
			m_mStaticMeshData[RemoveExtension(fileName)] = pStaticMesh;
		else
			m_mCurSceneMeshData[RemoveExtension(fileName)] = pStaticMesh;
	}
	else //Dynamic Mesh
	{

	}
}