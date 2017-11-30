#pragma once
#ifndef _V_AUDIORESAMPLE_H_
#define _V_AUDIORESAMPLE_H_

#include "../AudioBase/VAudioBase.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAudioResampleType
    //----------------------------------------------------------------------------------------------------
    enum class VAudioResampleType
    {
        Arbitrary = 0,
        Linear,
    };
    
    // VAudioResample
    //----------------------------------------------------------------------------------------------------
    class VAudioResample
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static VAudioBase Resample(VAudioBase const* _source, const VAudioFormat& _outputFormat);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        static double HanningWindowFilter(double _t, int _zeros, double _lowpassFrequency);
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VAudioResampleTest();
}

#endif
