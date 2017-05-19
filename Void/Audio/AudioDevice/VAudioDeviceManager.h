#pragma once
#ifndef _V_AUDIODEVICEMANAGER_H_
#define _V_AUDIODEVICEMANAGER_H_

#include "VAudioDevice.h"
#include <map>
#include <vector>
#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAudioDeviceManager
    //----------------------------------------------------------------------------------------------------
    class VAudioDeviceManager
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VAudioDeviceManager();
        VAudioDeviceManager(const VAudioDeviceManager& _manager);
        ~VAudioDeviceManager();
        
        //----------------------------------------------------------------------------------------------------
        unsigned long Count() const;
        VAudioDevice Device(int _deviceId) const;
        VAudioDevice DefaultInputDevice() const;
        VAudioDevice DefaultOutputDevice() const;
        
        //----------------------------------------------------------------------------------------------------
        bool SetSampleRate();
        
    protected:
        //----------------------------------------------------------------------------------------------------
        bool Initialize();
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::map<int, VAudioDevice> mDevices;
        int mDefaultInputDeviceId;
        int mDefaultOutputDeviceId;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VAudioDeviceManagerTest();
}

#endif
