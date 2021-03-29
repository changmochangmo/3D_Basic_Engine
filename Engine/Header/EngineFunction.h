#ifndef ENGINEFUNCTION_H
#define ENGINEFUNCTION_H



namespace Engine
{
	//smart pointer�� private Destructor������ ���� �ذ�
	template <typename T>
	void SmartDeleter(T* something)
	{
		delete something;
	}

	template <typename T>
	void SafeDelete(T& ptr)
	{
		if (ptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}

	template <typename T>
	void SafeDeleteArray(T& ptr)
	{
		if (ptr)
		{
			delete[] ptr;
			ptr = nullptr;
		}
	}

	//ClassName ������ �Լ�
	template <typename T>
	std::wstring GetCurClassName(void)
	{
		std::wstring className = StrToWStr(typeid(T).name());
		_uint nameStartPos = className.find_last_of(':');
		if (nameStartPos == std::string::npos)
			className.erase(0, 7);
		else
			className.erase(0, nameStartPos + 2);

		return className;
	}

	template <typename T>
	std::wstring GetCurClassName(T* something)
	{
		std::wstring className = StrToWStr(typeid(*something).name());
		_uint nameStartPos = className.find_last_of(':');
		if (nameStartPos == std::string::npos)
			className.erase(0, 7);
		else
			className.erase(0, nameStartPos + 2);

		return className;
	}

	//String ��ȯ �Լ�
	inline std::wstring StrToWStr(const std::string& str)
	{
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.from_bytes(str);
	}

	inline std::string WStrToStr(const std::wstring& wstr)
	{
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.to_bytes(wstr);
	}

	//FileName string���� Ȯ���ڸ� ���� �Լ�
	inline std::wstring RemoveExtension(const std::wstring& fileName)
	{
		_uint lastindex = fileName.find_last_of('.');
		return fileName.substr(0, lastindex);
	}



	//���� ���� �̸� ������ �Լ�
	inline std::wstring GetCurFileName(const std::string& str)
	{
		return StrToWStr(str.substr(str.find_last_of('\\') + 1));
	}

	inline std::wstringstream& operator >> (std::wstringstream& in, D3DXVECTOR3 & float3)
	{
		std::wstring vecStr;
		std::wstring vecStrX, vecStrY, vecStrZ;

		in >> vecStr;

		size_t xEndPos, yEndPos;

		xEndPos = vecStr.find_first_of(L",");
		yEndPos = vecStr.find_last_of(L",");

		vecStrX = vecStr.substr(0, xEndPos);
		vecStrY = vecStr.substr(++xEndPos, yEndPos - xEndPos);
		vecStrZ = vecStr.substr(++yEndPos);

		std::wstringstream ssX(vecStrX);
		std::wstringstream ssY(vecStrY);
		std::wstringstream ssZ(vecStrZ);

		ssX >> float3.x;
		ssY >> float3.y;
		ssZ >> float3.z;

		return in;
	}
}



#endif // !ENGINEFUNCTION_H





