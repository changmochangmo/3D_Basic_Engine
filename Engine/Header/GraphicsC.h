#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CGraphicsC final : public CComponent
{
public:
	explicit	CGraphicsC	(void);
			   ~CGraphicsC	(void);
public:
					SP(CComponent)		MakeClone		(CObject* pObject)	override;

					void				Awake			(void) override;
					void				Start			(SP(CComponent) spThis) override;

					void				FixedUpdate		(SP(CComponent) spThis) override;
					void				Update			(SP(CComponent) spThis) override;
					void				LateUpdate		(SP(CComponent) spThis) override;

					void				OnDestroy		(void) override;

					void				OnDisable		(void) override;
					void				OnEnable		(void) override;

public:
	static const	EComponentID	m_s_componentID = EComponentID::Graphics;

	D3DMATERIAL9 m_mtrl;
private:
					void				GenerateBV		(void);

private:
	GETTOR			(SP(CMeshC),		m_spMesh,		nullptr,		Mesh)
	GETTOR			(SP(CTextureC),		m_spTexture,	nullptr,		Texture)
	GETTOR			(SP(CTransformC),	m_spTransform,	nullptr,		Transform)
	GETTOR			(SP(CBitmapC),		m_spBitmap,		nullptr,		Bitmap)

	GETTOR			(_float3,			m_offsetBV,		ZERO_VECTOR,	OffsetBV)
	GETTOR			(_float3,			m_sizeBV,		ONE_VECTOR,		SizeBV)
	GETTOR_SETTOR	(_int,				m_renderID,		UNDEFINED,		RenderID)



};
END
#endif // !GRAPHICSCOMPONENT_H
