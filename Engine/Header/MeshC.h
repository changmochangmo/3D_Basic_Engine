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

private:
	GETTOR_SETTOR	(CMesh*,		m_pMeshData,		nullptr,		MeshData)
	GETTOR			(_float3,		m_minVertex,		MAX_VECTOR,		MinVertex)
	GETTOR			(_float3,		m_maxVertex,		-MAX_VECTOR,	MaxVertex)
	GETTOR_SETTOR	(_int,			m_renderID,			UNDEFINED,		RenderID)
};
END
#endif // !MESH_H
