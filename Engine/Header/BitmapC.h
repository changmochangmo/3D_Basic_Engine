//#ifndef BITMAPCOMPONENT_H
//#define BITMAPCOMPONENT_H
//
//BEGIN(Engine)
//class ENGINE_DLL CBitmapComponent final : public CComponent
//{
//public:
//	explicit					CBitmapComponent	(void);
//							   ~CBitmapComponent	(void);
//
//public:
//			SP(CComponent)	MakeClone			(CGameObject* pObject) override;
//			void				Awake				(void) override;
//			void				Start				(SP(CComponent) spThis) override;
//
//			_uint				FixedUpdate			(SP(CComponent) spThis) override;
//			_uint				Update				(SP(CComponent) spThis) override;
//			_uint				LateUpdate			(SP(CComponent) spThis) override;
//
//			void				OnDestroy			(void) override;
//
//			void				OnEnable			(void) override;
//			void				OnDisable			(void) override;
//
//	static LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer (void);
//	static LPDIRECT3DINDEXBUFFER9 GetIndexBuffer (void);
//private:
//	static	void				InitVertexBuffer	(void);
//	static	void				InitIndexBuffer		(void);
//
//public:
//	static const	EComponentID		m_s_componentID = EComponentID::Bitmap;
//
//protected:
//	static LPDIRECT3DVERTEXBUFFER9 m_s_pVertexBuffer;
//	static LPDIRECT3DINDEXBUFFER9 m_s_pIndexBuffer;
//};
//END
//
//#endif
