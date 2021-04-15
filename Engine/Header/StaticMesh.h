#ifndef STATICMESH_H
#define STATICMESH_H

#include "Mesh.h"

BEGIN(Engine)
class ENGINE_DLL CStaticMesh final : public CMesh
{
	friend class CMeshStore;
private:
	explicit				CStaticMesh		(void);
	virtual				   ~CStaticMesh		(void);

public:
				void		Awake			(void) override;
				void		Start			(void) override;
				void		OnDestory		(void) override;

private:

public:
private:
	GETTOR		(LPD3DXMESH,		m_pMesh,		nullptr,	Mesh)
	GETTOR		(LPD3DXBUFFER,		m_pAdjacency,	nullptr,	Adjacency)
	GETTOR		(LPD3DXBUFFER,		m_pSubset,		nullptr,	Subset)	// 서브셋의 개수 == 재질의 개수 == 텍스처의 개수
	GETTOR		(LPD3DXMATERIAL,	m_pMtrl,		nullptr,	Mtrl)
	GETTOR		(_ulong,			m_subsetCount,	0,			SubsetCount)
};
END

#endif