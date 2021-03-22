#include "EngineStdafx.h"
#include "UIComponent.h"
#include "DeviceManager.h"
#include "GameObject.h"
#include "TextureStore.h"
#include "DataStore.h"
#include "UIManager.h"
#include "MeshStore.h"

#include "ShaderManager.h"
#include "Shader.h"
#include "SceneManager.h"

USING(Engine)
CUIComponent::CUIComponent()  
{
}


CUIComponent::~CUIComponent(void)
{
}

SHARED(CComponent) CUIComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CUIComponent) pClone(new CUIComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);

	pClone->SetTextureKey(m_textureKey);
	pClone->SetTexData(m_pTexData);

	return pClone;
}

void CUIComponent::Awake(void)
{
	__super::Awake();
	m_componentID = (int)m_s_componentID;
}


void CUIComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
	//현재 오브젝트가 Static Scene의 오브젝트냐?
	_bool		isStatic = m_pOwner->GetIsStatic();

	m_pTransform = m_pOwner->GetComponent<CTransformComponent>();

	std::wstring layerKey = m_pOwner->GetLayerKey();
	std::wstring objectKey = m_pOwner->GetObjectKey();

	if(layerKey != L"Default" && objectKey != L"Default")
		GET_VALUE(isStatic, layerKey, objectKey, L"m_textureKey", m_textureKey);


	if ((m_pTexData = CTextureStore::GetInstance()->GetTextureData(m_textureKey)) == nullptr)
		m_pTexData = CTextureStore::GetInstance()->GetTextureData(L"None");

	m_meshDate = CMeshStore::GetInstance()->GetMeshData(L"Cube");

	DateInit();
}

_uint CUIComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CUIComponent::Update(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CUIComponent::LateUpdate(SHARED(CComponent) spThis)
{
	CUIManager::GetInstance()->
		AddToRenderList(m_sortingLayer, std::dynamic_pointer_cast<CUIComponent>(spThis));
	return NO_EVENT;
}

_uint CUIComponent::PreRender(void)
{
	// 데이터 셋팅
	if (m_pTransform == nullptr)
		MSG_BOX(__FILE__, L"m_pTransform is nullptr");


	GET_DEVICE->SetStreamSource(0, m_meshDate->vertexBuffer, 0, m_meshDate->vertexSize);
	GET_DEVICE->SetFVF(m_meshDate->FVF);
	GET_DEVICE->SetIndices(m_meshDate->indexBuffer);

	if (m_pTexData != nullptr)
		GET_DEVICE->SetTexture(0, m_pTexData->pTexture);
	else
		GET_DEVICE->SetTexture(0, nullptr);

	//좌표셋팅
	_mat identityMatrix;
	D3DXMatrixIdentity(&identityMatrix);
	GET_DEVICE->SetTransform(D3DTS_WORLD, &GetOwner()->GetComponent<CTransformComponent>()->GetWorldMatrix());
	GET_DEVICE->SetTransform(D3DTS_VIEW, &identityMatrix);
	GET_DEVICE->SetTransform(D3DTS_PROJECTION, &GET_CUR_SCENE->GetMainCamera()->GetOrthoMatrix());


	return _uint();
}

_uint CUIComponent::Render(void)
{

	GET_DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_meshDate->vertexCount, 0, m_meshDate->faceCount);


	GET_DEVICE->SetTransform(D3DTS_PROJECTION, &GET_CUR_SCENE->GetMainCamera()->GetProjMatrix());
	return _uint();
}

_uint CUIComponent::PostRender(void)
{
	return _uint();
}

void CUIComponent::OnDestroy(void)
{
}

void CUIComponent::OnEnable(void)
{
}

void CUIComponent::OnDisable(void)
{
}

void CUIComponent::DateInit()
{
	// FVF를 지정하여 보관할 데이터의 형식을 지정하고 사용자 정점을 보관할 메모리할당
	/*GET_DEVICE->CreateVertexBuffer(4 * sizeof(_CustomVertex), 0, customFVF, D3DPOOL_MANAGED, &m_meshDate.vertexBuffer, NULL);

	_CustomVertex* pVertices = nullptr;

	m_meshDate.vertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
	m_meshDate.vertexCount = 4;

	pVertices[0].position = _float3(-0.5f, 0.5f, 0);
	pVertices[0].uv = _float2(0, 0);

	pVertices[1].position = _float3(0.5f, 0.5f, 0);
	pVertices[1].uv = _float2(1, 0);

	pVertices[2].position = _float3(0.5f, -0.5f, 0);
	pVertices[2].uv = _float2(1, 1);

	pVertices[3].position = _float3(-0.5f, -0.5f, 0);
	pVertices[3].uv = _float2(0, 1);
		
	pVertices[0].normal = FLOAT3_BACK;
	pVertices[1].normal = FLOAT3_BACK;
	pVertices[2].normal = FLOAT3_BACK;
	pVertices[3].normal = FLOAT3_BACK;

	m_meshDate.vertexBuffer->Unlock();

	GET_DEVICE->CreateIndexBuffer(2 * sizeof(_float3), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_meshDate.indexBuffer, NULL);

	_float3* pIndices = nullptr;

	m_meshDate.indexBuffer->Lock(0, 0, (void**)&pIndices, 0);
	m_meshDate.faceCount = 2;

	pIndices[0] = _float3(0, 1, 2);
	pIndices[1] = _float3(0, 2, 3);

	m_meshDate.indexBuffer->Unlock();*/

}
