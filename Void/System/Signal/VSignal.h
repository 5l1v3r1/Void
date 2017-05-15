#pragma once
#ifndef _V_SIGNAL_H_
#define _V_SIGNAL_H_

#include "../../Memory/SmartPtr/VSmartPtr.h"
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
        static VSmartPtr<VSignalManager> Instance();
        static void Callback(int _signal);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        static VSmartPtr<VSignalManager> sInstance;
        
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
