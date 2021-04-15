#ifndef BASICOBJECT_H
#define BASICOBJECT_H

#include "Object.h"

class CBasicObject final : public Engine::CObject
{
	SMART_DELETER_REGISTER
private:
	explicit	CBasicObject		(void);
			   ~CBasicObject		(void);

public:
	static		SP(CBasicObject)			Create			(_bool isStatic);

				SP(Engine::CObject)		MakeClone		(void) override;
		
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
	GETTOR		(SP(Engine::CTransformC),	m_spTransform,	nullptr,	Transform)
};

#endif