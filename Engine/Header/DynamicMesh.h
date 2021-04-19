#ifndef DYNAMICMESH_H
#define DYNAMICMESH_H

#include "Mesh.h"
#include "HierarchyLoader.h"
#include "AniCtrl.h"

BEGIN(Engine)
class ENGINE_DLL CDynamicMesh final : public CMesh
{
	friend class CMeshStore;
private:
	explicit						CDynamicMesh			(void);
	virtual						   ~CDynamicMesh			(void);

public:
				CMesh*				MakeClone				(void) override;
				void				FreeClone				(void) override;

				void				Awake					(std::wstring const& filePath, 
															 std::wstring const& fileName) override;
				void				Start					(void) override;
				void				Update					(void) override;

				void				OnDestory				(void) override;

private:
	static		CDynamicMesh*		Create					(std::wstring const& filePath, 
															 std::wstring const& fileName);
				void				Free					(void) override;

//interface
public:
				void				UpdateFrame				(void);
				void				ChangeAniSet			(_uint index);
				void				ChangeAniSet			(std::string name);
				void				PlayAnimation			(void);

				_DerivedD3DXFRAME*	GetFrameByName			(std::string name);
				_bool				IsAnimationEnd			(void);

private:
				void				UpdateFrameMatrices		(_DerivedD3DXFRAME* pFrame, _mat* pParentMat);
				void				SetFrameMatPointer		(_DerivedD3DXFRAME* pFrame);
				_uint				FindFirstAniIndex		(std::wstring const& fileName);

private:
	typedef std::vector<_DerivedD3DXMESHCONTAINER*> _MESHCONTAINERS;
	GETTOR		(_MESHCONTAINERS,		m_vMeshContainers,		{},			MeshContainers)
	GETTOR		(D3DXFRAME*,			m_pRootFrame,			nullptr,	RootFrame)
	GETTOR		(CHierarchyLoader*,		m_pHierarchyLoader,		nullptr,	HierarchyLoader)
	GETTOR		(CAniCtrl*,				m_pAniCtrl,				nullptr,	AniCtrl)
};
END
#endif