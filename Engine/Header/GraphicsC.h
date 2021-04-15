#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CGraphicsC final : public CComponent
{
public:
	explicit	CGraphicsC	(void);
			   ~CGraphicsC	(void);
public:
					SP(CComponent)	MakeClone		(CObject* pObject)	override;

					void				Awake			(void) override;
					void				Start			(SP(CComponent) spThis) override;

					void				FixedUpdate		(SP(CComponent) spThis) override;
					void				Update			(SP(CComponent) spThis) override;
					void				LateUpdate		(SP(CComponent) spThis) override;
					
					void				PreRender		(void);
					void				Render			(void);
					void				PostRender		(void);	

					void				OnDestroy		(void) override;

					void				OnDisable		(void) override;
					void				OnEnable		(void) override;

public:
	static const	EComponentID	m_s_componentID = EComponentID::Graphics;

protected:

	GETTOR			(SP(CMeshC),		m_pMesh,		nullptr,			Mesh)
	GETTOR			(SP(CTextureC),		m_pTexture,		nullptr,			Texture)
	GETTOR			(SP(CTransformC),	m_pTransform,	nullptr,			Transform)
	//GETTOR			(SP(CBitmapComponent),		m_pBitmap,		nullptr,			Bitmap)
	GETTOR_SETTOR	(_int,				m_renderID,		UNDEFINED,			RenderID)
};
END
#endif // !GRAPHICSCOMPONENT_H
