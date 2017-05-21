#include "VAudioDeviceManager.h"
#include "../AudioHandler/VAudioHandler.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAudioDeviceManager
    //----------------------------------------------------------------------------------------------------
    VAudioDeviceManager::VAudioDeviceManager()
        :
        mDevices(),
        mDefaultInputDeviceId(-1),
        mDefaultOutputDeviceId(-1)
    {
        Initialize();
    }
    
    //----------------------------------------------------------------------------------------------------
    VAudioDeviceManager::VAudioDeviceManager(const VAudioDeviceManager& _manager)
        :
        mDevices(_manager.mDevices),
        mDefaultInputDeviceId(_manager.mDefaultInputDeviceId),
        mDefaultOutputDeviceId(_manager.mDefaultOutputDeviceId)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VAudioDeviceManager::~VAudioDeviceManager()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    unsigned long VAudioDeviceManager::Count() const
    {
        return mDevices.size();
    }
    
    //----------------------------------------------------------------------------------------------------
    VAudioDevice VAudioDeviceManager::Device(int _deviceId) const
    {
        auto it = mDevices.find(_deviceId);
        if (it != mDevices.end())
        {
            return it->second;
        }
        return VAudioDevice();
    }
    
    //----------------------------------------------------------------------------------------------------
    VAudioDevice VAudioDeviceManager::DefaultInputDevice() const
    {
        return Device(mDefaultInputDeviceId);
    }
    
    //----------------------------------------------------------------------------------------------------
    VAudioDevice VAudioDeviceManager::DefaultOutputDevice() const
    {
        return Device(mDefaultOutputDeviceId);
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VAudioDeviceManager::Initialize()
    {
        auto handler = VAudioHandler::Instance();
        if (handler)
        {
            mDevices = handler->LoadDevice();
            mDefaultInputDeviceId = handler->DefaultInputDeviceId();
            mDefaultOutputDeviceId = handler->DefaultOutputDeviceId();
            return true;
        }
        
        return false;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VAudioDeviceManagerTest()
    {
        VAudioDeviceManager manager;
        
        
        return;
    }
    
}
