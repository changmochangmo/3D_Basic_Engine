#ifndef MULTITEXTURE_H
#define MULTITEXTURE_H

BEGIN(Engine)
class CTexture final
{
public:
	explicit CTexture(void);
	virtual ~CTexture(void) = default;

	HRESULT InsertTexture(const std::wstring& filePath, const std::wstring& fileName, const int& index = 1);
	const TEXTURE_DATA* GetTexInfo(const std::wstring& objectKey, const int& index = 1);

	void ReleaseTexture();

private:
	std::unordered_map<std::wstring, std::vector<TEXTURE_DATA*>> m_mTexture;
};
END

#endif