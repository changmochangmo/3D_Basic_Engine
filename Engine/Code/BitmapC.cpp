#include "EngineStdafx.h"
#include "BitmapC.h"
#include "DeviceManager.h"

USING(Engine)
LPDIRECT3DVERTEXBUFFER9 CBitmapC::m_s_pVertexBuffer = nullptr;
LPDIRECT3DINDEXBUFFER9	CBitmapC::m_s_pIndexBuffer	= nullptr;

CBitmapC::CBitmapC()
{
}


CBitmapC::~CBitmapC()
{
}

SP(CComponent) CBitmapC::MakeClone(CObject * pObject)
{
	SP(CBitmapC) pClone(new CBitmapC);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	return pClone;
}

void CBitmapC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)(_int)m_s_componentID;;
	if (m_s_pVertexBuffer == nullptr)
		InitVertexBuffer();
	if (m_s_pIndexBuffer == nullptr)
		InitIndexBuffer();
}

void CBitmapC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
}

void CBitmapC::FixedUpdate(SP(CComponent) spThis)
{

}

void CBitmapC::Update(SP(CComponent) spThis)
{

}

void CBitmapC::LateUpdate(SP(CComponent) spThis)
{

}

void CBitmapC::OnDestroy(void)
{
}

void CBitmapC::OnEnable(void)
{
}

void CBitmapC::OnDisable(void)
{
}

LPDIRECT3DVERTEXBUFFER9 CBitmapC::GetVertexBuffer(void)
{
	return m_s_pVertexBuffer;
}

LPDIRECT3DINDEXBUFFER9 CBitmapC::GetIndexBuffer(void)
{
	return m_s_pIndexBuffer;
}

void CBitmapC::InitVertexBuffer(void)
{
	HRESULT result;
	//Create the vertex buffer
	result = GET_DEVICE->CreateVertexBuffer(4 * sizeof(_CustomVertex2D),
										    0,
										    customFVF2D,
										    D3DPOOL_MANAGED,
										    &m_s_pVertexBuffer,
										    NULL);

	if (FAILED(result))
	{
		MessageBox(nullptr, L"VertexBuffer creation failed in InitVertexBuffer", L"CGraphicsManager.cpp", MB_OK);
		return;
	}

	_CustomVertex2D* vertices;

	m_s_pVertexBuffer->Lock( 0, 0, (void**)& vertices, 0 );

	//Set the position
	vertices[0].position = D3DXVECTOR3(-0.5, 0.5, 0);
	vertices[1].position = D3DXVECTOR3(0.5, 0.5, 0);
	vertices[2].position = D3DXVECTOR3(0.5, -0.5, 0);
	vertices[3].position = D3DXVECTOR3(-0.5, -0.5, 0);

	//Set the texture information
	vertices[0].texture = D3DXVECTOR2(0.0f, 0.0f);
	vertices[1].texture = D3DXVECTOR2(1.0f, 0.0f);
	vertices[2].texture = D3DXVECTOR2(1.0f, 1.0f);
	vertices[3].texture = D3DXVECTOR2(0.0f, 1.0f);

	m_s_pVertexBuffer->Unlock();
}

void CBitmapC::InitIndexBuffer(void)
{
	HRESULT result;

	result = GET_DEVICE->CreateIndexBuffer( sizeof(_CustomVertex2D) * 2,
										    0, 
										    D3DFMT_INDEX16,
										    D3DPOOL_MANAGED,
										    &m_s_pIndexBuffer, 
										    NULL );

	if (FAILED(result))
	{
		MessageBox(nullptr, L"IndexBuffer creation failed in InitIndexBuffer", L"CGraphicsManager.cpp", MB_OK);
		return;
	}

	INDEX16* index = 0;

	m_s_pIndexBuffer->Lock( 0, 0, (void**)&index, 0 );

    //Match the vertex buffer and texture info
	index[0]._0 = 0;
	index[0]._1 = 1;
	index[0]._2 = 2;

	index[1]._0 = 0;
	index[1]._1 = 2;
	index[1]._2 = 3;

	m_s_pIndexBuffer->Unlock();
}
