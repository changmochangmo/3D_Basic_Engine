#include "EngineStdafx.h"
#include "ObjectFactory.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Layer.h"

USING(Engine)
IMPLEMENT_SINGLETON(CObjectFactory)

void CObjectFactory::Awake(void)
{
	__super::Awake();
}

void CObjectFactory::Start(void)
{
}

void CObjectFactory::OnDestroy(void)
{
	m_mCurPrototypes.clear();
	m_mStaticPrototypes.clear();
}

void CObjectFactory::OnEnable(void)
{
}

void CObjectFactory::OnDisable(void)
{
}

HRESULT CObjectFactory::AddPrototype(SP(CGameObject) pPrototype, _bool isStatic)
{
	if (pPrototype == nullptr)
		return E_FAIL;

	_PROTOTYPES* pCurPrototypes = nullptr;

	if (isStatic)
		pCurPrototypes = &m_mStaticPrototypes;
	else
		pCurPrototypes = &m_mCurPrototypes;

	auto& it = pCurPrototypes->find(pPrototype->GetObjectKey());
	if (it == pCurPrototypes->end())
	{
		(*pCurPrototypes)[pPrototype->GetObjectKey()] = pPrototype;
		pPrototype->SetIsStatic(isStatic);
	}
	else
	{
		MSG_BOX(__FILE__, (pPrototype->GetObjectKey() + L" is already in _PROTOTYPES").c_str());
		abort();
	}

	return S_OK;
}

SP(CGameObject) CObjectFactory::AddClone(const std::wstring & protoObjectKey,
										 _bool isStatic,
										 const std::wstring & name)
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
		abort();
	}

	SP(CGameObject) spClone = iter_find_prototype->second->MakeClone();
	if (spClone == nullptr)
	{
		MSG_BOX(__FILE__, (protoObjectKey + L" failed to make clone in AddClone").c_str());
		abort();
	}

	_int layerID = spClone->GetLayerID();
	std::vector<CLayer*> const* pLayers = &GET_CUR_SCENE->GetLayers();
	if (layerID < 0 || (_uint)layerID >= pLayers->size())
	{
		MSG_BOX(__FILE__, std::wstring(L"LayerID is out of range").c_str());
		abort();
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
