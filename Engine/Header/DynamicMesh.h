#ifndef DYNAMICMESH_H
#define DYNAMICMESH_H

#include "MeshData.h"
#include "HierarchyLoader.h"
#include "AniCtrl.h"

BEGIN(Engine)
class ENGINE_DLL CDynamicMesh final : public CMeshData
{
	friend class CMeshStore;
private:
	explicit						CDynamicMesh			(void);
	virtual						   ~CDynamicMesh			(void);

public:
				CMeshData*			MakeClone				(void) override;
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
				void				ChangeAniSet			(_uint index, 
															 _bool fixTillEnd = false,
															 _double smoothTime = 0.25,
															 _float changeWeight = 0.9f);
				void				ChangeAniSet			(std::string name,
															 _bool fixTillEnd = false,
															 _double smoothTime = 0.25,
															 _float changeWeight = 0.9f);
				void				PlayAnimation			(void);

				_DerivedD3DXFRAME*	GetFrameByName			(std::string name);
				_bool				IsAnimationEnd			(void);
				void				SetAniFixTillEnd		(_bool isItFixed);

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
	GETTOR_SETTOR(_bool,				m_playAnimation,		true,		PlayAnimation)
};
END
#endif