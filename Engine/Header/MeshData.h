#ifndef MESH_H
#define MESH_H

BEGIN(Engine)
class ENGINE_DLL CMeshData abstract
{
	friend class CMeshStore;
protected:
	explicit					CMeshData			(void);
	virtual					   ~CMeshData			(void);

public:
	virtual		CMeshData*		MakeClone			(void) PURE;
	virtual		void			FreeClone			(void) PURE;

	virtual		void			Awake				(std::wstring const& filePath, 
													 std::wstring const& fileName);
	virtual		void			Start				(void) PURE;
	virtual		void			Update				(void) PURE;

	virtual		void			OnDestory			(void) PURE;

public:
				void			AddTexNameToList	(std::wstring texName);

protected:
	virtual		void			Free				(void) PURE;


protected:
	typedef std::vector<std::wstring> _TEX_LIST;
	GETTOR			(_TEX_LIST,		m_vTexList,			{},				TexList)

	typedef std::list<std::wstring> _ANI_LIST;
	GETTOR			(_ANI_LIST,		m_vAniList,			{},				AniList)

	GETTOR			(std::wstring,	m_meshKey,			L"",			MeshKey)

	GETTOR			(_int,			m_meshType,			UNDEFINED,		MeshType) //Static or Dynamic
	GETTOR			(_float3,		m_meshSize,			ZERO_VECTOR,	MeshSize)

	GETTOR			(_float3,		m_minVertex,		MAX_VECTOR,		MinVertex)
	GETTOR			(_float3,		m_maxVertex,		-MAX_VECTOR,	MaxVertex)

	GETTOR			(_float3,		m_offset,			ZERO_VECTOR,	Offset)

};
END
#endif // !MESH_H
