#pragma once
#ifndef _V_SOUNDEX_H_
#define _V_SOUNDEX_H_

#include <string>
#include <map>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VSoundex
    // 0: a e h i o u w y
    // 1: b f p v
    // 2: c g j k q s x z
    // 3: d t
    // 4: l
    // 5: m n
    // 6: r
    //----------------------------------------------------------------------------------------------------
    class VSoundex
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VSoundex();
        virtual ~VSoundex();
        
        //----------------------------------------------------------------------------------------------------
        std::string Encode(const std::string& _content);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        void Initialize();
        char Encode(char _character);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::map<char, char> mCodingTable;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VSoundexTest();
}

#endif