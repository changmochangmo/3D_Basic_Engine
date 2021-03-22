#ifndef UICOMPONENT_H
#define UICOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CUIComponent final : public CSubComponent
{
public:
	explicit						CUIComponent	(void);
	virtual						   ~CUIComponent	(void);

public:
				SHARED(CComponent)	MakeClone			(CGameObject* pObject) override;

				void				Awake				(void) override;
				void				Start				(SHARED(CComponent) spSelf) override;

				_uint				FixedUpdate			(SHARED(CComponent) spSelf) override;
				_uint				Update				(SHARED(CComponent) spThis) override;
				_uint				LateUpdate			(SHARED(CComponent) spThis) override;

				_uint				PreRender(void);
				_uint				Render(void);
				_uint				PostRender(void);

				void				OnDestroy			(void) override;

				void				OnEnable			(void) override;
				void				OnDisable			(void) override;

private:
	void DateInit();
public:
	static const	EComponentID		m_s_componentID = EComponentID::UI;
private:
	GETTOR(SHARED(CTransformComponent), m_pTransform, nullptr, Transform)

	GETTOR_SETTOR(_uint, m_sortingLayer, 0, SortingLayer) // UI의 그려지는 순서 (숫자가 작을수록 빨리그려짐)

	GETTOR_SETTOR(std::wstring, m_textureKey, L"", TextureKey) // 이미지를 불러올 키값
	GETTOR_SETTOR(SHARED(_TexData), m_pTexData, nullptr, TexData) // 이미지를 저장할 변수

	SHARED(_MeshData) m_meshDate; // 버텍스 ,인덱스 버퍼를저장하기 위한 변수
};
END

#endif // !TEXTURECOMPONENT_H
