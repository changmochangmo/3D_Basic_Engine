#ifndef LOGOSCENE_H
#define LOGOSCENE_H

#include "Scene.h"

class CLogoScene final : public Engine::CScene
{
	SMART_DELETER_REGISTER;
private:
	explicit								CLogoScene			(void);
										   ~CLogoScene			(void);

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

#endif // !LOGOSCENE_H