#pragma once
#ifndef _V_SECUREHASHALGORITHM_H_
#define _V_SECUREHASHALGORITHM_H_

#include <string>
#include <vector>
#include <array>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VSecureHashAlgorithm
    // Todo: use big number
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Algorithm and variant|Output size(bits)|Internal state size(bits)|Block size(bits)|Max message size(bits)|Rounds|                           Operations|
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // SHA-0                |              160|              160(5 × 32)|             512|              2^64 - 1|    80|      And, Xor, Rot, Add(mod 232), Or|
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // SHA-1                |              160|              160(5 × 32)|             512|              2^64 - 1|    80|      And, Xor, Rot, Add(mod 232), Or|
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // SHA-2|        SHA-224|              224|              256(8 × 32)|             512|              2^64 - 1|    64| And, Xor, Rot, Add(mod 232), Or, Shr|
    //               SHA-256|              256|                        -|               -|                     -|     -|                                    -|
    //               SHA-384|              384|              512(8 × 64)|            1024|             2^128 - 1|    80| And, Xor, Rot, Add(mod 232), Or, Shr|
    //               SHA-512|              512|                        -|               -|                     -|     -|                                    -|
    //           SHA-512/224|              224|                        -|               -|                     -|     -|                                    -|
    //           SHA-512/256|              256|                        -|               -|                     -|     -|                                    -|
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // SHA-3|       SHA3-224|              224|         1600(5 × 5 × 64)|            1152|             Unlimited|    24|                   And, Xor, Rot, Not|
    //              SHA3-256|              256|                        -|            1088|                     -|     -|                                    -|
    //              SHA3-384|              384|                        -|             832|                     -|     -|                                    -|
    //              SHA3-512|              512|                        -|             576|                     -|     -|                                    -|
    //              SHAKE128|     d(arbitrary)|                        -|            1344|                     -|     -|                                    -|
    //              SHAKE256|     d(arbitrary)|                        -|            1088|                     -|     -|                                    -|
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    class VSecureHashAlgorithm
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static std::string SHA1(const std::string& _input);
        static std::string SHA2_224(const std::string& _input);
        static std::string SHA2_256(const std::string& _input);
        static std::string SHA2_384(const std::string& _input);
        static std::string SHA2_512(const std::string& _input);
        static std::string SHA2_512_224(const std::string& _input);
        static std::string SHA2_512_256(const std::string& _input);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        static void Preprocess(const std::string& _input, std::vector<std::array<unsigned char, 64>>& _chunks);
        static void Preprocess(const std::string& _input, std::vector<std::array<unsigned char, 128>>& _chunks);
        static unsigned int BitRotateLeft(const unsigned int& _value, const unsigned int& _rotate);
        static unsigned long long int BitRotateLeft(const unsigned long long int& _value, const unsigned long long int& _rotate);
        static unsigned int BitRotateRight(const unsigned int& _value, const unsigned int& _rotate);
        static unsigned long long int BitRotateRight(const unsigned long long int& _value, const unsigned long long int& _rotate);
        static unsigned int BitShiftRight(const unsigned int& _value, const unsigned int& _shift);
        static unsigned long long int BitShiftRight(const unsigned long long int& _value, const unsigned long long int& _shift);
        static bool IsBigEndian();
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VSecureHashAlgorithmTest();
}

#endif
