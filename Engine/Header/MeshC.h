#ifndef MESHC_H
#define MESHC_H

BEGIN(Engine)

class CMesh;
class ENGINE_DLL CMeshC final : public CComponent
{
public:
	explicit						CMeshC			(void);
								   ~CMeshC			(void);

public:
			SP(CComponent)			MakeClone		(CObject* pObject) override;
			void					Awake			(void) override;
			void					Start			(SP(CComponent) spThis) override;

			void					FixedUpdate		(SP(CComponent) spThis) override;
			void					Update			(SP(CComponent) spThis) override;
			void					LateUpdate		(SP(CComponent) spThis) override;

			void					OnDestroy		(void) override;

			void					OnEnable		(void) override;
			void					OnDisable		(void) override;
public:
			void					ChangeMesh		(std::wstring const& meshKey);

public:
	static const	EComponentID	m_s_componentID = EComponentID::Mesh;

protected:
	GETTOR_SETTOR	(const CMesh*,	m_pMeshData,	nullptr,	MeshData)

	
};
END
#endif // !MESH_H
