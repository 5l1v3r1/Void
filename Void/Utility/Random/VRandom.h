#pragma once
#ifndef _V_RANDOM_H_
#define _V_RANDOM_H_

#include <random>
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VRandom
    //----------------------------------------------------------------------------------------------------
    class VRandom
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VRandom();
        VRandom(const VRandom& _random);
        ~VRandom();
        
        //----------------------------------------------------------------------------------------------------
        int Rand(int _min, int _max);
        std::vector<int> MultipleRand(unsigned long _count, int _min, int _max);
        std::vector<int> MultipleUniqueRand(unsigned int _count, int _min, int _max);
        std::vector<float> NormalMultipleRand(unsigned long _count, float _mean, float _stddev);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::random_device mDevice;
        std::default_random_engine mEngine;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VRandomTest();
}

#endif
