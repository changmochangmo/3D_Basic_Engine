#ifndef BASICOBJECT_H
#define BASICOBJECT_H

#include "GameObject.h"

class CBasicObject final : public Engine::CGameObject
{
	SMART_DELETER_REGISTER
private:
	explicit			CBasicObject		(void);
					   ~CBasicObject		(void);

public:
	static			SP(CBasicObject)			Create				(void);

					SP(Engine::CGameObject)		MakeClone			(void) override;
		
					void						Awake				(void) override;
					void						Start				(void) override;
		
					void						FixedUpdate			(void) override;
					void						Update				(void) override;
					void						LateUpdate			(void) override;
		
					void						OnDestroy			(void) override;
		
					void						OnEnable			(void) override;
					void						OnDisable			(void) override;

public:
					void						SetBasicName		(void)  override;


private:
	static			_uint						m_s_uniqueID;
					SP(Engine::CTransformC)		m_spTransform;
};

#endif