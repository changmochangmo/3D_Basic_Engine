#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CTextManager final : public CEngine
{
	DECLARE_SINGLETON(CTextManager)
public:
	void		Awake			(void) override;
	void		Start			(void);

	void		PreRender		(void);
	void		Render			(void);
	void		PostRender		(void);

	void		OnDestroy		(void);

	void		AddText			(std::wstring textKey, std::wstring msg, 
								 D3DXVECTOR3 position, D3DXCOLOR color);
	void		RewriteText		(std::wstring textKey, std::wstring msg);
	void		DeleteText		(std::wstring textKey);

private:
	void		DrawMyText		(_Text* pText);
private:
	typedef std::unordered_map<std::wstring, _Text*> _TEXTS;

	_TEXTS		m_mTexts;
	LPD3DXFONT	m_pFont;

};
END
#endif	