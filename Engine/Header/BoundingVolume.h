#ifndef BOUNDINGVOLUME_H
#define BOUNDINGVOLUME_H

#include "DebugObject.h"

BEGIN(Engine)
class ENGINE_DLL CBoundingVolume final : public CDebugObject
{
	SMART_DELETER_REGISTER
protected:
	explicit							CBoundingVolume		(void);
									   ~CBoundingVolume		(void);

public:
	static		SP(CBoundingVolume)		Create				(_bool isStatic);
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
	static		_uint					m_s_uniqueID;
};
END
#endif