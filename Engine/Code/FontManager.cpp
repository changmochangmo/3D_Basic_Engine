#include "EngineStdafx.h"
#include "FontManager.h"
#include "DeviceManager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CFontManager)
void CFontManager::Awake(void)
{
	__super::Awake();
	AddFontResourceEx(L"..\\..\\Resource\\Font\\SohoGothicProMedium.ttf", FR_PRIVATE, 0);
}

void CFontManager::Start(void)
{

	if (FAILED(D3DXCreateFont(GET_DEVICE, -15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"SohoGothicProMedium", &m_pFont)))
	{
		int i = 0;
	}
}

_uint CFontManager::PreRender(void)
{
	return _uint();
}

_uint CFontManager::Render(void)
{
	for (auto& text : m_mTexts)
		DrawMyText(text.second);

	return NO_EVENT;
}

_uint CFontManager::PostRender(void)
{
	return _uint();
}

void CFontManager::OnDestroy(void)
{
	for (auto& text : m_mTexts)
		delete text.second;

	m_mTexts.clear();
}

void CFontManager::AddText(std::wstring textKey, std::wstring msg, D3DXVECTOR3 position, D3DXCOLOR color)
{
	_Text* pNewText = new _Text;

	pNewText->m_message = msg;
	pNewText->m_isVisible = true;
	pNewText->m_position = position;
	pNewText->m_color = color;

	m_mTexts[textKey] = pNewText;
}

void CFontManager::RewriteText(std::wstring textKey, std::wstring msg)
{
	m_mTexts[textKey]->m_message = msg;
}

void CFontManager::DeleteText(std::wstring textKey)
{
	auto& it = m_mTexts.find(textKey);
	delete (*it).second;
	m_mTexts.erase(it);
}

void CFontManager::DrawMyText(_Text* pText)
{
	if (!m_pFont)
		return;

	DWORD format = DT_EXPANDTABS;
	format |= DT_RIGHT;

	std::basic_string<WCHAR> msg = pText->m_message.c_str();

	RECT rect = { int(pText->m_position.x), int(pText->m_position.y), int(pText->m_position.x + 150), int(pText->m_position.y + 150) };
	m_pFont->DrawText(NULL, msg.c_str(), -1, &rect, format, pText->m_color);
}
