#include "EngineStdafx.h"
#include "ObjectFactory.h"
#include "Object.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Layer.h"

#pragma region EnginePrototypeHeaders
#include "EmptyObject.h"
#include "BoundingVolume.h"
#include "DebugCollider.h"
#include "Grid.h"
#pragma endregion

USING(Engine)
IMPLEMENT_SINGLETON(CObjectFactory)

void CObjectFactory::Awake(void)
{
	__super::Awake();

	InitPrototypes();
}

void CObjectFactory::Start(void)
{
}

void CObjectFactory::OnDestroy(void)
{
	for (auto& object : m_mCurPrototypes)
		object.second.reset();
	m_mCurPrototypes.clear();

	for (auto& object : m_mStaticPrototypes)
		object.second.reset();
	m_mStaticPrototypes.clear();
}

void CObjectFactory::OnEnable(void)
{
}

void CObjectFactory::OnDisable(void)
{
}

HRESULT CObjectFactory::AddPrototype(SP(CObject) pPrototype)
{
	if (pPrototype == nullptr)
		return E_FAIL;

	_PROTOTYPES* pCurPrototypes = nullptr;

	if (pPrototype->GetIsStatic())
		pCurPrototypes = &m_mStaticPrototypes;
	else
		pCurPrototypes = &m_mCurPrototypes;

	auto& it = pCurPrototypes->find(pPrototype->GetObjectKey());
	if (it == pCurPrototypes->end())
	{
		(*pCurPrototypes)[pPrototype->GetObjectKey()] = pPrototype;
	}
	else
	{
		MSG_BOX(__FILE__, (pPrototype->GetObjectKey() + L" is already in _PROTOTYPES").c_str());
		ABORT;
	}

	return S_OK;
}

SP(CObject) CObjectFactory::AddClone(const std::wstring & protoObjectKey,
									 CScene* pScene,
									 _bool isStatic,
									 const std::wstring & name,
									 _int layerTag)
{
	_PROTOTYPES* pCurPrototypes = nullptr;

	if (isStatic)
		pCurPrototypes = &m_mStaticPrototypes;
	else
		pCurPrototypes = &m_mCurPrototypes;


	auto iter_find_prototype = pCurPrototypes->find(protoObjectKey);
	if (pCurPrototypes->end() == iter_find_prototype)
	{
		MSG_BOX(__FILE__, (protoObjectKey + L" is not found in AddClone").c_str());
		ABORT;
	}

	SP(CObject) spClone = iter_find_prototype->second->MakeClone();
	if (spClone == nullptr)
	{
		MSG_BOX(__FILE__, (protoObjectKey + L" failed to make clone in AddClone").c_str());
		ABORT;
	}

	_int layerID = spClone->GetLayerID();
	if (layerID == UNDEFINED)
		layerID = layerTag;

	std::vector<CLayer*> const* pLayers = &pScene->GetLayers();
	if (layerID < 0 || (_uint)layerID >= pLayers->size())
	{
		MSG_BOX(__FILE__, std::wstring(L"LayerID is out of range").c_str());
		ABORT;
	}
	(*pLayers)[layerID]->AddGameObject(spClone);

	if (name == L"")
		spClone->SetBasicName();
	else
	{
		_bool isThereSameName = false;
		for (auto& gameObject : (*pLayers)[layerID]->GetGameObjects())
		{
			if (gameObject->GetName() == name)
			{
				isThereSameName = true;
				spClone->SetBasicName();
				break;
			}
		}

		if (isThereSameName == false)
			spClone->SetName(name);
	}

	return spClone;
}

void CObjectFactory::ClearCurPrototype(void)
{
	for (auto& prototype : m_mCurPrototypes)
	{
		prototype.second.reset();
	}
	m_mCurPrototypes.clear();
}

void CObjectFactory::InitPrototypes(void)
{
	SP(CObject) spEmptyObjectPrototype(CEmptyObject::Create(true));
	ADD_PROTOTYPE(spEmptyObjectPrototype);

	SP(CObject) spBoundingVolumePrototype(CBoundingVolume::Create(true));
	ADD_PROTOTYPE(spBoundingVolumePrototype);

	SP(CObject) spDebugColliderPrototype(CDebugCollider::Create(true));
	ADD_PROTOTYPE(spDebugColliderPrototype);

	SP(CObject) spGridPrototype(CGrid::Create(true));
	ADD_PROTOTYPE(spGridPrototype);
}
