#pragma once
#ifndef _V_TIME_H_
#define _V_TIME_H_

#include <chrono>
#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VTime
    // duration (Rep, Period)
    // system_clock
    // time_point (Clock, Duration)
    //----------------------------------------------------------------------------------------------------
    class VTime
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static VTime Now();
        
    public:
        //----------------------------------------------------------------------------------------------------
        VTime();
        VTime(std::time_t _time);
        VTime(const VTime& _time);
        ~VTime();
        
        //----------------------------------------------------------------------------------------------------
        VTime operator+(const VTime& _time) const;
        VTime operator-(const VTime& _time) const;
        
        //----------------------------------------------------------------------------------------------------
        std::time_t Timestamp();
        std::string String();

        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::time_t mTime; // milliseconds
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VTimeTest();
}

#endif