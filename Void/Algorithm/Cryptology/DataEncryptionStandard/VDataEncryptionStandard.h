#pragma once
#ifndef _V_DATAENCRYPTIONSTANDARD_H_
#define _V_DATAENCRYPTIONSTANDARD_H_

#include <string>
#include <bitset>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VDataEncryptionStandardType
    //----------------------------------------------------------------------------------------------------
    enum class VDataEncryptionStandardType
    {
        ECB = 0,
        CBC,
        CFB,
    };
    
    // VDataEncryptionStandardPadding
    //----------------------------------------------------------------------------------------------------
    enum class VDataEncryptionStandardPadding
    {
        NoPadding = 0,
        PKCS5Padding,
        SSL3Padding,
    };
    
    // VDataEncryptionStandard
    //----------------------------------------------------------------------------------------------------
    class VDataEncryptionStandard
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VDataEncryptionStandard();
        VDataEncryptionStandard(const VDataEncryptionStandard& _des);
        ~VDataEncryptionStandard();
        
        //----------------------------------------------------------------------------------------------------
        std::string Generate();
        bool LoadSecretKey(const std::string& _key);
        std::string Encrypt(const std::string& _code);
        std::string Decrypt(const std::string& _code);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        // void Initialize();
        bool StringToBits(const std::string& _string, std::bitset<64>& _bits);
        bool BitsToString(const std::bitset<64>& _bits, std::string& _string);
        bool InitialPermutation(const std::bitset<64>& _bits, std::bitset<32>& _left, std::bitset<32>& _right);
        bool FinalPermutation(const std::bitset<32>& _left, const std::bitset<32>& _right, std::bitset<64>& _bits);
        bool SubKey(unsigned _n, std::bitset<48>& _subKey);
        bool SubProcess(const std::bitset<48>& _subKey, std::bitset<32>& _left, std::bitset<32>& _right);
        bool TrimTail(std::string& _code);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::bitset<64> mKey;
        VDataEncryptionStandardType mType;
        VDataEncryptionStandardPadding mPadding;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VDataEncryptionStandardTest();
}

#endif
