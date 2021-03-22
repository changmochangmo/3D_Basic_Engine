#ifndef TEXTURESHADER_H
#define TEXTURESHADER_H

#include "Shader.h"

BEGIN(Engine)
class ENGINE_DLL CTextureShader final : public CShader
{
private:
	explicit			CTextureShader		(void);
					   ~CTextureShader		(void);

public:
	static		CTextureShader*		Create		(void);

				void				Awake		(void) override;
				void				Start		(void) override;

				void				PreRender	(CGraphicsComponent* pGraphics) override;
				void				Render		(CGraphicsComponent* pGraphics) override;
				void				PostRender	(CGraphicsComponent* pGraphics) override;

				void				OnDestroy	(void) override;

				void				OnEnable	(void) override;
				void				OnDisable	(void) override;

private:
				void				LoadShader	(void) override;
};
END
#endif
//
//#include "stdafx.h"
//#include "HLSLTestDemo.h"
//#include "ShadedCube.h"
//
//HLSLTestDemo::HLSLTestDemo()
//{
//}
//
//
//HLSLTestDemo::~HLSLTestDemo()
//{
//}
//
//void HLSLTestDemo::Setup()
//{
//	HRESULT hr = 0;
//	shadedCube = new ShadedCube();
//
//	/*D3DXCreateTextureFromFile(
//	DEVICE,
//	L"../../Resources/crate.jpg",
//	&texture);
//
//	ID3DXBuffer* vsShader = nullptr;
//	ID3DXBuffer* vsErrorBuffer = nullptr;
//	ID3DXBuffer* psShader = nullptr;
//	ID3DXBuffer* psErrorBuffer = nullptr;
//
//
//
//	hr = D3DXCompileShaderFromFile
//	(
//	L"../../Shaders/TestVS.hlsl",
//	0,
//	0,
//	"main",
//	"vs_2_0",
//	D3DXSHADER_DEBUG,
//	&vsShader,
//	&vsErrorBuffer,
//	&vsConstantTable
//	);
//
//	if (vsErrorBuffer)
//	{
//	MessageBoxA(0, (char*)vsErrorBuffer->GetBufferPointer(), 0, 0);
//
//	assert(false);
//	}
//	assert(SUCCEEDED(hr));
//
//	hr = DEVICE->CreateVertexShader
//	(
//	(DWORD*)vsShader->GetBufferPointer(),
//	&vsTestShader
//	);
//	assert(SUCCEEDED(hr));
//
//	hr = D3DXCompileShaderFromFile
//	(
//	L"../../Shaders/TestPS.hlsl",
//	0,
//	0,
//	"main",
//	"ps_2_0",
//	D3DXSHADER_DEBUG,
//	&psShader,
//	&psErrorBuffer,
//	&psConstantTable
//	);
//
//	if (psErrorBuffer)
//	{
//	MessageBoxA(0, (char*)psErrorBuffer->GetBufferPointer(), 0, 0);
//
//	assert(false);
//	}
//	assert(SUCCEEDED(hr));
//
//	hr = DEVICE->CreatePixelShader
//	(
//	(DWORD*)psShader->GetBufferPointer(),
//	&psTestShader
//	);
//	assert(SUCCEEDED(hr));
//
//	WorldMatrixHandle = vsConstantTable->GetConstantByName(0, "WorldMatrix");
//	ViewMatrixHandle = vsConstantTable->GetConstantByName(0, "ViewMatrix");
//	ProjMatrixHandle = vsConstantTable->GetConstantByName(0, "ProjMatrix");
//
//	vsConstantTable->SetDefaults(DEVICE);
//
//	DiffuseHandle = psConstantTable->GetConstantByName(0, "Diffuse");
//	BaseMapHandle = psConstantTable->GetConstantByName(0, "BaseMap");
//
//	UINT count;
//	psConstantTable->GetConstantDesc(BaseMapHandle, &BaseMapDesc, &count);
//
//	psConstantTable->SetDefaults(DEVICE);*/
//
//	//DEVICE->Create
//	D3DXCreateEffectFromFile(DEVICE, L"../../Shaders/TestShader.fx", nullptr, nullptr, 0, nullptr, &m_pEffect, nullptr);
//
//
//
//	D3DXVECTOR3 worldPos(0, 0, 0);
//	D3DXVECTOR3 scalePos(1, 1, 1);
//	D3DXMatrixTranslation(&worldMatrix, 0, 0, 0);
//
//
//
//	D3DXMatrixPerspectiveFovLH(
//		&projMatrix, D3DX_PI * 0.25f,
//		(float)WIN_WIDTH / (float)WIN_HEIGHT, 1.0f, 1000.0f);
//
//	D3DXVECTOR3 position(0, 2, -2);
//	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
//	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
//	D3DXMATRIX viewMatrix;
//	D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &up);
//
//
//}
//
//void HLSLTestDemo::Cleanup()
//{
//
//}
//
//void HLSLTestDemo::Display()
//{
//	DEVICE->SetStreamSource(0, shadedCube->_vb, 0, shadedCube->vertexSize);
//	DEVICE->SetVertexDeclaration(shadedCube->m_pDeclare);
//	DEVICE->SetIndices(shadedCube->_ib);
//
//	D3DXMATRIX yRot;
//
//	static float y = 0.0f;
//
//	D3DXMatrixRotationY(&yRot, y);
//	y += 0.001f;
//
//	if (y >= 6.28f)
//		y = 0.0f;
//
//	//   vsConstantTable->SetMatrix(DEVICE, WorldMatrixHandle, &yRot);
//	//vsConstantTable->SetMatrix(DEVICE, ViewMatrixHandle, &viewMatrix);
//	//vsConstantTable->SetMatrix(DEVICE, ProjMatrixHandle, &projMatrix);
//
//	D3DXVECTOR4 diffuse(255, 255, 255, 255);
//	//psConstantTable->SetVector(DEVICE, DiffuseHandle, &diffuse);
//	DEVICE->SetTexture(BaseMapDesc.RegisterIndex, texture);
//
//	//DEVICE->SetVertexShader(vsTestShader);
//	//DEVICE->SetPixelShader(psTestShader);
//
//
//	m_pEffect->SetValue("WorldMatrix", &worldMatrix, sizeof(worldMatrix));
//	m_pEffect->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
//	m_pEffect->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));
//	m_pEffect->SetValue("Diffuse", &diffuse, sizeof(diffuse));
//
//	m_pEffect->BeginPass(0);
//
//	DEVICE->DrawIndexedPrimitive
//	(
//		D3DPT_TRIANGLELIST,
//		0,
//		0,
//		24,
//		0,
//		12
//	);
//	m_pEffect->EndPass();
//
//}