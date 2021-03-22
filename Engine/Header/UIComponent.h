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

	GETTOR_SETTOR(_uint, m_sortingLayer, 0, SortingLayer) // UI�� �׷����� ���� (���ڰ� �������� �����׷���)

	GETTOR_SETTOR(std::wstring, m_textureKey, L"", TextureKey) // �̹����� �ҷ��� Ű��
	GETTOR_SETTOR(SHARED(_TexData), m_pTexData, nullptr, TexData) // �̹����� ������ ����

	SHARED(_MeshData) m_meshDate; // ���ؽ� ,�ε��� ���۸������ϱ� ���� ����
};
END

#endif // !TEXTURECOMPONENT_H
