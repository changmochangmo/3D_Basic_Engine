#include "EngineStdafx.h"
#include "FRC.h"
#include "DataStore.h"

USING(Engine)
IMPLEMENT_SINGLETON(CFRC)

void CFRC::Awake(void)
{
	__super::Awake();

	QueryPerformanceFrequency(&m_cpuTick);
	QueryPerformanceCounter(&m_beginTime);
	QueryPerformanceCounter(&m_endTime);
}

void CFRC::Start(void)
{
	GET_VALUE(true, m_sectionKey, m_objectKey, L"m_fps", m_fps);
}

void CFRC::OnDestroy(void)
{
}

void CFRC::OnEnable(void)
{
}

void CFRC::OnDisable(void)
{
}

bool CFRC::FrameLock(void)
{
	QueryPerformanceCounter(&m_endTime);
	m_spfLimit += float(m_endTime.QuadPart - m_beginTime.QuadPart) / m_cpuTick.QuadPart;

	m_beginTime.QuadPart = m_endTime.QuadPart;

	if ((1.f / m_fps) < m_spfLimit)
	{
		m_deltaTime = m_spfLimit;
		m_spfLimit = 0.f;
		QueryPerformanceFrequency(&m_cpuTick);


		if (m_deltaTime > 0.1)
			return false;


		return true;
	}
	return false;
}

void CFRC::TimerStart(void)
{
	LARGE_INTEGER performanceCounter;
	QueryPerformanceCounter(&performanceCounter); // 시작시간

	m_timer = performanceCounter.QuadPart;
}

_float CFRC::GetElapsedTime(void)
{
	LARGE_INTEGER performanceCounter;
	QueryPerformanceCounter(&performanceCounter);

	_float pcFreq = static_cast<_float>(m_cpuTick.QuadPart);

	_float timeMeasured = static_cast<_float>(performanceCounter.QuadPart - m_timer) / pcFreq;

	return timeMeasured;
}
