#include "EngineStdafx.h"
#include "DataStore.h"

#include <fstream>

USING(Engine)
IMPLEMENT_SINGLETON(CDataStore);

void CDataStore::Awake(void)
{
	__super::Awake();
	m_fpResourceHandler = std::bind(&CDataStore::ParsingData, this, std::placeholders::_1, std::placeholders::_2);
	m_resourcePath = L"..\\..\\Resource\\Data";
}

void CDataStore::Start(void)
{
	__super::Start();
}

void CDataStore::OnDestroy(void)
{
	delete[] m_mpCurDataMap;
	delete[] m_mpStaticDataMap;
}

void CDataStore::ClearCurResource(void)
{
	for (_uint i = 0; i < m_numOfSection; ++i)
		m_mpCurDataMap[i].clear();
}

void CDataStore::InitDataForScene(std::wstring curScene)
{
	InitResource(m_resourcePath + L"\\" + curScene);
}

void CDataStore::InitDataMap(_uint numOfDataID)
{
	m_numOfSection		= numOfDataID;

	m_mpCurDataMap		= new _FileKeyMap[numOfDataID];
	m_mpStaticDataMap	= new _FileKeyMap[numOfDataID];

	m_vHashKey.resize(numOfDataID);


	//엔진 쪽의 데이터 섹션
	AddDataSection(L"Engine", (_uint)EDataID::Engine);
	AddDataSection(L"Component", (_uint)EDataID::Component);
	AddDataSection(L"DebugObject", (_uint)EDataID::DebugObject);
}

void CDataStore::AddDataSection(std::wstring sectionKey, _uint ID)
{
	m_vHashKey[ID] = sectionKey;
}

void CDataStore::InitResource(std::wstring sourcePath)
{
	__super::InitResource(sourcePath);
}

void CDataStore::ParsingData(std::wstring filePath, std::wstring fileName)
{
	std::wifstream readFile;
	std::wstring fullPath = filePath + L"\\" + fileName;
	readFile.open(fullPath.c_str());


	if (readFile.is_open())
	{
		std::wstring line;
		std::wstring sectionKey = GetLastDirName(fullPath);
		std::wstring objectKey = GetFileName(fullPath);
		std::wstring variableKey;
		std::wstring keyValue;


		while (!readFile.eof() && std::getline(readFile, line))
		{
			_size symbolPos = line.find('=');
			if (symbolPos != std::wstring::npos)
			{
				variableKey = GetVariableKey(line, symbolPos);
				keyValue = GetKeyValue(line, symbolPos);

				if (m_isStatic)
					m_mpStaticDataMap[GetIndex(sectionKey)][objectKey][variableKey] = keyValue;
				else
					m_mpCurDataMap[GetIndex(sectionKey)][objectKey][variableKey] = keyValue;
			}
		}
	}
}

_int CDataStore::GetIndex(std::wstring sectionKey)
{
	for (_uint i = 0; i < m_vHashKey.size(); ++i)
	{
		if (m_vHashKey[i] == sectionKey)
			return i;
	}

	return -1;
}

std::wstring CDataStore::GetVariableKey(const std::wstring & lineFromFile, _size symbolPos)
{
	return lineFromFile.substr(0, symbolPos);
}

std::wstring CDataStore::GetKeyValue(const std::wstring & lineFromFile, _size symbolPos)
{
	return lineFromFile.substr(++symbolPos);
}

