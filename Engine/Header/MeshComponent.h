#ifndef MESH_H
#define MESH_H

BEGIN(Engine)
class ENGINE_DLL CMeshComponent final : public CSubComponent
{
public:
	explicit					CMeshComponent		(void);
							   ~CMeshComponent		(void);

public:
			SHARED(CComponent)	MakeClone			(CGameObject* pObject) override;
			void				Awake				(void) override;
			void				Start				(SHARED(CComponent) spThis) override;

			_uint				FixedUpdate			(SHARED(CComponent) spThis) override;
			_uint				Update				(SHARED(CComponent) spThis) override;
			_uint				LateUpdate			(SHARED(CComponent) spThis) override;

			void				OnDestroy			(void) override;

			void				OnEnable			(void) override;
			void				OnDisable			(void) override;

public:
	static const	EComponentID		m_s_componentID = EComponentID::Mesh;

protected:
	GETTOR_SETTOR	(std::wstring,		m_meshKey,		L"",		MeshKey)
	GETTOR_SETTOR	(SHARED(_MeshData),	m_pMeshData,	nullptr,	MeshData)

	
};
END
#endif // !MESH_H
