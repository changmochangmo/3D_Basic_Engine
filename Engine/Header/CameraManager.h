#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class CCamera;
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

			CCamera*				AddCamera			(const std::wstring& cameraKey, CCamera* pCamera);
			CCamera*				GetCamera			(const std::wstring& cameraKey);
			void					DeleteCamera		(const std::wstring& cameraKey);
			void					ChangeCameraKey		(const std::wstring& cameraKey, 
														 const std::wstring& newKey);

private:
	std::unordered_map<std::wstring, CCamera*> m_mCameras;

	GETTOR_SETTOR	(CCamera*,		m_pMainCamera,	nullptr,	MainCamera)
};
END
#endif