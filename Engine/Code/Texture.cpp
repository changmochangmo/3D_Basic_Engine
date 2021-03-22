#include "EngineStdafx.h"
#include "Texture.h"
#include "GraphicsManager.h"

USING(Engine)

CTexture::CTexture()
{
}

HRESULT CTexture::InsertTexture(const std::wstring& filePath, 
	const std::wstring& fileName, 
	const int& index)
{
	std::wstring objectKey = fileName.substr(0, fileName.find_first_of('.'));

	auto& iter_Find = m_mTexture.find(objectKey);
	if (iter_Find != m_mTexture.end())
		return E_FAIL;

	TEXTURE_DATA* pTexInfo = nullptr;
	for (int i = 0; i < index; ++i)
	{
		std::wstring fullFilePath = filePath + L"\\" + fileName;

		pTexInfo = new TEXTURE_DATA;
		if (FAILED(D3DXGetImageInfoFromFile(fullFilePath.c_str(), &pTexInfo->imageInfo)))
		{
			MSG_BOX(L"Error", L"Loading Image Info Failed");
			return E_FAIL;
		}
		if (FAILED(D3DXCreateTextureFromFileEx(GET_DEVICE,
			fullFilePath.c_str(),
			pTexInfo->imageInfo.Width,
			pTexInfo->imageInfo.Height,
			pTexInfo->imageInfo.MipLevels,
			0,
			pTexInfo->imageInfo.Format,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0,
			nullptr,
			nullptr,
			&pTexInfo->pTexture)))
		{
			std::wstring errMsg = fullFilePath + L"Loading Failed";
			MSG_BOX(L"Error", errMsg.c_str());
			return E_FAIL;
		}
		m_mTexture[objectKey].emplace_back(pTexInfo);
	}

	return S_OK;
}

const TEXTURE_DATA* CTexture::GetTexInfo(const std::wstring & objectKey, const int& index)
{
	auto& iter_Find = m_mTexture.find(objectKey);
	if (m_mTexture.end() == iter_Find)
		return nullptr;

	return iter_Find->second[index];
}

void CTexture::ReleaseTexture()
{
	for (auto& pair : m_mTexture)
	{
		for (auto& texture : pair.second)
		{
			SAFE_DELETE(texture);
		}
		pair.second.clear();
		pair.second.shrink_to_fit();
	}
}
