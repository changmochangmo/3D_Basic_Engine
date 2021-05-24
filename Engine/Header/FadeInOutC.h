#ifndef FADEINOUT_H
#define FADEINOUT_H

BEGIN(Engine)
class ENGINE_DLL CFadeInOutC final : public CComponent
{
public:
	explicit						CFadeInOutC			(void);
								   ~CFadeInOutC			(void);

public:
			SP(CComponent)			MakeClone			(CObject* pObject) override;
			void					Awake				(void) override;
			void					Start				(SP(CComponent) spThis) override;

			void					FixedUpdate			(SP(CComponent) spThis) override;
			void					Update				(SP(CComponent) spThis) override;
			void					LateUpdate			(SP(CComponent) spThis) override;

			void					OnDestroy			(void) override;

			void					OnEnable			(void) override;
			void					OnDisable			(void) override;
			
			void					Setup				(_bool isFadeIn, _float speed);
public:
	static const	EComponentID	m_s_componentID = EComponentID::FadeInOut;

private:
	GETTOR_SETTOR	(_bool,		m_isFadeIn,		false,		IsFadeIn)
	GETTOR_SETTOR	(_float,	m_speed,		1.f,		Speed)
	GETTOR_SETTOR	(_bool,		m_finish,		false,		Finish)
	
};
END
#endif