#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


BEGIN(Engine)
class ENGINE_DLL CGameObject abstract  
{
	SMART_DELETER_REGISTER

protected:
	explicit							CGameObject			(void);
	explicit							CGameObject			(const CGameObject& other);
	virtual							   ~CGameObject			(void);

public:
	virtual			SP(CGameObject)		MakeClone			(void) PURE;
		
	virtual			void				Awake				(void) PURE;
	virtual			void				Start				(void) PURE;
	
	virtual			void				FixedUpdate			(void) PURE;
	virtual			void				Update				(void) PURE;
	virtual			void				LateUpdate			(void) PURE;
	
	virtual			void				OnDestroy			(void) PURE;
	
	virtual			void				OnEnable			(void) PURE;
	virtual			void				OnDisable			(void) PURE;

public:
	virtual			void				OnCollisionEnter	(_CollisionInfo ci) {}
	virtual			void				OnCollisionStay		(_CollisionInfo ci) {}
	virtual			void				OnCollisionExit		(_CollisionInfo ci) {}

	virtual			void				OnTriggerEnter		(CCollisionC const* pCollisionC) {}
	virtual			void				OnTriggerStay		(CCollisionC const* pCollisionC) {}
	virtual			void				OnTriggerExit		(CCollisionC const* pCollisionC) {}

public:
	virtual			void				SetBasicName		(void) PURE;

protected:
					void				InitClone			(SP(CGameObject) spClone);

protected:
	typedef std::unordered_map<_uint, SP(CComponent)> _COMPONENTS;

	GETTOR			(_COMPONENTS,		m_mComponents,		{},			Components)

	GETTOR_SETTOR	(_bool,				m_isClone,			false,		IsClone)

	GETTOR_SETTOR	(_bool,				m_isStatic,			false,		IsStatic)
	GETTOR_SETTOR	(_bool,				m_isAwaked,			false,		IsAwaked)
	GETTOR_SETTOR	(_bool,				m_isStarted,		false,		IsStarted)

	GETTOR_SETTOR	(_bool,				m_isEnabled,		true,		IsEnabled)
	GETTOR_SETTOR	(_bool,				m_deleteThis,		false,		DeleteThis)

	GETTOR_SETTOR	(_int,				m_dataID,			-1,			DataID)						
	GETTOR_SETTOR	(_int,				m_layerID,			-1,			LayerID)
	GETTOR_SETTOR	(std::wstring,		m_objectKey,		L"",		ObjectKey)

	GETTOR_SETTOR	(std::wstring,		m_name,				L"",		Name)

public:
	//오브젝트에서 컴포넌트 가져오는 함수
	template <typename ComponentType>
	SP(ComponentType) GetComponent(void)
	{
		auto& it = m_mComponents.find((_uint)ComponentType::m_s_componentID);
		if (it != m_mComponents.end())
			return std::dynamic_pointer_cast<ComponentType>(it->second);

		return nullptr;
	}

	template <typename ComponentType>
	SP(ComponentType) AddComponent(void)
	{
		SP(ComponentType) pNewComponent = nullptr;

		if ((pNewComponent = GetComponent<ComponentType>()) == nullptr)
		{
			pNewComponent.reset(new ComponentType);
			pNewComponent->SetOwner(this);
			pNewComponent->Awake();
			m_mComponents[pNewComponent->GetComponentID()] = pNewComponent;

			return pNewComponent;
		}
		else
		{
			MSG_BOX(__FILE__, (pNewComponent->GetName() + L" is already in " + m_objectKey).c_str());
			ABORT;
		}

		return nullptr;
	}
	
	//클론에 컴포넌트 복제하는 함수
	template <typename ComponentType>
	void AddComponentToClone(SP(ComponentType) pComponent)
	{
		auto& iter_find_comp = m_mComponents.find(pComponent->GetComponentID());
		if (iter_find_comp != m_mComponents.end())
		{
			MSG_BOX(__FILE__, (pComponent->GetName() + L" is already in " + m_objectKey).c_str());
			return;
		}

		SP(CComponent) pNewComponent = pComponent->MakeClone(this);
		m_mComponents[pComponent->GetComponentID()] = pNewComponent;
	}
};
END

#endif // !GAMEOBJECT_H
