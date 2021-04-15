#ifndef STATICMESH_H
#define STATICMESH_H

#include "Mesh.h"

BEGIN(Engine)
class ENGINE_DLL CStaticMesh final : public CMesh
{
	friend class CMeshStore;
public:
	explicit				CStaticMesh		(void);
	virtual				   ~CStaticMesh		(void);

public:
				void		Awake			(void) override;
				void		Start			(void) override;
				void		OnDestory		(void) override;

				void		PreRender		(void) override;
				void		Render			(void) override;
				void		PostRender		(void) override;

private:

public:
private:
	LPD3DXMESH				m_pMesh			= nullptr;
	LPD3DXBUFFER			m_pAdjacency	= nullptr;
	LPD3DXBUFFER			m_pSubset		= nullptr;	// 서브셋의 개수 == 재질의 개수 == 텍스처의 개수
	LPD3DXMATERIAL			m_pMtrl			= nullptr;
	_ulong					m_subsetCount	= 0;
};
END

#endif