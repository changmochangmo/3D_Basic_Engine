#ifndef ENGINEFUNCTION_H
#define ENGINEFUNCTION_H



namespace Engine
{
	//smart pointer랑 private Destructor사이의 문제 해결
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

	//ClassName 따오는 함수
	template <typename T>
	std::wstring GetCurClassName(void)
	{
		std::wstring className = StrToWStr(typeid(T).name());
		_size nameStartPos = className.find_last_of(':');
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
		_size nameStartPos = className.find_last_of(':');
		if (nameStartPos == std::wstring::npos)
			className.erase(0, 7);
		else
			className.erase(0, nameStartPos + 2);

		return className;
	}

	//String 변환 함수
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

	//FileName string에서 확장자명 떼는 함수
	inline std::wstring RemoveExtension(const std::wstring& fileName)
	{
		_size lastindex = fileName.find_last_of('.');
		return fileName.substr(0, lastindex);
	}



	//현재 파일 이름 따오는 함수
	inline std::wstring GetCurFileName(const std::string& str)
	{
		return StrToWStr(str.substr(str.find_last_of('\\') + 1));
	}

	inline std::wstringstream& operator >> (std::wstringstream& in, _float3 & float3)
	{
		std::wstring vecStr;
		std::wstring vecStrX, vecStrY, vecStrZ;

		in >> vecStr;

		_size xEndPos, yEndPos;

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

	inline std::wstringstream& operator >> (std::wstringstream& in, _float2 & float2)
	{
		std::wstring vecStr;
		std::wstring vecStrX, vecStrY;

		in >> vecStr;

		_size xEndPos;

		xEndPos = vecStr.find_first_of(L",");

		vecStrX = vecStr.substr(0, xEndPos);
		vecStrY = vecStr.substr(++xEndPos);

		std::wstringstream ssX(vecStrX);
		std::wstringstream ssY(vecStrY);

		ssX >> float2.x;
		ssY >> float2.y;

		return in;
	}


	template<class T> inline T	operator	~	(T a)		{ return (T)~(int)a; }
	template<class T> inline T	operator	|	(T a, T b)	{ return (T)((int)a | (int)b); }
	template<class T> inline T	operator	&	(T a, T b)	{ return (T)((int)a & (int)b); }
	template<class T> inline T	operator	^	(T a, T b)	{ return (T)((int)a ^ (int)b); }
	template<class T> inline T& operator	|=	(T& a, T b) { return (T&)((int&)a |= (int)b); }
	template<class T> inline T& operator	&=	(T& a, T b) { return (T&)((int&)a &= (int)b); }
	template<class T> inline T& operator	^=	(T& a, T b) { return (T&)((int&)a ^= (int)b); }
}



#endif // !ENGINEFUNCTION_H





