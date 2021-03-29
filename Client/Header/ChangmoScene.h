#pragma once

#include "Scene.h"
class CChangmoScene final : public Engine::CScene
{
	SMART_DELETER_REGISTER;
private:
	explicit							CChangmoScene		(void);
									   ~CChangmoScene		(void);

public:
	static			Engine::CScene*		Create				(void);
					void				Free				(void) override;

					void				Awake				(_int numOfLayers) override;
					void				Start				(void) override;
															   
					_uint				FixedUpdate			(void) override;
					_uint				Update				(void) override;
					_uint				LateUpdate			(void) override;	
					
					void				OnDestroy			(void) override;

					void				OnEnable			(void) override;	 
					void				OnDisable			(void) override;

private:
					void				InitPrototypes		(void) override;
};

