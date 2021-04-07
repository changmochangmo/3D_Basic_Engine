#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class CCameraC;
class ENGINE_DLL CCameraManager final : public CEngine
{
	DECLARE_SINGLETON(CCameraManager)

public:
			void					Awake				(void) override;
			void					Start				(void);

			void					Update				(void);
			void					LateUpdate			(void);	

			void					OnDestroy			(void);

			void					OnEnable			(void);
			void					OnDisable			(void);

			SP(CCameraC)			AddCamera			(const std::wstring& cameraKey, SP(CCameraC) spCamera);
			SP(CCameraC)			GetCamera			(const std::wstring& cameraKey);
			void					DeleteCamera		(const std::wstring& cameraKey);
			void					ChangeCameraKey		(const std::wstring& cameraKey, 
														 const std::wstring& newKey);

private:
			void					SetMainCameraMode	(void);

private:
	std::unordered_map<std::wstring, SP(CCameraC)> m_mCameras;

	GETTOR_SETTOR	(SP(CCameraC),	m_spMainCamera,	nullptr,	MainCamera)
	GETTOR_SETTOR	(_bool,			m_updateProj,	false,		UpdateProj)
};
END
#endif