#pragma once
#ifndef _V_TIMER_H_
#define _V_TIMER_H_

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VTimer
    //----------------------------------------------------------------------------------------------------
    class VTimer
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VTimer();
        VTimer(const VTimer& _timer);
        ~VTimer();
        
        //----------------------------------------------------------------------------------------------------
        void Start();
        void Stop();
        void Reset();
        void Tick();
        long long int DeltaTime();
        long long int TotalTime();
        
    protected:
        //----------------------------------------------------------------------------------------------------
        long long int m_startTime;
        long long int m_pausedTime;
        long long int m_stopTime;
        long long int m_previousTime;
        long long int m_currentTime;
        bool m_isStopped;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VTimerTest();
}

#endif
