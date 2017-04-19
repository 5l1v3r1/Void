#pragma once
#ifndef _V_BASE58_H_
#define _V_BASE58_H_

#include <string>
#include <map>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VBase58Alphabet
    // 123456789abcdefghijkmnopqrstuvwxyzABCDEFGHJKLMNPQRSTUVWXYZ
    // 123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz
    // rpshnaf39wBUDNEGHJKLM4PQRST7VWXYZ2bcdeCg65jkm8oFqi1tuvAxyz
    //----------------------------------------------------------------------------------------------------
    enum class VBase58Alphabet
    {
        DEFAULT = 0,
        BITCOIN,
        RIPPLE,
    };
    
    // VBase58
    // Base64 - Base58 = '0', 'O', 'I', 'l', '+', '/'
    //----------------------------------------------------------------------------------------------------
    class VBase58
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VBase58(VBase58Alphabet _alphabet=VBase58Alphabet::DEFAULT);
        
        //----------------------------------------------------------------------------------------------------
        std::string Encode(unsigned long long _target);
        
        //----------------------------------------------------------------------------------------------------
        unsigned long long Decode(const std::string& _target);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        void LoadAlphabet(VBase58Alphabet _alphabet=VBase58Alphabet::DEFAULT);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::string mAlphabet;
        std::map<char, unsigned> mAlphabetMap;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VBase58Test();
}

#endif
