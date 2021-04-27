#ifndef DEBUGC_H
#define DEBUGC_H

BEGIN(Engine)
class CBoundingVolume;
class ENGINE_DLL CDebugC final : public CComponent
{
public:
	explicit						CDebugC			(void);
								   ~CDebugC			(void);

public:
			SP(CComponent)			MakeClone		(CObject* pObject) override;
			void					Awake			(void) override;
			void					Start			(SP(CComponent) spThis) override;

			void					FixedUpdate		(SP(CComponent) spThis) override;
			void					Update			(SP(CComponent) spThis) override;
			void					LateUpdate		(SP(CComponent) spThis) override;

			void					OnDestroy		(void) override;

			void					OnEnable		(void) override;
			void					OnDisable		(void) override;

public:
	static const	EComponentID	m_s_componentID = EComponentID::Debug;

private:
	GETTOR	(SP(CBoundingVolume),	m_spBV,		nullptr,	BV)
};
END
#endif