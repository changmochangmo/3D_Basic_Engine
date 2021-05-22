#ifndef CREDITSCENE_H
#define CREDITSCENE_H

#include "Scene.h"
class Engine::CObject;
class CCreditScene final : public Engine::CScene
{
private:
	explicit							CCreditScene		(void);
									   ~CCreditScene		(void);

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

	GETTOR			(SP(Engine::CObject),	m_spCredit,		nullptr,	Credit)
};

#endif

