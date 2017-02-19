#pragma once
#ifndef _V_SIMHASH_H_
#define _V_SIMHASH_H_

#include <cstdint>
#include <stddef.h>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VSimHash
    //----------------------------------------------------------------------------------------------------
    class VSimHash
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static uint64_t Hash(const char* _key, size_t _length);
        static bool IsEqual(uint64_t _left, uint64_t _right, unsigned short _n=3);
        static unsigned short HammingDistance(uint64_t _left, uint64_t _right);
        
    public:
        //----------------------------------------------------------------------------------------------------
        

    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VSimHashTest();
}

#endif
