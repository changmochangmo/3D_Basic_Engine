#include "EngineStdafx.h"
#include "TextManager.h"
#include "DeviceManager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CTextManager)
void CTextManager::Awake(void)
{
	__super::Awake();
	AddFontResourceEx(L"..\\..\\Resource\\Font\\SohoGothicProMedium.ttf", FR_PRIVATE, 0);
}

void CTextManager::Start(void)
{

	if (FAILED(D3DXCreateFont(GET_DEVICE, -15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"SohoGothicProMedium", &m_pFont)))
	{
		int i = 0;
	}
}

void CTextManager::PreRender(void)
{
	GET_DEVICE->Clear(0, nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(255, 125, 125, 125),
		1.f, 0);

	GET_DEVICE->BeginScene();
}

void CTextManager::Render(void)
{
	for (auto& text : m_mTexts)
		DrawMyText(text.second);
}

void CTextManager::PostRender(void)
{
	GET_DEVICE->EndScene();
	GET_DEVICE->Present(NULL, NULL, NULL, NULL);
}

void CTextManager::OnDestroy(void)
{
	for (auto& text : m_mTexts)
		delete text.second;

	m_mTexts.clear();
}

void CTextManager::AddText(std::wstring textKey, std::wstring msg, D3DXVECTOR3 position, D3DXCOLOR color)
{
	_Text* pNewText = new _Text;

	pNewText->m_message = msg;
	pNewText->m_isVisible = true;
	pNewText->m_position = position;
	pNewText->m_color = color;

	m_mTexts[textKey] = pNewText;
}

void CTextManager::RewriteText(std::wstring textKey, std::wstring msg)
{
	m_mTexts[textKey]->m_message = msg;
}

void CTextManager::DeleteText(std::wstring textKey)
{
	auto& it = m_mTexts.find(textKey);
	delete (*it).second;
	m_mTexts.erase(it);
}

void CTextManager::DrawMyText(_Text* pText)
{
	if (!m_pFont)
		return;

	DWORD format = DT_EXPANDTABS;
	format |= DT_RIGHT;

	std::basic_string<WCHAR> msg = pText->m_message.c_str();

	RECT rect = { int(pText->m_position.x), int(pText->m_position.y), int(pText->m_position.x + 150), int(pText->m_position.y + 150) };
	m_pFont->DrawText(NULL, msg.c_str(), -1, &rect, format, pText->m_color);
}
