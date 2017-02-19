#include "VSimHash.h"
#include "../../../Utility/String/VString.h"
#include "../../../Utility/Logger/VLogger.h"
#include "../JenkinsHash/VJenkinsHash.h"
#include <string>
#include <vector>
#include <map>
#include <bitset>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VSimHash
     //----------------------------------------------------------------------------------------------------
    uint64_t VSimHash::Hash(const char* _key, size_t _length)
    {
        // Split
        std::vector<std::string> tokens = Match(std::string(_key, _length), std::regex("[\\w\u4e00-\u9fcc]{1,4}")); // Todo: option
        std::map<std::string, size_t> features;
        for (auto& token : tokens)
        {
            auto it = features.find(token);
            if(it != features.end())
            {
                ++it->second;
            }
            else
            {
                features[token] = 1;
            }
        }
        
        // Count
        int sums[64] = { 0 };
        uint64_t masks[64];
        for (int i = 0; i < 64; ++i)
        {
            masks[i] = 1LL << i;
        }
        for (auto feature : features)
        {
            uint64_t featureHash = (uint64_t)VJenkinsHash::OneAtATimeHash(feature.first.c_str(), feature.first.size());
            for (int i = 0; i < 64; ++i)
            {
                sums[i] += featureHash & masks[i] ? feature.second : -feature.second;
            }
        }
        
        // Build
        uint64_t result = 0;
        for (int i = 0; i < 64; ++i)
        {
            if (0 < sums[i])
            {
                result |= masks[i];
            }
        }
        return result;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VSimHash::IsEqual(uint64_t _left, uint64_t _right, unsigned short _n)
    {
        _left ^= _right;
        unsigned short count = 0;
        while(_left && ++count <= _n)
        {
            _left &= _left - 1;
        }
        return count <= _n;
    }
    
    //----------------------------------------------------------------------------------------------------
    unsigned short VSimHash::HammingDistance(uint64_t _left, uint64_t _right)
    {
        _left ^= _right;
        unsigned short count = 0;
        while(_left)
        {
            _left &= _left - 1;
            ++count;
        }
        return count;
    }

    // Test
    //----------------------------------------------------------------------------------------------------
    void VSimHashTest()
    {
        std::string sentence0("ya xixi hehehe hahaha haha haha");
        std::string sentence1("ya xixixi hehehe haha haha haha");
        uint64_t hash0 = VSimHash::Hash(sentence0.c_str(), sentence0.size());
        uint64_t hash1 = VSimHash::Hash(sentence1.c_str(), sentence1.size());
        std::bitset<64> code0(hash0);
        std::bitset<64> code1(hash1);
        VLogger::Info("Sim Hash: %s", code0.to_string().c_str());
        VLogger::Info("Sim Hash: %s", code1.to_string().c_str());
        VLogger::Info("Distance: %d", VSimHash::HammingDistance(hash0, hash1));
        
        return;
    }
}
