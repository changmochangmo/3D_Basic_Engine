#ifndef MESH_H
#define MESH_H

BEGIN(Engine)
class ENGINE_DLL CMesh abstract
{
	friend class CMeshStore;
protected:
	explicit			CMesh			(void);
	virtual			   ~CMesh			(void);

public:
	virtual		void	Awake			(void) PURE;
	virtual		void	Start			(void) PURE;
	virtual		void	OnDestory		(void) PURE;

	GETTOR		(_int,	m_meshType,		UNDEFINED,	MeshType)
};
END
#endif // !MESH_H
