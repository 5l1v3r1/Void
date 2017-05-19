#pragma once
#ifndef _V_AUDIODEVICE_H_
#define _V_AUDIODEVICE_H_

#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAudioDevice
    //----------------------------------------------------------------------------------------------------
    class VAudioDevice
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VAudioDevice()
            :
            deviceId(-1),
            deviceName(),
            sampleRate(0),
            maxInputChannels(0),
            maxOutputChannels(0),
            frameLatency(0)
        {
        }
        
        VAudioDevice(const VAudioDevice& _device)
            :
            deviceId(_device.deviceId),
            deviceName(_device.deviceName),
            sampleRate(_device.sampleRate),
            maxInputChannels(_device.maxInputChannels),
            maxOutputChannels(_device.maxOutputChannels),
            frameLatency(_device.frameLatency)
        {
        }
        
        ~VAudioDevice()
        {
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        int deviceId;
        std::string deviceName;
        double sampleRate;
        int maxInputChannels;
        int maxOutputChannels;
        int frameLatency;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VAudioDeviceTest();
}

#endif
