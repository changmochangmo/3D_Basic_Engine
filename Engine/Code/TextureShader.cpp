#include "EngineStdafx.h"
#include "TextureShader.h"
#include "DeviceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CameraManager.h"
#include "CameraC.h"
#include "Mesh.h"


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
			if (FAILED(m_pShader->BeginPass(i)))
			{
				MSG_BOX(__FILE__, L"Shader BeginPass Failed");
				ABORT;
			}
			_int meshType = pGC->GetMesh()->GetMeshData()->GetMeshType();

			switch (meshType)
			{
			case (_int)EMeshType::Static:
				__super::RenderStaticMesh(pGC);
				break;

			case (_int)EMeshType::Dynamic:
				__super::RenderDynamicMesh(pGC);
				break;

			default:
				break;
			}

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
