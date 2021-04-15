#ifndef MESH_H
#define MESH_H

BEGIN(Engine)
class ENGINE_DLL CMesh abstract
{
public:
	explicit				CMesh		(void);
	virtual				   ~CMesh		(void);

public:
	virtual		void		Awake		(void) PURE;
	virtual		void		Start		(void) PURE;
	virtual		void		OnDestory	(void) PURE;

	virtual		void		PreRender	(void) PURE;
	virtual		void		Render		(void) PURE;
	virtual		void		PostRender	(void) PURE;
};
END
#endif // !MESH_H
