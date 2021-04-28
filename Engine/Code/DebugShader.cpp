#include "EngineStdafx.h"
#include "DebugShader.h"
#include "CameraManager.h"
#include "StaticMesh.h"
#include "DynamicMesh.h"

USING(Engine)
CDebugShader::CDebugShader()
{
}


CDebugShader::~CDebugShader()
{
}

CDebugShader * CDebugShader::Create(void)
{
	CDebugShader* pInstance = new CDebugShader;
	pInstance->Awake();
	pInstance->Start();

	return pInstance;
}

void CDebugShader::Awake(void)
{
	__super::Awake();
	m_filePath		= L"..\\..\\Resource\\Shader\\DebugShader.fx";
	m_shaderType	= (_int)EShaderType::Debug;
}

void CDebugShader::Start(void)
{
	LoadShader();
}

void CDebugShader::PreRender(CGraphicsC * pGC)
{
	__super::PreRender(pGC);
	m_pShader->SetVector("Color", &_float4(0.f, 0.f, 0.f, 1.f));
}

void CDebugShader::Render(CGraphicsC * pGC)
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
			const std::vector<CMesh*>& vMeshData = pGC->GetMesh()->GetMeshDatas();

			for (_int i = 0; i < (_int)vMeshData.size(); ++i)
			{
				CStaticMesh* pSM = dynamic_cast<CStaticMesh*>(vMeshData[i]);
				for (_ulong j = 0; j < pSM->GetSubsetCount(); ++j)
					pSM->GetMesh()->DrawSubset(j);

				m_pShader->EndPass();
			}
		}

		m_pShader->End();
	}
}

void CDebugShader::PostRender(CGraphicsC * pGC)
{
}

void CDebugShader::OnDestroy(void)
{
}

void CDebugShader::OnEnable(void)
{
}

void CDebugShader::OnDisable(void)
{
}

void CDebugShader::LoadShader(void)
{
	__super::LoadShader();
}
