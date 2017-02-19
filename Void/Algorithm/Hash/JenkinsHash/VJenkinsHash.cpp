#include "VJenkinsHash.h"
#include "../../../Utility/Logger/VLogger.h"
#include <bitset>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VJenkinsHash
    //----------------------------------------------------------------------------------------------------
    unsigned VJenkinsHash::OneAtATimeHash(const char* _key, size_t _length)
    {
        size_t i = 0;
        unsigned hash = 0;
        while (i != _length) {
            hash += _key[i++];
            hash += hash << 10;
            hash ^= hash >> 6;
        }
        hash += hash << 3;
        hash ^= hash >> 11;
        hash += hash << 15;
        return hash;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VJenkinsHash::Mix(unsigned& _a, unsigned& _b, unsigned& _c)
    {
        _a -= _b; _a -= _c; _a ^= ( _c >> 13 );
        _b -= _c; _b -= _a; _b ^= ( _a << 8 );
        _c -= _a; _c -= _b; _c ^= ( _b >> 13 );
        _a -= _b; _a -= _c; _a ^= ( _c >> 12 );
        _b -= _c; _b -= _a; _b ^= ( _a << 16 );
        _c -= _a; _c -= _b; _c ^= ( _b >> 5 );
        _a -= _b; _a -= _c; _a ^= ( _c >> 3 );
        _b -= _c; _b -= _a; _b ^= ( _a << 10 );
        _c -= _a; _c -= _b; _c ^= ( _b >> 15 );
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VJenkinsHashTest()
    {
        unsigned hash = VJenkinsHash::OneAtATimeHash("xixixi", 6);
        std::bitset<32> code(hash);
        VLogger::Info("Hash: %s", code.to_string().c_str());
        
        return;
    }
}
