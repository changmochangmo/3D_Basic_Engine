#ifndef DEBUGOBJECT_H
#define DEBUGOBJECT_H

#include "Object.h"

BEGIN(Engine)
class ENGINE_DLL CDebugObject abstract : public CObject
{
	SMART_DELETER_REGISTER
protected:
	explicit									CDebugObject		(void);
											   ~CDebugObject		(void);

public:
	virtual			SP(Engine::CObject)			MakeClone			(void) PURE;
	
	virtual			void						Awake				(void);
	virtual			void						Start				(void);
	
	virtual			void						FixedUpdate			(void);
	virtual			void						Update				(void);
	virtual			void						LateUpdate			(void);
	
	virtual			void						OnDestroy			(void);
	
	virtual			void						OnEnable			(void);
	virtual			void						OnDisable			(void);

public:
	virtual			void						SetBasicName		(void) PURE;

protected:
	GETTOR_SETTOR	(CObject*,					m_pOwner,		nullptr,		Owner)
	GETTOR			(SP(Engine::CMeshC),		m_spMesh,		nullptr,		Mesh)
	GETTOR			(SP(Engine::CGraphicsC),	m_spGraphics,	nullptr,		Graphics)
	GETTOR			(_float3,					m_offset,		ZERO_VECTOR,	Offset)
};
END
#endif