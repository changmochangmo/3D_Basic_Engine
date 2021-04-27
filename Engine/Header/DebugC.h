#ifndef DEBUGC_H
#define DEBUGC_H

BEGIN(Engine)
class CMesh;
class ENGINE_DLL CDebugC final : public CComponent
{
public:
	explicit							CDebugC	(void);
									   ~CDebugC	(void);

//Override functions									   
public:
					SP(CComponent)		MakeClone			(CObject* pObject) override;

					void				Awake				(void) override;
					void				Start				(SP(CComponent) spThis) override;

					void				FixedUpdate			(SP(CComponent) spThis) override;
					void				Update				(SP(CComponent) spThis) override;
					void				LateUpdate			(SP(CComponent) spThis) override;

					void				OnDestroy			(void) override;

					void				OnEnable			(void) override;
					void				OnDisable			(void) override;

public:
					void				ChangeMesh			(std::wstring const& meshKey);
private:
					void				SetupBV				(void);
					
public:
	static const	EComponentID		m_s_componentID = EComponentID::Debug;

private:
	typedef std::vector<CMesh*> _MESHES;
	
	GETTOR			(_MESHES,			m_vMeshDatas,		{},				MeshDatas)
	GETTOR			(_int,				m_debugType,		UNDEFINED,		DebugType)

	GETTOR			(SP(CTransformC),	m_spTransform,		nullptr,		Transform)
	GETTOR			(SP(CMeshC),		m_spMesh,			nullptr,		Mesh)

	GETTOR			(_float3,			m_offset,			ZERO_VECTOR,	Offset)
	GETTOR			(_float3,			m_size,				ZERO_VECTOR,	Size)
	GETTOR			(_int,				m_renderID,			UNDEFINED,		RenderID)
};
END
#endif