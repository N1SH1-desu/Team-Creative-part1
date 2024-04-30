#include "CpuTimer.h"
#include "WinMin.h"

CpuTimer::CpuTimer() :
    m_baseTime(0),
    m_currTime(0),
    m_deltaTime(0.0),
    m_perSecCount(0.0),
    m_prevTime(0)
{
    __int64 countPerSec{};
    QueryPerformanceFrequency((LARGE_INTEGER*)&countPerSec);
    m_perSecCount = (1.0 / countPerSec);
}

CpuTimer::~CpuTimer()
{
}

float CpuTimer::DeltaTime() const
{
    return (float)m_deltaTime;
}

void CpuTimer::Start()
{
    __int64 baseTime{};
    QueryPerformanceCounter((LARGE_INTEGER*)&baseTime);

    m_baseTime = baseTime;
    m_prevTime = baseTime;
}

void CpuTimer::Tick()
{
    __int64 currTime{};
    QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

    m_currTime = currTime;
    m_deltaTime = (double)((m_currTime - m_baseTime) * m_perSecCount);

    m_prevTime = currTime;

}
