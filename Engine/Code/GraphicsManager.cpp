#include "EngineStdafx.h"
#include "GraphicsManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "DeviceManager.h"
#include "Object.h"
#include "CameraManager.h"
#include "CameraC.h"
#include "Frustum.h"
#include "ShaderManager.h"
#include "Shader.h"

USING(Engine)
IMPLEMENT_SINGLETON(CGraphicsManager)

void CGraphicsManager::Awake(void)
{
	__super::Awake();
}

void CGraphicsManager::Start(void)
{
}

void CGraphicsManager::FixedUpdate(void)
{
}

void CGraphicsManager::Update(void)
{
}

void CGraphicsManager::LateUpdate(void)
{
	for (int i = 0; i < (_int)ERenderID::NumOfRenderID; ++i)
	{
		for (auto& it = m_vRenderList[i].begin(); it != m_vRenderList[i].end();)
		{
			if ((*it)->GetOwner() == nullptr)
			{
				(*it).reset();
				it = m_vRenderList[i].erase(it);
			}
			else
				++it;
		}
	}
}

void CGraphicsManager::PreRender(void)
{
	GET_DEVICE->Clear(0, nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(255, 125, 125, 125),
		1.f, 0);

	GET_DEVICE->BeginScene();
}

void CGraphicsManager::Render(void)
{
	RenderBase();
	RenderNonAlpha();
	RenderWire();
	RenderAlphaTest();
	RenderAlphaBlend();
	RenderUI();

	ClearRenderList();
}

void CGraphicsManager::PostRender(void)
{
	GET_DEVICE->EndScene();
	//GET_DEVICE->Present(NULL, NULL, NULL, NULL);
}

void CGraphicsManager::OnDestroy(void)
{
	for (_uint i = 0; i < (_uint)ERenderID::NumOfRenderID; ++i)
	{
		for (auto& pGC : m_vRenderList[i])
			pGC.reset();

		m_vRenderList[i].clear();
	}
}

void CGraphicsManager::OnEnable(void)
{
}

void CGraphicsManager::OnDisable(void)
{
}

void CGraphicsManager::AddToRenderList(_int renderID, SP(CGraphicsC) pGC)
{
	if (pGC == nullptr)
	{
		MSG_BOX(__FILE__, L"GraphicComponent is null in AddToRenderList");
		ABORT;
	}

	if (renderID >= (_int)ERenderID::NumOfRenderID || renderID < 0)
	{
		MSG_BOX(__FILE__, L"renderID is out of range in AddToRenderList");
		ABORT;
	}

	m_vRenderList[(_uint)renderID].push_back(pGC);
}

void CGraphicsManager::ClearRenderList(void)
{
	for (_int i = 0; i < (_int)ERenderID::NumOfRenderID; ++i)
		m_vRenderList[i].clear();
}

void CGraphicsManager::RenderBase(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	CShader* pShader = GET_SHADER((_int)EShaderType::Texture);
	for (auto& spGC : m_vRenderList[(_int)ERenderID::Base])
	{
		if (spGC->GetOwner() != nullptr && spGC->GetIsEnabled())
		{
			if (GET_MAIN_CAM->GetFrustum()->
				CheckAabb(spGC->GetTransform()->GetPosition(),
					spGC->GetTransform()->GetSize() / 2.f))
			{
				pShader->PreRender(spGC.get());
				pShader->Render(spGC.get());
				pShader->PostRender(spGC.get());
			}
		}

		spGC.reset();
	}

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void CGraphicsManager::RenderNonAlpha(void)
{
	CShader* pShader = GET_SHADER((_int)EShaderType::Texture);
	for (auto& spGC : m_vRenderList[(_int)ERenderID::NonAlpha])
	{
		if (spGC->GetOwner() != nullptr && spGC->GetIsEnabled())
		{
			if (GET_MAIN_CAM->GetFrustum()->
				CheckAabb(spGC->GetTransform()->GetPosition(),
					spGC->GetTransform()->GetSize() / 2.f))
			{
				pShader->PreRender(spGC.get());
				pShader->Render(spGC.get());
				pShader->PostRender(spGC.get());
			}
		}
		spGC.reset();
	}
}

void CGraphicsManager::RenderWire(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CShader* pShader = GET_SHADER((_int)EShaderType::Debug);
	for (auto& spGC : m_vRenderList[(_int)ERenderID::WireFrame])
	{
		if (spGC->GetOwner() != nullptr && spGC->GetIsEnabled())
		{
			if (GET_MAIN_CAM->GetFrustum()->
				CheckAabb(spGC->GetTransform()->GetPosition(),
					spGC->GetTransform()->GetSize() / 2.f))
			{
				pShader->PreRender(spGC.get());
				pShader->Render(spGC.get());
				pShader->PostRender(spGC.get());
			}
		}
		spGC.reset();
	}
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void CGraphicsManager::RenderAlphaTest(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// 햇키드 얼굴 랜더링 할때 알파테스팅 해줘야됨
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 1); // 알파 기준 설정
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER); // 알파 테스팅 수행

	CShader* pShader = GET_SHADER((_int)EShaderType::Texture);
	for (auto& spGC : m_vRenderList[(_int)ERenderID::AlphaTest])
	{
		if (spGC->GetOwner() != nullptr && spGC->GetIsEnabled())
		{
			if (spGC->GetOwner() != nullptr && spGC->GetIsEnabled())
			{
				if (GET_MAIN_CAM->GetFrustum()->
					CheckAabb(spGC->GetTransform()->GetPosition(),
							  spGC->GetTransform()->GetSize() / 2.f))
				{
					pShader->PreRender(spGC.get());
					pShader->Render(spGC.get());
					pShader->PostRender(spGC.get());
				}
			}
		}

		spGC.reset();
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void CGraphicsManager::RenderAlphaBlend(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	CShader* pShader = GET_SHADER((_int)EShaderType::Texture);
	for (auto& spGC : m_vRenderList[(_int)ERenderID::AlphaBlend])
	{
		if (spGC->GetOwner() != nullptr && spGC->GetIsEnabled())
		{
			if (GET_MAIN_CAM->GetFrustum()->
				CheckAabb(spGC->GetTransform()->GetPosition(),
						  spGC->GetTransform()->GetSize() / 2.f))
			{
				pShader->PreRender(spGC.get());
				pShader->Render(spGC.get());
				pShader->PostRender(spGC.get());
			}
		}
		spGC.reset();
	}
}

void CGraphicsManager::RenderUI(void)
{
	CShader* pShader = GET_SHADER((_int)EShaderType::Texture);
	for (auto& spGC : m_vRenderList[(_int)ERenderID::UI])
	{
		if (spGC->GetOwner() != nullptr && spGC->GetIsEnabled())
		{
			if (GET_MAIN_CAM->GetFrustum()->
				CheckAabb(spGC->GetTransform()->GetPosition(),
					spGC->GetTransform()->GetSize() / 2.f))
			{
				pShader->PreRender(spGC.get());
				pShader->Render(spGC.get());
				pShader->PostRender(spGC.get());
			}
		}
		spGC.reset();
	}
}
