#pragma once

class CpuTimer
{
public:
    CpuTimer();
    ~CpuTimer();

    float DeltaTime() const;

    void Start();
    void Tick();

private:
    double  m_deltaTime;
    double  m_perSecCount;
    
    __int64 m_baseTime;
    __int64 m_prevTime;
    __int64 m_currTime;
};
