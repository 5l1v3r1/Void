#pragma once
#ifndef _V_SIGNAL_H_
#define _V_SIGNAL_H_

#include "../../Memory/SmartPointer/VSmartPointer.h"
#include <map>
#include <functional>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VSignalManager
    //----------------------------------------------------------------------------------------------------
    class VSignalManager
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static void Bind(int _signal, const std::function<void()>& _handler);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        static VSmartPointer<VSignalManager> Instance();
        static void Callback(int _signal);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        static VSmartPointer<VSignalManager> sInstance;
        
    protected:
        //----------------------------------------------------------------------------------------------------
        VSignalManager();
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::map<int, std::function<void()>> mHandler;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VSignalTest();
}

#endif
