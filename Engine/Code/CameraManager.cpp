#include "EngineStdafx.h"
#include "CameraManager.h"
#include "CameraC.h"
#include "ObjectFactory.h"
#include "GameObject.h"
#include "InputManager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CCameraManager)

void CCameraManager::Awake(void)
{
	__super::Awake();
}

void CCameraManager::Start(void)
{
	if (m_spMainCamera == nullptr)
	{
		SP(CGameObject) spBasicObject = ADD_CLONE(L"BasicObject", true);
		m_spMainCamera = spBasicObject->AddComponent<CCameraC>();
		spBasicObject->GetComponent<CTransformC>()->SetPosition(_float3(0, 0, -3));
		AddCamera(L"FreeCamera", m_spMainCamera);
	}
}

void CCameraManager::Update(void)
{
	if (m_updateProj)
	{
		for (auto& camera : m_mCameras)
		{
			camera.second->SetUpdateProj(true);
		}
		m_updateProj = false;
	}
	
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

void CCameraManager::SetMainCameraMode(void)
{
	if (IMKEY_DOWN(KEY_1))
	{
		m_spMainCamera->SetMode(ECameraMode::Fixed);
		m_spMainCamera->SetMoveable(false);
		m_spMainCamera->SetRotatable(false);
	}
	else if (IMKEY_DOWN(KEY_2))
	{
		m_spMainCamera->SetMode(ECameraMode::Edit);
		m_spMainCamera->SetMoveable(true);
		m_spMainCamera->SetRotatable(false);
	}
	else if (IMKEY_DOWN(KEY_3))
	{
		m_spMainCamera->SetMode(ECameraMode::FPS);
		m_spMainCamera->SetMoveable(true);
		m_spMainCamera->SetRotatable(false);
	}
}
