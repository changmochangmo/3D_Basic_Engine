#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


BEGIN(Engine)
class ENGINE_DLL CGameObject final  
{
	SMART_DELETER_REGISTER

protected:
	explicit							CGameObject			(void);
	explicit							CGameObject			(const CGameObject& other);
									   ~CGameObject			(void);

public:
	static			SHARED(CGameObject) Create				(std::wstring layerKey = L"",
															 std::wstring objectKey = L"",
															 _bool isStatic = false);
					SHARED(CGameObject)	MakeClone			(void);
		
					void				Awake				(void);
					void				Start				(void);

					_uint				FixedUpdate			(void);
					_uint				Update				(void);
					_uint				LateUpdate			(void);

					void				OnDestroy			(void);

					void				OnEnable			(void);
					void				OnDisable			(void);

protected:
	typedef std::unordered_map<_uint, SHARED(CComponent)> _COMPONENTS;

	GETTOR			(_COMPONENTS,			m_mComponents,		{},				Components)
	GETTOR_SETTOR	(SHARED(CComponent),	m_pMainComponent,	nullptr,		MainComponent)

	GETTOR_SETTOR	(_bool,					m_isClone,			false,			IsClone)
	GETTOR_SETTOR	(_bool,					m_isStatic,			false,			IsStatic)
	GETTOR_SETTOR	(_bool,					m_isAwaked,			false,			IsAwaked)
	GETTOR_SETTOR	(_bool,					m_isStarted,		false,			IsStarted)
	GETTOR_SETTOR	(_bool,					m_isEnabled,		true,			IsEnabled)
	GETTOR_SETTOR	(_bool,					m_isNeedToBeDeleted,false,			IsNeedToBeDeleted)


	GETTOR_SETTOR	(std::wstring,			m_layerKey,			L"",			LayerKey)
	GETTOR_SETTOR	(std::wstring,			m_objectKey,		L"",			ObjectKey)
	GETTOR_SETTOR	(std::wstring,			m_name,				L"",			Name)




public:
	//오브젝트에서 컴포넌트 가져오는 함수
	template <typename ComponentType>
	SHARED(ComponentType) GetComponent(void)
	{
		auto& it = m_mComponents.find((_uint)ComponentType::m_s_componentID);
		if (it != m_mComponents.end())
			return std::dynamic_pointer_cast<ComponentType>(it->second);

		return nullptr;
	}

	//프로토 타입에 컴포넌트 추가하는 함수
	template <typename ComponentType>
	SHARED(ComponentType) AddComponent(void)
	{
		SHARED(ComponentType) pNewComponent = nullptr;

		if ((pNewComponent = GetComponent<ComponentType>()) == nullptr)
		{
			pNewComponent.reset(new ComponentType);
			if (pNewComponent->GetIsMain())
			{
				if (m_pMainComponent == nullptr)
					m_pMainComponent = pNewComponent;
				else
					return nullptr;
			}
			pNewComponent->SetOwner(this);
			pNewComponent->Awake();
			m_mComponents[pNewComponent->GetComponentID()] = pNewComponent;

			return pNewComponent;
		}
		else
			MSG_BOX(__FILE__, (pNewComponent->GetName() + L" is already in " + this->GetName()).c_str());

		return nullptr;
	}
	
	//클론에 컴포넌트 추가하는 함수
	template <typename ComponentType>
	void AddComponentToClone(SHARED(ComponentType) pComponent)
	{
		auto& iter_find_comp = m_mComponents.find(pComponent->GetComponentID());
		if (iter_find_comp != m_mComponents.end())
			return;

		SHARED(CComponent) pNewComponent = pComponent->MakeClone(this);
		pNewComponent->Awake();

		m_mComponents[pComponent->GetComponentID()] = pNewComponent;
	}
};
END

#endif // !GAMEOBJECT_H
