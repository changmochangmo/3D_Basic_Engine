#include "EngineStdafx.h"
#include "GraphicsManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "DeviceManager.h"
#include "GameObject.h"
#include "CameraManager.h"
#include "Camera.h"
#include "Frustum.h"

USING(Engine)
IMPLEMENT_SINGLETON(CGraphicsManager)

void CGraphicsManager::Awake(void)
{
	__super::Awake();
}

void CGraphicsManager::Start(void)
{
}

_uint CGraphicsManager::FixedUpdate(void)
{
	return NO_EVENT;
}

_uint CGraphicsManager::Update(void)
{
	return NO_EVENT;
}

_uint CGraphicsManager::LateUpdate(void)
{
	for (int i = 0; i < (_int)ERenderID::NumOfRenderID; ++i)
	{
		for (auto& it = m_vRenderList[i].begin(); it != m_vRenderList[i].end();)
		{
			if ((*it)->GetOwner() == nullptr)
				it = m_vRenderList[i].erase(it);
			else
				++it;
		}
	}

	return NO_EVENT;
}

_uint CGraphicsManager::PreRender(void)
{
	GET_DEVICE->Clear(0, nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(255, 0, 0, 0),
		1.f, 0);

	GET_DEVICE->BeginScene();



	
	return NO_EVENT;
}

_uint CGraphicsManager::Render(void)
{
	_uint event = NO_EVENT;

	for (_uint i = 0; i < (_uint)ERenderID::NumOfRenderID; ++i)
	{
		if ((_uint)ERenderID::WireFrame == i)
		{
			GET_DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		}
		else
		{
			GET_DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}

		if ((_uint)ERenderID::UI == i)
		{
			GET_DEVICE->SetRenderState(D3DRS_ZENABLE, FALSE);
			GET_DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		}

		for (auto& pGC : m_vRenderList[i])
		{
			if (pGC->GetOwner() != nullptr)
			{
				if (GET_MAIN_CAM->GetFrustum()->CheckAabb(pGC->GetTransform()->GetPosition(), 
														  pGC->GetTransform()->GetScale() / 2.f))
				{
					if (event = pGC->PreRender()) return event;
					if (event = pGC->Render()) return event;
					if (event = pGC->PostRender()) return event;
				}
			}

			pGC.reset();		
		}

		if ((_uint)ERenderID::UI == i)
		{
			GET_DEVICE->SetRenderState(D3DRS_ZENABLE, TRUE);
			GET_DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		}

		m_vRenderList[i].clear();
	}

	return event;
}

_uint CGraphicsManager::PostRender(void)
{
	GET_DEVICE->EndScene();
	GET_DEVICE->Present(NULL, NULL, NULL, NULL);
	return NO_EVENT;
}

void CGraphicsManager::OnDestroy(void)
{

	for (_uint i = 0; i < (_uint)ERenderID::NumOfRenderID; ++i)
		m_vRenderList[i].clear();
}

void CGraphicsManager::OnEnable(void)
{
}

void CGraphicsManager::OnDisable(void)
{
}

void CGraphicsManager::AddToRenderList(_int renderID, SHARED(CGraphicsComponent) pGC)
{
	if (pGC == nullptr)
	{
		MSG_BOX(__FILE__, L"GraphicComponent is null in AddToRenderList");
		abort();
	}

	if ((_int)ERenderID::NumOfRenderID <= renderID || renderID < 0)
	{
		MSG_BOX(__FILE__, L"renderID is out of range in AddToRenderList");
		abort();
	}

	m_vRenderList[(_uint)renderID].push_back(pGC);
}
