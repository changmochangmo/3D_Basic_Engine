#ifndef COLGRAPHICS_H
#define COLGRAPHICS_H

#include "DebugObject.h"

BEGIN(Engine)
class CCollider;
class ENGINE_DLL CDebugCollider final : public CDebugObject
{
SMART_DELETER_REGISTER
protected:
	explicit								CDebugCollider		(void);
										   ~CDebugCollider		(void);

public:
	static			SP(CDebugCollider)		Create				(_bool isStatic);
					SP(Engine::CObject)		MakeClone			(void) override;
		
					void					Awake				(void) override;
					void					Start				(void) override;
		
					void					FixedUpdate			(void) override;
					void					Update				(void) override;
					void					LateUpdate			(void) override;
		
					void					OnDestroy			(void) override;
		
					void					OnEnable			(void) override;
					void					OnDisable			(void) override;

public:
					void					SetBasicName		(void) override;
private:
	static			_uint					m_s_uniqueID;

	GETTOR_SETTOR	(CCollider*,			m_pCollider,		nullptr,	Collider)
};
END
#endif
