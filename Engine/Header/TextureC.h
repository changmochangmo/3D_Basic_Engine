#ifndef TEXTURECOMPONENT_H
#define TEXTURECOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CTextureC final : public CComponent
{
public:
	explicit					CTextureC	(void);
	virtual					   ~CTextureC	(void);

public:
				SP(CComponent)	MakeClone			(CObject* pObject) override;

				void			Awake				(void) override;
				void			Start				(SP(CComponent) spSelf) override;

				void			FixedUpdate			(SP(CComponent) spSelf) override;
				void			Update				(SP(CComponent) spThis) override;
				void			LateUpdate			(SP(CComponent) spThis) override;

				void			OnDestroy			(void) override;

				void			OnEnable			(void) override;
				void			OnDisable			(void) override;

public:
				void			AddTexture			(std::wstring const& textureKey);
				void			ChangeTexture		(const _size index, std::wstring const& textureKey);

public:
	static const	EComponentID	m_s_componentID = EComponentID::Texture;
private:
	typedef std::vector<_TexData*> _TEXDATAS;
	GETTOR_SETTOR	(_TEXDATAS,		m_vTexData,		{},						TexData)
	GETTOR_SETTOR	(_float4,		m_color,		_float4(1, 1, 1, 1),	Color)
	GETTOR_SETTOR	(_int,			m_numOfTex,		UNDEFINED,				NumOfTex)	
	
};
END

#endif // !TEXTURECOMPONENT_H
