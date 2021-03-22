#pragma once

#include "Scene.h"
class CStage1Scene final : public Engine::CScene
{
	SMART_DELETER_REGISTER;
private:
	explicit								CStage1Scene(void);
										   ~CStage1Scene(void);

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

private:
	_float3 m_PreRotation;
	_float m_FowardVal;
	_float m_Rot;
	_float m_EventTimer;
	_int   m_EventCount;

	SHARED(Engine::CGameObject) m_pPlayer;

private:
	void CameraEvent();

	
};

