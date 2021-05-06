#ifndef BASICOBJECT_H
#define BASICOBJECT_H

#include "Object.h"

BEGIN(Engine)
class ENGINE_DLL CEmptyObject final : public CObject
{
	SMART_DELETER_REGISTER
private:
	explicit	CEmptyObject		(void);
			   ~CEmptyObject		(void);

public:
	static		SP(CEmptyObject)			Create			(_bool isStatic);

				SP(Engine::CObject)			MakeClone		(void) override;
		
				void						Awake			(void) override;
				void						Start			(void) override;
		
				void						FixedUpdate		(void) override;
				void						Update			(void) override;
				void						LateUpdate		(void) override;
		
				void						OnDestroy		(void) override;
		
				void						OnEnable		(void) override;
				void						OnDisable		(void) override;

public:
				void						SetBasicName	(void)  override;


private:
	static		_uint						m_s_uniqueID;
};
END

#endif