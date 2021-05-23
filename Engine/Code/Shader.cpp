#include "EngineStdafx.h"
#include "Shader.h"
#include "DeviceManager.h"
#include "StaticMesh.h"
#include "DynamicMesh.h"
#include "CameraManager.h"
#include "CameraC.h"

USING(Engine)
CShader::CShader()
{
}


CShader::~CShader()
{
}

void CShader::Awake(void)
{
	__super::Awake();
}

void CShader::PreRender(CGraphicsC * pGC)
{
	//m_pShader->SetMatrix("WorldMatrix", &pGC->GetTransform()->GetWorldMatrix());
	//m_pShader->SetMatrix("ViewMatrix", &GET_MAIN_CAM->GetViewMatrix());
	//m_pShader->SetMatrix("ProjMatrix", &GET_MAIN_CAM->GetProjMatrix());

	GET_DEVICE->SetTransform(D3DTS_WORLD, &pGC->GetTransform()->GetWorldMatrix());
	GET_DEVICE->SetTransform(D3DTS_VIEW, &GET_MAIN_CAM->GetViewMatrix());
	GET_DEVICE->SetTransform(D3DTS_PROJECTION, &GET_MAIN_CAM->GetProjMatrix());
}

void CShader::LoadShader(void)
{
	D3DXCreateEffectFromFile(GET_DEVICE, m_filePath.c_str(),
		nullptr, nullptr, 0, nullptr, &m_pShader, nullptr);

	if (m_pShader == nullptr)
	{
		MSG_BOX(__FILE__, L"Create Effect failed in LoadShader");
		ABORT;
	}
}