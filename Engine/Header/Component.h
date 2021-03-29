#ifndef COMPONENT_H
#define COMPONENT_H

BEGIN(Engine)
class CGameObject;
class ENGINE_DLL CComponent abstract  
{
public:
	explicit	CComponent		(void);
	virtual	   ~CComponent		(void);

public:
	virtual		SHARED(CComponent)	MakeClone	(CGameObject* pObject)			PURE;

	virtual		void				Awake		(void)							PURE;
	virtual		void				Start		(SHARED(CComponent) spThis)		PURE;

	virtual		_uint				FixedUpdate	(SHARED(CComponent) spThis)		PURE;
	virtual		_uint				Update		(SHARED(CComponent) spThis)		PURE;
	virtual		_uint				LateUpdate	(SHARED(CComponent) spThis)		PURE;

	virtual		void				OnDestroy	(void)							PURE;
	
	virtual		void				OnEnable	(void)							PURE;
	virtual		void				OnDisable	(void)							PURE;

protected:
	GETTOR_SETTOR	(CGameObject*,	m_pOwner,		nullptr,					Owner)
	
	
	GETTOR_SETTOR	(_bool,			m_isAwaked,		false,						IsAwaked)
	GETTOR_SETTOR	(_bool,			m_isStarted,	false,						IsStarted)
	GETTOR_SETTOR	(_bool,			m_isEnabled,	true,						IsEnabled)

	GETTOR_SETTOR	(_int,			m_dataID,		(_int)EDataID::Component,	DataID)
	GETTOR_SETTOR	(std::wstring,  m_name,			L"",						Name)

	GETTOR			(_int,			m_componentID,	-1,							ComponentID)
};
END

#endif // !COMPONENT_H