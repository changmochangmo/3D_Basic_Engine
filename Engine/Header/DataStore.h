#ifndef DATASTORE_H
#define DATASTORE_H

#include "ResourceStore.h"

BEGIN(Engine)
class ENGINE_DLL CDataStore final : public CResourceStore
{
	DECLARE_SINGLETON(CDataStore)
public:
				void					Awake				(void) override;
				void					Start				(void) override;
				void					OnDestroy			(void) override;

				void					ClearCurResource	(void) override;

				void					InitDataForScene	(std::wstring curScene);
				void					InitDataMap			(_uint numOfDataID);

				void					AddDataSection		(std::wstring sectionKey, _uint ID);
private:
				void					InitResource		(std::wstring sourcePath) override;
				void					ParsingData			(std::wstring filePath, 
															 std::wstring fileName);

				_int					GetIndex			(std::wstring sectionKey);

				std::wstring			GetVariableKey		(const std::wstring& lineFromFile, _size symbolPos);
				std::wstring			GetKeyValue			(const std::wstring& lineFromFile, _size symbolPos);

	friend		std::wstringstream&		operator >>			(std::wstringstream& in, _float3& float3);
	friend		std::wstringstream&		operator >>			(std::wstringstream& in, _float2& float3);

private:
	//VariableKey, KeyValue
	typedef std::unordered_map<std::wstring, std::wstring>	_VarKeyMap;
	//FileNameKey
	typedef std::unordered_map<std::wstring, _VarKeyMap>	_FileKeyMap;
	//DataKey
	_FileKeyMap*	m_mpCurDataMap;
	_FileKeyMap*	m_mpStaticDataMap;
	_uint			m_numOfSection;

	std::vector<std::wstring> m_vHashKey;
	

public:
	template <typename T>
	bool GetValue(_bool isStatic, _int dataID, 
				  std::wstring objectKey, std::wstring varKey, T& result)
	{
		_FileKeyMap** ppDataMap = nullptr;
		if (isStatic)
			ppDataMap = &m_mpStaticDataMap;
		else
			ppDataMap = &m_mpCurDataMap;

		if ((_uint)dataID >= m_numOfSection)
		{
			MSG_BOX(__FILE__, std::wstring(L"dataID is out of range").c_str());
			ABORT;
		}
		
		auto& iter_object = (*ppDataMap)[dataID].find(objectKey);
		if (iter_object == (*ppDataMap)[dataID].end())
		{
			MSG_BOX(__FILE__, (L"objectKey [" + objectKey + L"] is missing in GetValue").c_str());
			ABORT;
		}

		auto& iter_var = iter_object->second.find(varKey);
		if (iter_var == iter_object->second.end())
		{
			MSG_BOX(__FILE__,
					(L"object : ["	+ objectKey + 
					 L"] var: ["	+ varKey	 + L"] Missing varKey in GetValue").c_str());
			ABORT;
		}

		//stringstream�̶�� ���̺귯���� �ִµ�
		//���⿡ ��Ʈ�� ���� �ְ�
		std::wstringstream ss(iter_var->second);

		//bool type�� �������� �Լ�
		ss << std::boolalpha;

		//�̷��� �ٸ� Ÿ���� ������ �־��ָ�, ��Ʈ���� �˾Ƽ� �� Ÿ�Կ�
		//�´� ������ ��ȯ�ؼ� �־���.
		ss >> result;
		
		return true;
	}
};
END
#endif // !DATASTORE_H