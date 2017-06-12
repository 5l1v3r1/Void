#include "VDataEncryptionStandard.h"
#include "../../../Utility/Random/VRandom.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VDataEncryptionStandard
    //----------------------------------------------------------------------------------------------------
    VDataEncryptionStandard::VDataEncryptionStandard()
        :
        mKey(),
        mType(VDataEncryptionStandardType::CBC),
        mPadding(VDataEncryptionStandardPadding::NoPadding)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VDataEncryptionStandard::VDataEncryptionStandard(const VDataEncryptionStandard& _des)
        :
        mKey(_des.mKey),
        mType(_des.mType),
        mPadding(_des.mPadding)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VDataEncryptionStandard::~VDataEncryptionStandard()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    std::string VDataEncryptionStandard::Generate()
    {
        std::string key;
        VRandom random;
        for (int i = 0; i < 8; ++i)
        {
            key.push_back((char)random.Rand(0, 255));
        }
        return key;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VDataEncryptionStandard::LoadSecretKey(const std::string& _key)
    {
        return StringToBits(_key, mKey);
    }
    
    //----------------------------------------------------------------------------------------------------
    std::string VDataEncryptionStandard::Encrypt(const std::string& _code)
    {
        std::string result;
        result.reserve(_code.size() + 8);
        for (unsigned index = 0; index < _code.length(); index += 8)
        {
            // Load
            std::bitset<64> bits;
            StringToBits(_code.substr(index, 8), bits);
            
            // IP
            std::bitset<32> left, right;
            InitialPermutation(bits, left, right);
            
            // Process
            for (char i = 0; i < 16; ++i)
            {
                std::bitset<48> subKey;
                SubKey(i, subKey);
                SubProcess(subKey, left, right);
                if (i != 15)
                {
                    // Exchange
                    std::bitset<32> temp = left;
                    left = right;
                    right = temp;
                }
            }
            
            // FP
            FinalPermutation(left, right, bits);
            
            // Save
            std::string string;
            BitsToString(bits, string);
            result += string;
        }
        
        return result;
    }
    
    //----------------------------------------------------------------------------------------------------
    std::string VDataEncryptionStandard::Decrypt(const std::string& _code)
    {
        std::string result;
        result.reserve(_code.size() + 8);
        for (unsigned index = 0; index < _code.length(); index += 8)
        {
            // Load
            std::bitset<64> bits;
            StringToBits(_code.substr(index, 8), bits);
            
            // IP
            std::bitset<32> left, right;
            InitialPermutation(bits, left, right);
            
            // Process
            for (char i = 15; 0 <= i; --i)
            {
                std::bitset<48> subKey;
                SubKey(i, subKey);
                SubProcess(subKey, left, right);
                if (i != 0)
                {
                    // Exchange
                    std::bitset<32> temp = left;
                    left = right;
                    right = temp;
                }
            }
            
            // FP
            FinalPermutation(left, right, bits);
            
            // Save
            std::string string;
            BitsToString(bits, string);
            result += string;
        }
        TrimTail(result);
        
        return result;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VDataEncryptionStandard::StringToBits(const std::string& _string, std::bitset<64>& _bits)
    {
        std::string target = _string.substr(0, 8);
        target.resize(8, '\0');
        for (unsigned i = 0; i < 64; ++i)
        {
            char subbits = target[i >> 3];
            if (subbits & (1 << (7 - i % 8)))
            {
                _bits.set(i, 1);
            }
            else
            {
                _bits.set(i, 0);
            }
        }
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VDataEncryptionStandard::BitsToString(const std::bitset<64>& _bits, std::string& _string)
    {
        _string = std::string(8, '\0');
        for (unsigned i = 0; i < 64; ++i)
        {
            if (_bits[i])
            {
                _string[i / 8] |= 1 << (7 - i % 8);
            }
        }
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VDataEncryptionStandard::InitialPermutation(const std::bitset<64>& _bits, std::bitset<32>& _left, std::bitset<32>& _right)
    {
        const unsigned char ipTable[64] = {
            58, 50, 42, 34, 26, 18, 10, 2,
            60, 52, 44, 36, 28, 20, 12, 4,
            62, 54, 46, 38, 30, 22, 14, 6,
            64, 56, 48, 40, 32, 24, 16, 8,
            57, 49, 41, 33, 25, 17, 9, 1,
            59, 51, 43, 35, 27, 19, 11, 3,
            61, 53, 45, 37, 29, 21, 13, 5,
            63, 55, 47, 39, 31, 23, 15, 7
        };
        // Right
        for (unsigned i = 0; i < 32; ++i)
        {
            _right[i] = _bits[ipTable[i] - 1];
        }
        // Left
        for (unsigned i = 0; i < 32; ++i)
        {
            _left[i] = _bits[ipTable[i + 32] - 1];
        }
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VDataEncryptionStandard::FinalPermutation(const std::bitset<32>& _left, const std::bitset<32>& _right, std::bitset<64>& _bits)
    {
        const unsigned char fpTable[64] = {
            40, 8, 48, 16, 56, 24, 64, 32,
            39, 7, 47, 15, 55, 23, 63, 31,
            38, 6, 46, 14, 54, 22, 62, 30,
            37, 5, 45, 13, 53, 21, 61, 29,
            36, 4, 44, 12, 52, 20, 60, 28,
            35, 3, 43, 11, 51, 19, 59, 27,
            34, 2, 42, 10, 50, 18, 58, 26,
            33, 1, 41, 9, 49, 17, 57, 25
        };
        for (unsigned i = 0; i < 64; ++i)
        {
            if (fpTable[i] <= 32)
            {
                _bits[i] = _right[fpTable[i] - 1];
            }
            else
            {
                _bits[i] = _left[fpTable[i] - 32 - 1];
            }
        }
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VDataEncryptionStandard::SubKey(unsigned _n, std::bitset<48>& _subKey)
    {
        if (16 <= _n)
        {
            return false;
        }
        
        // Permutation
        const unsigned char keyTable[56] = {
            57, 49, 41, 33, 25, 17, 9, 1,
            58, 50, 42, 34, 26, 18, 10, 2,
            59, 51, 43, 35, 27, 19, 11, 3,
            60, 52, 44, 36, 63, 55, 47, 39,
            31, 23, 15, 7, 62, 54, 46, 38,
            30, 22, 14, 6, 61, 53, 45, 37,
            29, 21, 13, 5, 28, 20, 12, 4
        };
        std::bitset<56> realKey;
        for (unsigned i = 0; i < 56; ++i)
        {
            realKey[i] = mKey[keyTable[i]];
        }
        
        // Shift
        const unsigned char shiftTable[16] = {
            1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
        };
        for (unsigned i = 0; i < _n; ++i)
        {
            for (unsigned j = 0; j < shiftTable[i]; ++j)
            {
                _subKey[48 - shiftTable[i] + j] = realKey[56 - shiftTable[i] + j];
                _subKey[48 / 2 - shiftTable[i] + j] = realKey[56 / 2 - shiftTable[i] + j];
            }
            realKey <<= shiftTable[i];
            for (unsigned j = 0; j < shiftTable[i]; ++j)
            {
                realKey[56 / 2 + j] = _subKey[48 - shiftTable[i] + j];
                realKey[j] = _subKey[48 / 2 - shiftTable[i] + j];
            }
        }
        
        // Compress
        const unsigned char compressTable[48] = {
            14, 17, 11, 24, 1, 5, 3, 28,
            15, 6, 21, 10, 23, 19, 12, 4,
            26, 8, 16, 7, 27, 20, 13, 2,
            41, 52, 31, 37, 47, 55, 30, 40,
            51, 45, 33, 48, 44, 49, 39, 56,
            34, 53, 46, 42, 50, 36, 29, 32
        };
        for (unsigned i = 0; i < 48; ++i)
        {
            _subKey[i] = realKey[compressTable[i] - 1];
        }
        
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VDataEncryptionStandard::SubProcess(const std::bitset<48>& _subKey, std::bitset<32>& _left, std::bitset<32>& _right)
    {
        // Expansion
        const unsigned char ExpansionFunctionTable[48] = {
            32, 1, 2, 3, 4, 5,
            4, 5, 6, 7, 8, 9,
            8, 9, 10, 11, 12, 13,
            12, 13, 14, 15, 16, 17,
            16, 17, 18, 19, 20, 21,
            20, 21, 22, 23, 24, 25,
            24, 25, 26, 27, 28, 29,
            28, 29, 30, 31, 32, 1
        };
        std::bitset<48> code;
        for (unsigned i = 0; i < 48; ++i)
        {
            code[i] = _right[ExpansionFunctionTable[i] - 1];
        }
        code ^= _subKey;
        
        // Substitution boxes
        const unsigned char SubstitutionBoxes[8][64]= {
            {
                14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
            },
            {
                15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9
            },
            {
                10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12
            },
            {
                7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14
            },
            {
                2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3
            },
            {
                12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13
            },
            {
                4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12
            },
            {
                13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
            }
        };
        std::bitset<2> rows;
        std::bitset<4> columns;
        for (unsigned i = 0; i < 8; ++i)
        {
            rows[0] = code[6 * i];
            rows[1] = code[6 * i + 5];
            columns[0] = code[6 * i + 1];
            columns[1] = code[6 * i + 2];
            columns[2] = code[6 * i + 3];
            columns[4] = code[6 * i + 4];
            std::bitset<4> temp(SubstitutionBoxes[i][rows.to_ulong() * 16 + columns.to_ulong()]);
            for (unsigned j = 0; j < 4; ++j)
            {
                code[4 * i + j] = temp[j];
            }
        }
        
        // Permutation
        const unsigned char permutationTable[32] = {
            16, 7, 20, 21, 29, 12, 28, 17,
            1, 15, 23, 26, 5, 18, 31, 10,
            2, 8, 24, 14, 32, 27, 3, 9,
            19, 13, 30, 6, 22, 11, 4, 25
        };
        std::bitset<32> subCode;
        for (unsigned i = 0; i < 32; ++i)
        {
            subCode[i] = code[permutationTable[i] - 1];
        }
        _left ^= subCode;
        
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VDataEncryptionStandard::TrimTail(std::string& _code)
    {
        if (mPadding == VDataEncryptionStandardPadding::NoPadding)
        {
            while(_code.size() && _code.back() == '\0')
            {
                _code.pop_back();
            }
        }
        else
        {
            return false;
        }
        return true;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VDataEncryptionStandardTest()
    {
        VDataEncryptionStandard des;
        // auto key = des.Generate();
        des.LoadSecretKey("123abcde");
        auto result = des.Encrypt("I wanna walk on your wavelength");
        result = des.Decrypt(result);
        
        return;
    }
    
}
