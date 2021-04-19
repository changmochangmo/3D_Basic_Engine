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
	virtual		CMesh*	MakeClone		(void) PURE;
	virtual		void	FreeClone		(void) PURE;

	virtual		void	Awake			(std::wstring const& filePath, 
										 std::wstring const& fileName) PURE;
	virtual		void	Start			(void) PURE;
	virtual		void	Update			(void) PURE;

	virtual		void	OnDestory		(void) PURE;

protected:
	virtual		void	Free			(void) PURE;

	GETTOR		(_int,	m_meshType,		UNDEFINED,	MeshType)
};
END
#endif // !MESH_H
