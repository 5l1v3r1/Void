#pragma once
#ifndef _V_AUDIOMACOSHANDLER_H_
#define _V_AUDIOMACOSHANDLER_H_

#include "../../../VDefine.h"
#if defined(_VOID_ENABLE_COREAUDIO_) && defined(_VOID_MACOS_)
#define _VOID_USE_COREAUDIO_
#include "../VAudioHandler.h"
#include "../../AudioDevice/VAudioDevice.h"
#include "../../AudioStream/VAudioStream.h"
#include <CoreAudio/CoreAudio.h>
#include <CoreServices/CoreServices.h>
#include <AudioToolbox/AudioToolbox.h>
#include <AudioUnit/AudioUnit.h>
#include <libkern/OSAtomic.h>
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
    protected:
        //----------------------------------------------------------------------------------------------------
        static OSStatus AudioIOProcCallback(AudioDeviceID _inDevice, const AudioTimeStamp* _inNow, const AudioBufferList* _inInputData, const AudioTimeStamp* _inInputTime, AudioBufferList* _outOutputData, const AudioTimeStamp* _inOutputTime, void* _inClientData);
        static OSStatus AudioRenderCallback(void* _inRefCon, AudioUnitRenderActionFlags* _ioActionFlags, const AudioTimeStamp* _inTimeStamp, UInt32 _inBusNumber, UInt32 _inNumberFrames, AudioBufferList* __nullable _ioData);
        
    public:
        //----------------------------------------------------------------------------------------------------
        VAudioMacOSHandler();
        VAudioMacOSHandler(const VAudioMacOSHandler& _handler);
        virtual ~VAudioMacOSHandler() {};
        
        //----------------------------------------------------------------------------------------------------
        virtual std::map<int, VAudioDevice> LoadDevice();
        virtual int DefaultInputDeviceId();
        virtual int DefaultOutputDeviceId();
        virtual bool Open(VAudioStream& _stream);
        virtual bool Start(VAudioStream& _stream);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        
        
    protected:
        //----------------------------------------------------------------------------------------------------
        AudioUnit mAudioUnit;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VAudioMacOSHandlerTest();
}

#endif
#endif
