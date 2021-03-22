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
					//cpu의 초당 진동수
					LARGE_INTEGER		m_cpuTick			= {};
					//측정 시작했을때의 진동수
					LARGE_INTEGER		m_beginTime			= {};
					//측정 종료시의 진동수
					LARGE_INTEGER		m_endTime			= {};
					//한 프레임의 속도 리미트. second per frame limit.
					_float				m_spfLimit			= 0.f;
					//1초에 몇 프레임이 흘러가는지.
					_float				m_fps				= 0.f;

					LONGLONG			m_timer				= {};
					

	GETTOR			(_float,			m_deltaTime,		0.f,		DeltaTime)
};
END
#endif