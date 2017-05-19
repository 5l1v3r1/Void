#pragma once
#ifndef _V_AUDIOHANDLER_H_
#define _V_AUDIOHANDLER_H_

#include "../../Memory/SmartPtr/VSmartPtr.h"
#include "../AudioDevice/VAudioDevice.h"
#include <map>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAudioHandler
    //----------------------------------------------------------------------------------------------------
    class VAudioHandler
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static VSmartPtr<VAudioHandler> Instance();
        
    public:
        //----------------------------------------------------------------------------------------------------
        virtual ~VAudioHandler() {};
        
        //----------------------------------------------------------------------------------------------------
        virtual std::map<int, VAudioDevice> LoadDevice() = 0;
        virtual int DefaultInputDeviceId() = 0;
        virtual int DefaultOutputDeviceId() = 0;
        
    protected:
        //----------------------------------------------------------------------------------------------------
        
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VAudioHandlerTest();
}

#endif
