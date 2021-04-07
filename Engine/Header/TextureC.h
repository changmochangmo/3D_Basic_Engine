#ifndef TEXTURECOMPONENT_H
#define TEXTURECOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CTextureC final : public CComponent
{
public:
	explicit					CTextureC	(void);
	virtual					   ~CTextureC	(void);

public:
				SP(CComponent)	MakeClone			(CGameObject* pObject) override;

				void			Awake				(void) override;
				void			Start				(SP(CComponent) spSelf) override;

				void			FixedUpdate			(SP(CComponent) spSelf) override;
				void			Update				(SP(CComponent) spThis) override;
				void			LateUpdate			(SP(CComponent) spThis) override;

				void			OnDestroy			(void) override;

				void			OnEnable			(void) override;
				void			OnDisable			(void) override;

public:
	static const	EComponentID	m_s_componentID = EComponentID::Texture;
private:
	GETTOR_SETTOR	(std::wstring,	m_textureKey,	L"",					TextureKey)
	GETTOR_SETTOR	(_TexData*,		m_pTexData,		nullptr,				TexData)
	GETTOR_SETTOR	(_float4,		m_color,		_float4(1, 1, 1, 1),	Color)
	
};
END

#endif // !TEXTURECOMPONENT_H