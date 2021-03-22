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

	inline constexpr unsigned int HashCode(const char* str)
	{
		return str[0] ? static_cast<unsigned int>(str[0]) + 0xEDB8832Full * HashCode(str + 1) : 8603;
		// https://m.blog.naver.com/PostView.nhn?blogId=devmachine&logNo=220952781191&proxyReferer=https:%2F%2Fwww.google.com%2F
	}

	inline float MathfMax(float _value_1, float _value_2)
	{
		if (_value_1 > _value_2)
			return _value_1;
		else
			return _value_2;
	}

	inline float MathfMin(float _value_1, float _value_2)
	{
		if (_value_1 > _value_2)
			return _value_2;
		else
			return _value_1;
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

	inline _float Distance(_float3 & thisPosition, _float3 targetPosition)
	{
		_float x = thisPosition.x - targetPosition.x;    // �� a�� ����
		_float y = thisPosition.y - targetPosition.y;    // �� b�� ����
		_float z = thisPosition.z - targetPosition.z;    // �� b�� ����

		_float c = sqrt((x * x) + (y * y) + (z * z));
		return c;
	}
}



#endif // !ENGINEFUNCTION_H





