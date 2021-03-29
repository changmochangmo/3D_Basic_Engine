#include "EngineStdafx.h"
#include "CameraManager.h"
#include "Camera.h"

USING(Engine)
IMPLEMENT_SINGLETON(CCameraManager)

void CCameraManager::Awake(void)
{
	__super::Awake();

	m_pMainCamera = AddCamera(L"Free", CCamera::Create());
}

void CCameraManager::Start(void)
{
}

void CCameraManager::Update(void)
{
	for (auto& camera : m_mCameras)
	{
		if(camera.second->GetEnable())
			camera.second->Update();
	}
}

void CCameraManager::LateUpdate(void)
{
	for (auto& it = m_mCameras.begin(); it != m_mCameras.end();)
	{
		if (it->second->GetDeleteThis())
		{
			it->second->Free();
			it = m_mCameras.erase(it);
		}
		else
		{
			if (it->second->GetEnable())
				it->second->LateUpdate();

			++it;
		}
	}
}

void CCameraManager::OnDestroy(void)
{
	for (auto& camera : m_mCameras)
	{
		camera.second->Free();
	}

	m_mCameras.clear();
}

void CCameraManager::OnEnable(void)
{
}

void CCameraManager::OnDisable(void)
{
}

CCamera* CCameraManager::AddCamera(const std::wstring & cameraKey, CCamera * pCamera)
{
	m_mCameras.emplace(cameraKey, pCamera);

	return pCamera;
}

CCamera * CCameraManager::GetCamera(const std::wstring & cameraKey)
{
	return m_mCameras[cameraKey];
}

void CCameraManager::DeleteCamera(const std::wstring & cameraKey)
{
	auto& it = m_mCameras.find(cameraKey);
	it->second->Free();
	m_mCameras.erase(it);
}

void CCameraManager::ChangeCameraKey(const std::wstring & cameraKey, const std::wstring & newKey)
{
	AddCamera(newKey, m_mCameras[cameraKey]);
	m_mCameras.erase(cameraKey);
}
