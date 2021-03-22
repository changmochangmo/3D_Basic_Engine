#ifndef MAINCOMPONENT_H
#define MAINCOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CMainComponent abstract : public CComponent
{
public:
	explicit	CMainComponent	(void);
	virtual	   ~CMainComponent	(void);

public:
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