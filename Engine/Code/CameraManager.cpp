#include "EngineStdafx.h"
#include "CameraManager.h"
#include "CameraC.h"
#include "ObjectFactory.h"
#include "Object.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "WndApp.h"

USING(Engine)
IMPLEMENT_SINGLETON(CCameraManager)

void CCameraManager::Awake(void)
{
	__super::Awake();
}

void CCameraManager::Start(_int collisionID)
{
	m_camColliderID = collisionID;
	//if (m_spMainCamera == nullptr)
	//{
	//	SP(CObject) spCameraObject = ADD_CLONE(L"Camera", true, L"BasicCamera", (_int)ELayerID::Camera);
	//	m_spMainCamera = spCameraObject->GetComponent<CCameraC>();
	//
	//	AddCamera(L"FreeCamera", m_spMainCamera);
	//	m_spMainCamera->SetTarget(GET_CUR_SCENE->FindObjectWithKey(L"Player"));
	//}
}

void CCameraManager::Update(void)
{	
	SetMainCameraMode();
}

void CCameraManager::LateUpdate(void)
{
	for (auto& iter = m_mCameras.begin(); iter != m_mCameras.end();)
	{
		if (iter->second->GetOwner() == nullptr)
		{
			iter->second.reset();
			iter = m_mCameras.erase(iter);
		}
		else
			++iter;
	}
}

void CCameraManager::OnDestroy(void)
{
	for (auto& camera : m_mCameras)
	{
		camera.second.reset();
	}

	m_mCameras.clear();
}

void CCameraManager::OnEnable(void)
{
}

void CCameraManager::OnDisable(void)
{
}

SP(CCameraC) CCameraManager::AddCamera(const std::wstring & cameraKey, SP(CCameraC) spCamera)
{
	m_mCameras.emplace(cameraKey, spCamera);

	return spCamera;
}

SP(CCameraC) CCameraManager::GetCamera(const std::wstring & cameraKey)
{
	return m_mCameras[cameraKey];
}

void CCameraManager::DeleteCamera(const std::wstring & cameraKey)
{
	auto& it = m_mCameras.find(cameraKey);
	it->second.reset();
	m_mCameras.erase(it);
}

void CCameraManager::ChangeCameraKey(const std::wstring & cameraKey, const std::wstring & newKey)
{
	AddCamera(newKey, m_mCameras[cameraKey]);
	m_mCameras.erase(cameraKey);
}

void CCameraManager::DeleteMainCam(void)
{
	m_mCameras.clear();
	m_spMainCamera.reset();
}

void CCameraManager::SetMainCameraMode(void)
{
	if (IMKEY_DOWN(KEY_F1))
	{
		m_spMainCamera->SetMode(ECameraMode::Fixed);
		m_spMainCamera->GetTransform()->SetPosition(-7.75f, 0.67f, 56.1f);
		m_spMainCamera->GetTransform()->SetRotation(0, 0, 0);
		m_spMainCamera->SetMoveable(false);
		m_spMainCamera->SetRotatable(false);
		ShowCursor(true);
	}
	else if (IMKEY_DOWN(KEY_F2))
	{
		m_spMainCamera->SetMode(ECameraMode::Edit);
		m_spMainCamera->SetMoveable(true);
		m_spMainCamera->SetRotatable(false);
		ShowCursor(true);
	}
	else if (IMKEY_DOWN(KEY_F3))
	{
		m_spMainCamera->SetMode(ECameraMode::FPS);
		m_spMainCamera->SetMoveable(true);
		m_spMainCamera->SetRotatable(false);
		ShowCursor(false);
	}
	else if (IMKEY_DOWN(KEY_F4))
	{
		m_spMainCamera->SetMode(ECameraMode::Follower);
		m_spMainCamera->SetMoveable(false);
		m_spMainCamera->SetRotatable(false);
		ShowCursor(false);
	}
}
