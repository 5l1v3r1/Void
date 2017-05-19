#pragma once
#ifndef _V_AUDIOMACOSHANDLER_H_
#define _V_AUDIOMACOSHANDLER_H_

#include "../../../VDefine.h"
#if defined(_VOID_ENABLE_COREAUDIO_) && defined(TARGET_OS_MAC)
#define _VOID_USE_COREAUDIO_
#include "../VAudioHandler.h"
#include "../../AudioDevice/VAudioDevice.h"
#include <map>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAudioMacOSHandler
    // OS: MacOS
    // Library: Code Audio
    //----------------------------------------------------------------------------------------------------
    class VAudioMacOSHandler : public VAudioHandler
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VAudioMacOSHandler();
        VAudioMacOSHandler(const VAudioMacOSHandler& _handler);
        virtual ~VAudioMacOSHandler() {};
        
        //----------------------------------------------------------------------------------------------------
        virtual std::map<int, VAudioDevice> LoadDevice();
        virtual int DefaultInputDeviceId();
        virtual int DefaultOutputDeviceId();
        
    protected:
        //----------------------------------------------------------------------------------------------------
        
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VAudioMacOSHandlerTest();
}

#endif
#endif
