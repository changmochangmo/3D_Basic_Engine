#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include "Scene.h"

class CMainMenuScene final : public Engine::CScene
{
	SMART_DELETER_REGISTER;
private:
	explicit								CMainMenuScene		(void);
										   ~CMainMenuScene		(void);
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

protected:
	virtual			void					InitLayers			(void) override;
	virtual			void					InitPrototypes		(void) override;
};


#endif // !MAINMENUSCENE_H