#pragma once
#ifndef _V_AUDIOBASE_H_
#define _V_AUDIOBASE_H_

#include "../../Memory/SmartPointer/VSmartPointer.h"
#include "./AudioFormat/VAudioFormat.h"
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAudioBase
    //----------------------------------------------------------------------------------------------------
    class VAudioBase
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VAudioBase();
        VAudioBase(const VAudioFormat& _format);
        VAudioBase(const VAudioBase& _base);
        virtual ~VAudioBase();
        
        //----------------------------------------------------------------------------------------------------
        const VAudioFormat& Format() const;
        VSharePointer<std::vector<char>>& Data();
        const VSharePointer<std::vector<char>>& Data() const;
        char* Block(const unsigned long& _originIndex, const unsigned long& _length=0);
        const char* Block(const unsigned long& _originIndex, const unsigned long& _length=0) const;
        
        //----------------------------------------------------------------------------------------------------
        unsigned long BlockCount() const;
        float DurationSeconds() const;
        
    protected:
        //----------------------------------------------------------------------------------------------------
        VAudioFormat mFormat;
        VSharePointer<std::vector<char>> mData;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VAudioBaseTest();
}

#endif
