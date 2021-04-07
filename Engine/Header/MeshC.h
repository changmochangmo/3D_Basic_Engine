#ifndef MESH_H
#define MESH_H

BEGIN(Engine)
class ENGINE_DLL CMeshC final : public CComponent
{
public:
	explicit					CMeshC		(void);
							   ~CMeshC		(void);

public:
			SP(CComponent)		MakeClone			(CGameObject* pObject) override;
			void				Awake				(void) override;
			void				Start				(SP(CComponent) spThis) override;

			void				FixedUpdate			(SP(CComponent) spThis) override;
			void				Update				(SP(CComponent) spThis) override;
			void				LateUpdate			(SP(CComponent) spThis) override;

			void				OnDestroy			(void) override;

			void				OnEnable			(void) override;
			void				OnDisable			(void) override;

public:
	static const	EComponentID	m_s_componentID = EComponentID::Mesh;

protected:
	GETTOR_SETTOR	(std::wstring,	m_meshKey,		L"",		MeshKey)
	GETTOR_SETTOR	(SP(_MeshData),	m_pMeshData,	nullptr,	MeshData)

	
};
END
#endif // !MESH_H
