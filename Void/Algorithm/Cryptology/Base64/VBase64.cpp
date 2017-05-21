#include "VBase64.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VBase64
    //----------------------------------------------------------------------------------------------------
    VBase64::VBase64()
        :
        mAlphabet()
    {
        LoadAlphabet();
    }
    
    //----------------------------------------------------------------------------------------------------
    std::string VBase64::Encode(const std::string& _target)
    {
        std::string result;
        result.reserve((_target.length() + 2 - ((_target.length() + 2) % 3)) / 3 * 4);
        
        // 3n
        unsigned long i = 0;
        for (; i + 2 < _target.length(); i += 3) {
            std::string pack = Bit8ToBit6(_target[i], _target[i + 1], _target[i + 2]);
            for (char part : pack)
            {
                result.push_back(mAlphabet[part]);
            }
        }
        // length - 3n
        unsigned long remainder = _target.length() - i;
        if (remainder == 2)
        {
            std::string pack = Bit8ToBit6(_target[i], _target[i + 1], '\0');
            result.push_back(mAlphabet[pack[0]]);
            result.push_back(mAlphabet[pack[1]]);
            result.push_back(mAlphabet[pack[2]]);
            result.push_back('=');
        } else if (remainder == 1)
        {
            std::string pack = Bit8ToBit6(_target[i], '\0', '\0');
            result.push_back(mAlphabet[pack[0]]);
            result.push_back(mAlphabet[pack[1]]);
            result.push_back('=');
            result.push_back('=');
        }
        
        return result;
    }
    
    //----------------------------------------------------------------------------------------------------
    std::string VBase64::Decode(const std::string& _target)
    {
        std::string result;
        unsigned redundancy = 0;
        for (std::string::const_reverse_iterator it = _target.rbegin(); *it == '='; ++it, ++redundancy);
        result.reserve(_target.length() / 4 * 3 - redundancy);
        
        // 4n or 4n - 4
        unsigned long i = 0;
        for (; i + 3 < _target.length() - redundancy; i += 4) {
            std::string pack = Bit6ToBit8(mAlphabetMap[_target[i]], mAlphabetMap[_target[i + 1]], mAlphabetMap[_target[i + 2]], mAlphabetMap[_target[i + 3]]);
            for (char part : pack)
            {
                result.push_back(part);
            }
        }
        // 4 - redundancy if redundancy
        if (redundancy == 2)
        {
            std::string pack = Bit6ToBit8(mAlphabetMap[_target[i]], mAlphabetMap[_target[i + 1]], '\0', '\0');
            result.push_back(pack[0]);
        }
        else if (redundancy == 1)
        {
            std::string pack = Bit6ToBit8(mAlphabetMap[_target[i]], mAlphabetMap[_target[i + 1]], mAlphabetMap[_target[i + 2]], '\0');
            result.push_back(pack[0]);
            result.push_back(pack[1]);
        }
        else
        {
            
        }
        
        return result;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VBase64::LoadAlphabet()
    {
        mAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        mAlphabetMap.clear();
        for (unsigned int i = 0; i < mAlphabet.length(); ++i) {
            mAlphabetMap[mAlphabet[i]] = i;
        }
    }
    
    //----------------------------------------------------------------------------------------------------
    std::string VBase64::Bit8ToBit6(char _a, char _b, char _c)
    {
        std::string result;
        result.resize(4);
        result[0] = (_a & 0xfc) >> 2;
        result[1] = ((_a & 0x03) << 4) + ((_b & 0xf0) >> 4);
        result[2] = ((_b & 0x0f) << 2) + ((_c & 0xc0) >> 6);
        result[3] = (_c & 0x3f);
        return result;
    }
    
    //----------------------------------------------------------------------------------------------------
    std::string VBase64::Bit6ToBit8(char _a, char _b, char _c, char _d)
    {
        std::string result;
        result.resize(3);
        result[0] = (_a << 2) + ((_b & 0x30) >> 4);
        result[1] = ((_b & 0xf) << 4) + ((_c & 0x3c) >> 2);
        result[2] = ((_c & 0x3) << 6) + _d;
        return result;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VBase64Test()
    {
        VBase64 base64;
        std::string code = base64.Encode("hi");
        code = base64.Decode(code);
        code = base64.Encode("hello");
        code = base64.Decode(code);
        code = base64.Encode("");
        code = base64.Decode(code);
        code = base64.Encode("123456");
        code = base64.Decode(code);
        code = base64.Encode("1234567");
        code = base64.Decode(code);
        code = base64.Encode("\xff\x01\xaa");
        code = base64.Decode(code);
        code = base64.Encode("S\x9c\345");
        code = base64.Decode(code);
        
        return;
    }
    
}
