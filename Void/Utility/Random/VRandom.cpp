#include "VRandom.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VRandom
    //----------------------------------------------------------------------------------------------------
    VRandom::VRandom()
        :
        mDevice(),
        mEngine(mDevice())
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    VRandom::VRandom(const VRandom& _random)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VRandom::~VRandom()
    {
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VRandomTest()
    {
        VRandom random1;
        int result = random1.Rand(5, 10);
        result = random1.Rand(5, 10);
        result = random1.Rand(5, 10);
        result = random1.Rand(5, 10);
        result = random1.Rand(5, 10);
        
        VRandom random2;
        result = random2.Rand(5, 5);
        result = random2.Rand(5, 6);
        result = random2.Rand(5, 7);
        result = random2.Rand(5, 8);
        result = random2.Rand(5, 100);
        float floatResult = random2.RealRand(5.f, 100.f);
        floatResult = random2.RealRand(-5.f, 1.f);
        auto mutipleResult = random2.MultipleRand(100, 5, 100);
        mutipleResult = random2.MultipleUniqueRand(10, 5, 10);
        mutipleResult = random2.MultipleUniqueRand(10, 5, 50);
        auto mutipleFloatResult = random2.MultipleRealRand(100, 5.f, 100.f);
        mutipleFloatResult = random2.MultipleRealRand(100, 5.f, 100.f);
        floatResult = random2.NormalRand(0, 1);
        auto mutipleNormalResult = random2.NormalMultipleRand<float>(20, 0, 1);
        mutipleNormalResult = random2.NormalMultipleRand<float>(20, 0, 1);
        
        return;
    }
    
}
