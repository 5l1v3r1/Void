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
    
    //----------------------------------------------------------------------------------------------------
    int VRandom::Rand(int _min, int _max)
    {
        std::uniform_int_distribution<int> distribution(_min, _max);
        return distribution(mEngine);
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
        result = random2.Rand(5, 10);
        result = random2.Rand(5, 10);
        result = random2.Rand(5, 10);
        result = random2.Rand(5, 10);
        result = random2.Rand(5, 10);
        
        return;
    }
    
}
