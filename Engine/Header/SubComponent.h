#ifndef SUBCOMPONENT_H
#define SUBCOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CSubComponent abstract : public CComponent
{
public:
	explicit	CSubComponent	(void);
	virtual	   ~CSubComponent	(void);

public:
	// CComponent을(를) 통해 상속됨
	virtual		SHARED(CComponent)	MakeClone		(CGameObject * pObject) PURE;

	virtual		void				Awake			(void) PURE;
	virtual		void				Start			(SHARED(CComponent) spThis) PURE;

	virtual		_uint				FixedUpdate		(SHARED(CComponent) spThis) PURE;
	virtual		_uint				Update			(SHARED(CComponent) spThis) PURE;
	virtual		_uint				LateUpdate		(SHARED(CComponent) spThis) PURE;

	virtual		void				OnDestroy		(void) PURE;
	virtual		void				OnEnable		(void) PURE;
	virtual		void				OnDisable		(void) PURE;
};
END
#endif