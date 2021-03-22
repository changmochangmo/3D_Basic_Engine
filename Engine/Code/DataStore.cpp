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
	m_mStaticDataMap.clear();
	m_mCurDataMap.clear();
}

void CDataStore::ClearCurResource(void)
{
	m_mCurDataMap.clear();
}

void CDataStore::InitDataForScene(std::wstring curScene)
{
	InitResource(m_resourcePath + L"\\" + curScene);
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
		std::wstring layerKey = GetLayerKey(fullPath);
		std::wstring objectKey = GetObjectKey(fullPath);
		std::wstring variableKey;
		std::wstring keyValue;



		while (!readFile.eof() && std::getline(readFile, line))
		{
			variableKey = GetVariableKey(line);
			keyValue = GetKeyValue(line);

			if(m_isStatic)
				m_mStaticDataMap[layerKey][objectKey][variableKey] = keyValue;
			else
				m_mCurDataMap[layerKey][objectKey][variableKey] = keyValue;
		}
	}
}

std::wstring CDataStore::GetLayerKey(const std::wstring & fullPath)
{
	size_t startPoint, endPoint;
	startPoint = fullPath.find_first_of(L"\\");
	startPoint = fullPath.find(L"\\", ++startPoint);
	startPoint = fullPath.find(L"\\", ++startPoint);
	startPoint = fullPath.find(L"\\", ++startPoint);
	startPoint = fullPath.find(L"\\", ++startPoint);
	endPoint = fullPath.find(L"\\", ++startPoint);

	return fullPath.substr(startPoint, endPoint - startPoint);
}

std::wstring CDataStore::GetObjectKey(const std::wstring & fullPath)
{
	size_t startPoint, endPoint;
	startPoint = fullPath.find_last_of('\\') + 1;
	endPoint = fullPath.find_last_of('.');

	return fullPath.substr(startPoint, endPoint - startPoint);
}

std::wstring CDataStore::GetVariableKey(const std::wstring & lineFromFile)
{
	size_t endPoint = lineFromFile.find_first_of('=');

	return lineFromFile.substr(0, endPoint);
}

std::wstring CDataStore::GetKeyValue(const std::wstring & lineFromFile)
{
	size_t startPoint = lineFromFile.find_first_of('=');
	return lineFromFile.substr(++startPoint);
}

