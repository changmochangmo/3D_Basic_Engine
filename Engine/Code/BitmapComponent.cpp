//#include "EngineStdafx.h"
//#include "BitmapComponent.h"
//#include "DeviceManager.h"
//
//USING(Engine)
//LPDIRECT3DVERTEXBUFFER9 CBitmapComponent::m_s_pVertexBuffer = nullptr;
//LPDIRECT3DINDEXBUFFER9 CBitmapComponent::m_s_pIndexBuffer = nullptr;
//
//CBitmapComponent::CBitmapComponent()
//{
//}
//
//
//CBitmapComponent::~CBitmapComponent()
//{
//}
//
//SHARED(CComponent) CBitmapComponent::MakeClone(CGameObject * pObject)
//{
//	SHARED(CBitmapComponent) pClone(new CBitmapComponent);
//	pClone->SetOwner(pObject);
//	pClone->SetName(m_name);
//
//	return pClone;
//}
//
//void CBitmapComponent::Awake(void)
//{
//	__super::Awake();
//	m_componentID = (_int)(_int)m_s_componentID;;
//	if (m_s_pVertexBuffer == nullptr)
//		InitVertexBuffer();
//	if (m_s_pIndexBuffer == nullptr)
//		InitIndexBuffer();
//}
//
//void CBitmapComponent::Start(SHARED(CComponent) spThis)
//{
//	__super::Start(spThis);
//}
//
//_uint CBitmapComponent::FixedUpdate(SHARED(CComponent) spThis)
//{
//	return _uint();
//}
//
//_uint CBitmapComponent::Update(SHARED(CComponent) spThis)
//{
//	return _uint();
//}
//
//_uint CBitmapComponent::LateUpdate(SHARED(CComponent) spThis)
//{
//	return _uint();
//}
//
//void CBitmapComponent::OnDestroy(void)
//{
//}
//
//void CBitmapComponent::OnEnable(void)
//{
//}
//
//void CBitmapComponent::OnDisable(void)
//{
//}
//
//LPDIRECT3DVERTEXBUFFER9 CBitmapComponent::GetVertexBuffer(void)
//{
//	return m_s_pVertexBuffer;
//}
//
//LPDIRECT3DINDEXBUFFER9 CBitmapComponent::GetIndexBuffer(void)
//{
//	return m_s_pIndexBuffer;
//}
//
//void CBitmapComponent::InitVertexBuffer(void)
//{
//	HRESULT result;
//	//Create the vertex buffer
//	result = GET_DEVICE->CreateVertexBuffer(4 * sizeof(_CustomVertex2D),
//										    0,
//										    customFVF2D,
//										    D3DPOOL_MANAGED,
//										    &m_s_pVertexBuffer,
//										    NULL);
//
//	if (FAILED(result))
//	{
//		MessageBox(nullptr, L"VertexBuffer creation failed in InitVertexBuffer", L"CGraphicsManager.cpp", MB_OK);
//		return;
//	}
//
//	_CustomVertex2D* vertices;
//
//	m_s_pVertexBuffer->Lock( 0, 0, (void**)& vertices, 0 );
//
//    //Set the position
//    vertices[0].position = D3DXVECTOR3 (-0.5, -0.5, 0);
//    vertices[1].position = D3DXVECTOR3 ( 0.5, -0.5, 0);
//    vertices[2].position = D3DXVECTOR3 ( 0.5,  0.5, 0);
//    vertices[3].position = D3DXVECTOR3 (-0.5,  0.5, 0);
//
//    //Set the texture information
//    vertices[0].texture  = D3DXVECTOR2 (0.0f, 1.0f);
//    vertices[1].texture  = D3DXVECTOR2 (1.0f, 1.0f);
//    vertices[2].texture  = D3DXVECTOR2 (1.0f, 0.0f);
//    vertices[3].texture  = D3DXVECTOR2 (0.0f, 0.0f);
//
//	m_s_pVertexBuffer->Unlock();
//}
//
//void CBitmapComponent::InitIndexBuffer(void)
//{
//	HRESULT result;
//
//	result = GET_DEVICE->CreateIndexBuffer( 6 * sizeof(WORD),
//										    0, 
//										    D3DFMT_INDEX16,
//										    D3DPOOL_MANAGED,
//										    &m_s_pIndexBuffer, 
//										    NULL );
//
//	if (FAILED(result))
//	{
//		MessageBox(nullptr, L"IndexBuffer creation failed in InitIndexBuffer", L"CGraphicsManager.cpp", MB_OK);
//		return;
//	}
//
//	WORD* index = 0;
//
//	m_s_pIndexBuffer->Lock( 0, 0, (void**)&index, 0 );
//
//    //Match the vertex buffer and texture info
//    index[0] = 0;
//    index[1] = 1;
//    index[2] = 2;
//    index[3] = 0;
//    index[4] = 2;
//    index[5] = 3;
//
//	m_s_pIndexBuffer->Unlock();
//}
