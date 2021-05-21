#ifndef BITMAPCOMPONENT_H
#define BITMAPCOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CBitmapC final : public CComponent
{
public:
	explicit						CBitmapC			(void);
								   ~CBitmapC			(void);

public:
			SP(CComponent)			MakeClone			(CObject* pObject) override;
			void					Awake				(void) override;
			void					Start				(SP(CComponent) spThis) override;

			void					FixedUpdate			(SP(CComponent) spThis) override;
			void					Update				(SP(CComponent) spThis) override;
			void					LateUpdate			(SP(CComponent) spThis) override;

			void					OnDestroy			(void) override;

			void					OnEnable			(void) override;
			void					OnDisable			(void) override;

	static LPDIRECT3DVERTEXBUFFER9	GetVertexBuffer		(void);
	static LPDIRECT3DINDEXBUFFER9	GetIndexBuffer		(void);
private:
	static	void					InitVertexBuffer	(void);
	static	void					InitIndexBuffer		(void);

public:
	static const	EComponentID	m_s_componentID = EComponentID::Bitmap;

protected:
	static LPDIRECT3DVERTEXBUFFER9	m_s_pVertexBuffer;
	static LPDIRECT3DINDEXBUFFER9	m_s_pIndexBuffer;
};
END

#endif
