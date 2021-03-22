#ifndef TEXTURECOMPONENT_H
#define TEXTURECOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CTextureComponent final : public CSubComponent
{
public:
	explicit						CTextureComponent	(void);
	virtual						   ~CTextureComponent	(void);

public:
				SHARED(CComponent)	MakeClone			(CGameObject* pObject) override;

				void				Awake				(void) override;
				void				Start				(SHARED(CComponent) spSelf) override;

				_uint				FixedUpdate			(SHARED(CComponent) spSelf) override;
				_uint				Update				(SHARED(CComponent) spThis) override;
				_uint				LateUpdate			(SHARED(CComponent) spThis) override;

				void				OnDestroy			(void) override;

				void				OnEnable			(void) override;
				void				OnDisable			(void) override;

public:
	static const	EComponentID		m_s_componentID = EComponentID::Texture;
private:
	GETTOR_SETTOR	(std::wstring,		m_textureKey,	L"",		TextureKey)
	GETTOR_SETTOR	(SHARED(_TexData),	m_pTexData,		nullptr,	TexData)
	GETTOR_SETTOR	(D3DXVECTOR4,		m_color,		D3DXVECTOR4(1.f, 1.f, 1.f, 1.f), Color)
	
};
END

#endif // !TEXTURECOMPONENT_H
