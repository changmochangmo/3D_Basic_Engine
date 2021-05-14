#ifndef BOSSSCENE_H
#define BOSSSCENE_H

#include "Scene.h"

class CBossScene final : public Engine::CScene
{
private:
	explicit							CBossScene			(void);
									   ~CBossScene			(void);

public:
	static			Engine::CScene*		Create				(void);
					void				Free				(void) override;

					void				Awake				(_int numOfLayers) override;
					void				Start				(void) override;
															   
					void				FixedUpdate			(void) override;
					void				Update				(void) override;
					void				LateUpdate			(void) override;	
					
					void				OnDestroy			(void) override;

					void				OnEnable			(void) override;	 
					void				OnDisable			(void) override;

private:
					void				InitPrototypes		(void) override;
};

#endif