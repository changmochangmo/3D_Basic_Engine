#include "EngineStdafx.h"
#include "MeshStore.h"
#include "DeviceManager.h"

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
	m_mStaticMeshData.clear();
	m_mCurSceneMeshData.clear();
}

void CMeshStore::ClearCurResource(void)
{
	m_mCurSceneMeshData.clear();
}

SP(_MeshData) CMeshStore::GetMeshData(std::wstring meshKey)
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
	SP(_MeshData)		newMesh(new _MeshData);

	newMesh->maxVertex = _float3(-FLT_MAX, -FLT_MAX, FLT_MAX);
	newMesh->minVertex = _float3(FLT_MAX, FLT_MAX, FLT_MAX);

	std::ifstream           fin;
	std::string             str;
	std::string::size_type  sz;

	std::vector<_float3>	vPosition;
	std::vector<_float3>	vNormal;
	std::vector<_float2>	vTexture;
	std::vector<_Face>		vFace;

	_float3                 position;;
	_float3                 normal;
	_float2                 uv;
	_Face					face;

	std::wstring fullFilePath = filePath + L"\\" + fileName;

	// Open the model file.
	fin.open(fullFilePath);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::getline(fin, str);
			if (str.size() > 2)
			{
				if (str[0] == 'v')
				{
					if (str[1] == ' ')
					{
						str = str.substr(2, str.size());
						position.x = std::stof(str, &sz); str = str.substr(sz + 1, str.size());
						position.y = std::stof(str, &sz); str = str.substr(sz + 1, str.size());
						position.z = std::stof(str, &sz);
						vPosition.emplace_back(position);

						if (position.x < newMesh->minVertex.x)
							newMesh->minVertex.x = position.x;
						if (position.y < newMesh->minVertex.y)
							newMesh->minVertex.y = position.y;
						if (position.z < newMesh->minVertex.z)
							newMesh->minVertex.z = position.z;

						if (position.x > newMesh->minVertex.x)
							newMesh->minVertex.x = position.x;
						if (position.y > newMesh->minVertex.y)
							newMesh->minVertex.y = position.y;
						if (position.z > newMesh->minVertex.z)
							newMesh->minVertex.z = position.z;
					}
					else if (str[1] == 'n')
					{
						str = str.substr(2, str.size());
						normal.x = std::stof(str, &sz); str = str.substr(sz + 1, str.size());
						normal.y = std::stof(str, &sz); str = str.substr(sz + 1, str.size());
						normal.z = std::stof(str, &sz);
						vNormal.emplace_back(normal);
					}
					else if (str[1] == 't')
					{
						str = str.substr(2, str.size());
						uv.x = std::stof(str, &sz); str = str.substr(sz + 1, str.size());
						uv.y = std::stof(str, &sz); str = str.substr(sz + 1, str.size());
						vTexture.emplace_back(uv);
					}
				}
				else if ((str[0] == 'f') && (str[1] == ' ')) //인덱스
				{
					int numOfSlash = 0;
					str = str.substr(2, str.size()); // 문자열의 2번부터 사이즈만큼


					for (_uint i = 0; i < str.size(); ++i) // /을만날때까지 값을게속증가시킨다.
					{
						if (str.at(i) == '/')
						{
							++numOfSlash;
						}
					}

					newMesh->vertexNumInFace = numOfSlash / 2; //왜 2를나눌까?

					for (_uint i = 0; i < newMesh->vertexNumInFace; ++i) // 값들 대입
					{	
						face.vertexIndex[i] = std::stoi(str, &sz) - 1; // 인덱스
						str = str.substr(sz + 1, str.size());
						face.uvIndex[i] = std::stoi(str, &sz) - 1; // 텍스쳐같은데 애매하네
						str = str.substr(sz + 1, str.size());
						face.normIndex[i] = std::stoi(str, &sz) - 1; // 노말값도 애매하네
						if (str.size() > sz)
							str = str.substr(sz + 1, str.size());
					}

					vFace.emplace_back(face);
				}
			}
		}
		
		newMesh->vertexSize = sizeof(_CustomVertex);
		newMesh->vertexCount = (_uint)vPosition.size();
		newMesh->faceCount = (_uint)vFace.size();
		newMesh->FVF = customFVF;

		newMesh->indexSize = sizeof(WORD);
		newMesh->indexFormat = D3DFMT_INDEX16;

		HRESULT result;

		result = GET_DEVICE->CreateVertexBuffer(
			newMesh->faceCount * 3 * newMesh->vertexSize,
			0,
			newMesh->FVF,
			D3DPOOL_MANAGED,
			&newMesh->vertexBuffer,
			nullptr);

		result = GET_DEVICE->CreateIndexBuffer(
			newMesh->faceCount * newMesh->vertexNumInFace * newMesh->indexSize,
			0,
			newMesh->indexFormat,
			D3DPOOL_MANAGED,
			&newMesh->indexBuffer,
			nullptr);


		_CustomVertex* pVertices = nullptr;

		newMesh->vertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
		for (_uint i = 0; i < newMesh->faceCount; ++i)
		{
			for (_uint j = 0; j < 3; ++j)
			{
				pVertices[i * 3 + j].position = vPosition[vFace[i].vertexIndex[j]];
				pVertices[i * 3 + j].uv = vTexture[vFace[i].uvIndex[j]];
				pVertices[i * 3 + j].normal = vNormal[vFace[i].normIndex[j]];
			}
		}
		newMesh->vertexBuffer->Unlock();

		WORD* pIndices = nullptr;
		newMesh->indexBuffer->Lock(0, 0, (void**)&pIndices, 0);
		for (_uint i = 0; i < newMesh->faceCount * newMesh->vertexNumInFace; ++i)
			pIndices[i] = i ;
		newMesh->indexBuffer->Unlock();


		if (m_isStatic)
			m_mStaticMeshData[RemoveExtension(fileName)] = newMesh;
		else
			m_mCurSceneMeshData[RemoveExtension(fileName)] = newMesh;

		newMesh.reset();
	}
}