#ifndef FRC_H
#define FRC_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CFRC final : public CEngine
{
	DECLARE_SINGLETON(CFRC)
public:
					void				Awake				(void) override;
					void				Start				(void);

					void				OnDestroy			(void);

					void				OnEnable			(void);
					void				OnDisable			(void);

					bool				FrameLock			(void);

					void				TimerStart			(void);
					_float				GetElapsedTime		(void);
private:

					//cpu�� �ʴ� ������
					LARGE_INTEGER		m_cpuTick			= {};
					//���� ������������ ������
					LARGE_INTEGER		m_beginTime			= {};
					//���� ������� ������
					LARGE_INTEGER		m_endTime			= {};
					//�� �������� �ӵ� ����Ʈ. second per frame limit.
					_float				m_spfLimit			= 0.f;

					LONGLONG			m_timer				= {};
					
	GETTOR			(_float,			m_fixedDeltaTime,	0.f,		FixedDeltaTime)
	GETTOR			(_float,			m_deltaTime,		0.f,		DeltaTime)
	GETTOR			(_float,			m_FPS,				0.f,		FPS)

};
END
#endif