#ifndef MESH_H
#define MESH_H

BEGIN(Engine)
class ENGINE_DLL CMesh abstract
{
	friend class CMeshStore;
protected:
	explicit					CMesh				(void);
	virtual					   ~CMesh				(void);

public:
	virtual		CMesh*			MakeClone			(void) PURE;
	virtual		void			FreeClone			(void) PURE;

	virtual		void			Awake				(std::wstring const& filePath, 
													 std::wstring const& fileName) PURE;
	virtual		void			Start				(void) PURE;
	virtual		void			Update				(void) PURE;

	virtual		void			OnDestory			(void) PURE;

public:
				void			AddTexNameToList	(std::wstring texName);

protected:
	virtual		void			Free				(void) PURE;


protected:
	typedef std::vector<std::wstring> _TEXLIST;
	GETTOR		(_TEXLIST,		m_vTexList,			{},				TexList)

	GETTOR		(_int,			m_meshType,			UNDEFINED,		MeshType)
	GETTOR		(_float3,		m_minVertex,		MAX_VECTOR,		MinVertex)
	GETTOR		(_float3,		m_maxVertex,		-MAX_VECTOR,	MaxVertex)

	GETTOR		(_float3*,		m_pVertices,		nullptr,		Vertices)
	GETTOR		(_uint,			m_numOfVtx,			0,				NumOfVtx)
	GETTOR		(_uint,			m_stride,			0,				Stride)
};
END
#endif // !MESH_H
