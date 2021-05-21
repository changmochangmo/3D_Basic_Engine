#include "EngineStdafx.h"
#include "UIShader.h"
#include "DeviceManager.h"
#include "CameraManager.h"
#include "CameraC.h"
#include "Object.h"

USING(Engine)
CUIShader::CUIShader()
{
}


CUIShader::~CUIShader()
{
}

CUIShader * CUIShader::Create(void)
{
	CUIShader* pUIShader = new CUIShader;
	pUIShader->Awake();
	pUIShader->Start();

	return pUIShader;
}

void CUIShader::Awake(void)
{
	__super::Awake();
	m_filePath = L"..\\..\\Resource\\Shader\\UIShader.fx";
	m_shaderType = (_int)EShaderType::UI;
}

void CUIShader::Start(void)
{
	LoadShader();
}

void CUIShader::PreRender(CGraphicsC * pGC)
{
	SP(CTextureC) spTexture = pGC->GetTexture();
	SP(CBitmapC) spBitmap	= pGC->GetBitmap();
	
	GET_DEVICE->SetStreamSource(0, spBitmap->GetVertexBuffer(), 0, sizeof(_CustomVertex2D));
	GET_DEVICE->SetFVF(customFVF2D);
	GET_DEVICE->SetIndices(spBitmap->GetIndexBuffer());

	_mat identityMatrix;
	D3DXMatrixIdentity(&identityMatrix);
	GET_DEVICE->SetTransform(D3DTS_WORLD, &pGC->GetOwner()->GetTransform()->GetWorldMatrix());
	GET_DEVICE->SetTransform(D3DTS_VIEW, &identityMatrix);
	GET_DEVICE->SetTransform(D3DTS_PROJECTION, &GET_MAIN_CAM->GetOrthoMatrix());
	// 	if (spTexture != nullptr)
	// 		GET_DEVICE->SetTexture(0, spTexture->GetTexData()->pTexture);
	// 	else
	// 		GET_DEVICE->SetTexture(0, nullptr);

	GET_DEVICE->
		SetTexture(0, spTexture->GetTexData()[spTexture->GetMeshIndex()][spTexture->GetTexIndex()]->pTexture);
}

void CUIShader::Render(CGraphicsC * pGC)
{
	GET_DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

void CUIShader::PostRender(CGraphicsC * pGC)
{
	GET_DEVICE->SetTransform(D3DTS_PROJECTION, &GET_MAIN_CAM->GetProjMatrix());
}

void CUIShader::OnDestroy(void)
{
}

void CUIShader::OnEnable(void)
{
}

void CUIShader::OnDisable(void)
{
}

void CUIShader::LoadShader(void)
{
	__super::LoadShader();
}
