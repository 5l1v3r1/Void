#include "VBase58.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VBase58
    //----------------------------------------------------------------------------------------------------
    VBase58::VBase58(VBase58Alphabet _alphabet)
        :
        mAlphabet()
    {
        LoadAlphabet(_alphabet);
    }
    
    //----------------------------------------------------------------------------------------------------
    std::string VBase58::Encode(unsigned long long _target)
    {
        std::string result;
        while (0 < _target)
        {
            unsigned remainder = _target % 58;
            result.push_back(mAlphabet[remainder]);
            _target /= 58;
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
    
    //----------------------------------------------------------------------------------------------------
    unsigned long long VBase58::Decode(const std::string& _target)
    {
        unsigned long long result = 0;
        for (unsigned i = 0; i < _target.length(); ++i)
        {
            result *= 58;
            result += mAlphabetMap[_target[i]];
        }
        return result;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VBase58::LoadAlphabet(VBase58Alphabet _alphabet)
    {
        switch (_alphabet) {
            case VBase58Alphabet::DEFAULT:
                mAlphabet = "123456789abcdefghijkmnopqrstuvwxyzABCDEFGHJKLMNPQRSTUVWXYZ";
                break;
            case VBase58Alphabet::BITCOIN:
                mAlphabet = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
                break;
            case VBase58Alphabet::RIPPLE:
                mAlphabet = "rpshnaf39wBUDNEGHJKLM4PQRST7VWXYZ2bcdeCg65jkm8oFqi1tuvAxyz";
                break;
            default:
                mAlphabet = "123456789abcdefghijkmnopqrstuvwxyzABCDEFGHJKLMNPQRSTUVWXYZ";
                break;
        }
        mAlphabetMap.clear();
        for (int i = 0; i < mAlphabet.length(); ++i) {
            mAlphabetMap[mAlphabet[i]] = i;
        }
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VBase58Test()
    {
        VBase58 base58;
        auto code = base58.Encode(1234567);
        auto decode = base58.Decode(code);
        code = base58.Encode(0);
        decode = base58.Decode(code);
        code = base58.Encode(1111);
        decode = base58.Decode(code);
        
        return;
    }
    
}
