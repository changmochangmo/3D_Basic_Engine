#include "EngineStdafx.h"
#include "FRC.h"
#include "TextManager.h"

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
	m_FPS = 140;
}

void CFRC::OnDestroy(void)
{
}

void CFRC::OnEnable(void)
{
	m_enable = true;
	QueryPerformanceFrequency(&m_cpuTick);
	QueryPerformanceCounter(&m_beginTime);
	QueryPerformanceCounter(&m_endTime);
	m_spfLimit = 0.f;
}

void CFRC::OnDisable(void)
{
	m_enable = false;
}

_bool CFRC::FrameLock(void)
{
	if (m_enable == false)
		return true;

	QueryPerformanceCounter(&m_endTime);
	m_spfLimit += float(m_endTime.QuadPart - m_beginTime.QuadPart) / m_cpuTick.QuadPart;
	m_beginTime.QuadPart = m_endTime.QuadPart;

	if ((1.f / m_FPS) < m_spfLimit)
	{
		m_deltaTime = m_spfLimit;
		m_spfLimit = 0.f;
		QueryPerformanceFrequency(&m_cpuTick);

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

_float CFRC::GetDeltaTime(void)
{
	return m_deltaTime * m_dtCoef;
}
