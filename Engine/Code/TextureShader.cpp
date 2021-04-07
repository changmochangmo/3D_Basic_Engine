#include "EngineStdafx.h"
#include "TextureShader.h"
#include "DeviceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CameraManager.h"
#include "CameraC.h"

USING(Engine)
CTextureShader::CTextureShader()
{
}

CTextureShader::~CTextureShader()
{
}

CTextureShader * CTextureShader::Create(void)
{
	CTextureShader* pTextureShader = new CTextureShader;
	pTextureShader->Awake();
	pTextureShader->Start();

	return pTextureShader;
}

void CTextureShader::Awake(void)
{
	__super::Awake();
	m_filePath = L"..\\..\\Resource\\Shader\\TextureShader.fx";
	
}

void CTextureShader::Start(void)
{
	LoadShader();
}

void CTextureShader::PreRender(CGraphicsC* pGC)
{
	m_pShader->SetMatrix("WorldMatrix", &pGC->GetTransform()->GetWorldMatrix());
	m_pShader->SetMatrix("ViewMatrix", &GET_MAIN_CAM->GetViewMatrix());
	m_pShader->SetMatrix("ProjMatrix", &GET_MAIN_CAM->GetProjMatrix());
	m_pShader->SetVector("Color", &pGC->GetTexture()->GetColor());
}

void CTextureShader::Render(CGraphicsC* pGC)
{
	_uint inumPasses = 0;

	if (SUCCEEDED(m_pShader->Begin(&inumPasses, NULL)))
	{
		for (_uint i = 0; i < inumPasses; ++i)
		{
			if (FAILED(m_pShader->BeginPass(0)))
				int a = 0;
			GET_DEVICE->DrawIndexedPrimitive(
				D3DPT_TRIANGLELIST,
				0,
				0,
				pGC->GetMesh()->GetMeshData()->vertexCount,
				0,
				pGC->GetMesh()->GetMeshData()->faceCount
			);
			m_pShader->EndPass();

		}

		m_pShader->End();
	}
}

void CTextureShader::PostRender(CGraphicsC* pGraphics)
{
}

void CTextureShader::OnDestroy(void)
{
}

void CTextureShader::OnEnable(void)
{
}

void CTextureShader::OnDisable(void)
{
}

void CTextureShader::LoadShader(void)
{
	__super::LoadShader();
}
