#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "Engine.h"

BEGIN(Engine)
class CGameObject;
class ENGINE_DLL CObjectFactory final : public CEngine
{
	DECLARE_SINGLETON(CObjectFactory)
public:
			void						Awake				(void) override;
			void						Start				(void);

			void						OnDestroy			(void);

			void						OnEnable			(void);
			void						OnDisable			(void);

			HRESULT						AddPrototype		(SHARED(CGameObject) pPrototype, _bool isStatic);
			SHARED(CGameObject)			AddClone			(const std::wstring& protoObjectKey,
															 _bool isStatic = false);

			void						ClearCurPrototype	(void);
private:															 
	//�������� ���� ������ ���� ��. �� ���� �ϳ��� Scene�� �ǹ�. ������Ÿ��
	typedef std::unordered_map<std::wstring, SHARED(CGameObject)> _PROTOTYPES;
					_PROTOTYPES		m_mCurPrototypes;
					_PROTOTYPES		m_mStaticPrototypes;
};
END
#endif