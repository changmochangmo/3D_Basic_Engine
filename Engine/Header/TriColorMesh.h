#ifndef TRICOLORMESH_H
#define TRICOLORMESH_H

#include "Mesh.h"

BEGIN(Engine)
class ENGINE_DLL CTriColorMesh : public CMesh
{
public:
	virtual			void			InitPrototype		(void)			PURE;
	virtual			void			InitClone			(void* pArg)	PURE;
	virtual			CComponent*		MakeClone			(void* pArg)	PURE;
	virtual			void			Free				(void)			override;

	static			CTriColorMesh*	Create				(void);
public:
	CTriColorMesh();
	virtual ~CTriColorMesh();
};
END
#endif // !TRICOLORMESH_H
