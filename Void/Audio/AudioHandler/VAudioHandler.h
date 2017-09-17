#pragma once
#ifndef _V_AUDIOHANDLER_H_
#define _V_AUDIOHANDLER_H_

#include "../../Memory/SmartPointer/VSmartPointer.h"
#include "../AudioDevice/VAudioDevice.h"
#include <map>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    //----------------------------------------------------------------------------------------------------
    class VAudioStream;
    
    // VAudioHandler
    //----------------------------------------------------------------------------------------------------
    class VAudioHandler
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static VSharePointer<VAudioHandler> Instance();
        
    public:
        //----------------------------------------------------------------------------------------------------
        virtual ~VAudioHandler() {};
        
        //----------------------------------------------------------------------------------------------------
        virtual std::map<int, VAudioDevice> LoadDevice() = 0;
        virtual int DefaultInputDeviceId() = 0;
        virtual int DefaultOutputDeviceId() = 0;
        virtual bool Open(VAudioStream& _stream) = 0;
        virtual bool Start(VAudioStream& _stream) = 0;
        
    protected:
        //----------------------------------------------------------------------------------------------------
        
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VAudioHandlerTest();
}

#endif
