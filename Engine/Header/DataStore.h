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
private:
				void					InitResource		(std::wstring sourcePath) override;
				void					ParsingData			(std::wstring filePath, 
															 std::wstring fileName);

				std::wstring			GetLayerKey			(const std::wstring& fullPath);
				std::wstring			GetObjectKey		(const std::wstring& fullPath);
				std::wstring			GetVariableKey		(const std::wstring& lineFromFile);
				std::wstring			GetKeyValue			(const std::wstring& lineFromFile);

	friend		std::wstringstream&		operator >>			(std::wstringstream& in, D3DXVECTOR3& float3);

private:
	//VariableKey, KeyValue
	typedef std::unordered_map<std::wstring, std::wstring>	_VarKeyMap;
	//ObjectKey
	typedef std::unordered_map<std::wstring, _VarKeyMap>	_ObjectKeyMap;
	//DataKey
	typedef std::unordered_map<std::wstring, _ObjectKeyMap> _DataKeyMap;
					_DataKeyMap		m_mCurDataMap;
					_DataKeyMap		m_mStaticDataMap;

public:
	template <typename T>
	bool GetValue(_bool isStatic, std::wstring sectionKey, 
				  std::wstring objectKey, std::wstring varKey, T& result)
	{
		_DataKeyMap* pDataMap = nullptr;
		if (isStatic)
			pDataMap = &m_mStaticDataMap;
		else
			pDataMap = &m_mCurDataMap;

		auto& iter_section = pDataMap->find(sectionKey);
		if (iter_section == pDataMap->end())
		{
			MSG_BOX(__FILE__, (L"sectionKey [" + sectionKey + L"] is missing in GetValue").c_str());
			return false;
		}

		auto& iter_object = iter_section->second.find(objectKey);
		if (iter_object == iter_section->second.end())
		{
			MSG_BOX(__FILE__, (L"objectKey [" + objectKey + L"] is missing in GetValue").c_str());
			return false;
		}

		auto& iter_var = iter_object->second.find(varKey);
		if (iter_var == iter_object->second.end())
		{
			MSG_BOX(__FILE__,
					(L"object : ["	+ objectKey + 
					 L"] var: ["	+ varKey	 + L"] Missing varKey in GetValue").c_str());
			return false;
		}

		std::wstringstream ss(iter_var->second);

		ss << std::boolalpha;
		ss >> result;

		return true;
	}
};
END
#endif // !DATASTORE_H