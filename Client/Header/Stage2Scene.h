#pragma once

#include "Scene.h"
class CStage2Scene final : public Engine::CScene
{
	SMART_DELETER_REGISTER;
private:
	explicit								CStage2Scene(void);
										   ~CStage2Scene(void);

public:
	static			SHARED(Engine::CScene)	Create				(void);

					void					Awake				(void) override;
					void					Start				(void) override;
																   
					_uint					FixedUpdate			(void) override;
					_uint					Update				(void) override;
					_uint					LateUpdate			(void) override;	
					
					void					OnDestroy			(void) override;

					void					OnEnable			(void) override;	 
					void					OnDisable			(void) override;

private:
					void					InitLayers			(void) override;
					void					InitPrototypes		(void) override;

private:
	HRESULT SceneLoad();
	
};

