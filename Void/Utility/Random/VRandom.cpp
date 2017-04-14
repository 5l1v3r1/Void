#include "VRandom.h"
#include <map>

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
    
    //----------------------------------------------------------------------------------------------------
    float VRandom::Rand(float _min, float _max)
    {
        std::uniform_real_distribution<float> distribution(_min, _max);
        return distribution(mEngine);
    }
    
    //----------------------------------------------------------------------------------------------------
    std::vector<int> VRandom::MultipleRand(unsigned long _count, int _min, int _max)
    {
        std::vector<int> result;
        result.reserve(_count);
        std::uniform_int_distribution<int> distribution(_min, _max);
        for (unsigned long i = 0; i < _count; ++i)
        {
            result.push_back(distribution(mEngine));
        }
        return result;
    }
    
    // Optimize: 1 / 2 reverse
    //----------------------------------------------------------------------------------------------------
    std::vector<int> VRandom::MultipleUniqueRand(unsigned int _count, int _min, int _max)
    {
        if (_max - _min + 1 < _count)
        {
            _count = _max - _min + 1;
        }
        
        std::vector<int> result;
        result.reserve(_count);
        std::map<int, int> replaceTable;
        for (unsigned int i = 0; i < _count; ++i)
        {
            std::uniform_int_distribution<int> distribution(_min, _max - i);
            int rand = distribution(mEngine);
            // find real rand
            std::map<int, int>::iterator it = replaceTable.find(rand);
            it == replaceTable.end() ? result.push_back(rand) : result.push_back(it->second);
            // replace rand
            it = replaceTable.find(_max - i);
            it == replaceTable.end() ? replaceTable[rand] = _max - i : replaceTable[rand] = it->second;
        }
        return result;
    }
    
    //----------------------------------------------------------------------------------------------------
    std::vector<float> VRandom::MultipleRand(unsigned long _count, float _min, float _max)
    {
        std::vector<float> result;
        result.reserve(_count);
        std::uniform_real_distribution<float> distribution(_min, _max);
        for (unsigned long i = 0; i < _count; ++i)
        {
            result.push_back(distribution(mEngine));
        }
        return result;
    }
    
    //----------------------------------------------------------------------------------------------------
    std::vector<float> VRandom::NormalMultipleRand(unsigned long _count, float _mean, float _stddev)
    {
        std::vector<float> result;
        result.reserve(_count);
        std::normal_distribution<float> distribution(_mean, _stddev);
        for (unsigned long i = 0; i < _count; ++i)
        {
            result.push_back(distribution(mEngine));
        }
        return result;
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
        float floatResult = random2.Rand(5.f, 100.f);
        floatResult = random2.Rand(-5.f, 1.f);
        auto mutipleResult = random2.MultipleRand(100, 5, 100);
        mutipleResult = random2.MultipleUniqueRand(10, 5, 10);
        mutipleResult = random2.MultipleUniqueRand(10, 5, 50);
        auto mutipleFloatResult = random2.MultipleRand(100, 5.f, 100.f);
        mutipleFloatResult = random2.MultipleRand(100, 5.f, 100.f);
        auto mutipleNormalResult = random2.NormalMultipleRand(20, 0, 1);
        mutipleNormalResult = random2.NormalMultipleRand(20, 0, 1);
        
        return;
    }
    
}
