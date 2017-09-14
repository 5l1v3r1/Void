#include "VSignal.h"
#include "../../Utility/Logger/VLogger.h"
#include <signal.h>
#include <unistd.h>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VSignalManager
    //----------------------------------------------------------------------------------------------------
    VSmartPointer<VSignalManager> VSignalManager::sInstance = nullptr;
    
    //----------------------------------------------------------------------------------------------------
    void VSignalManager::Bind(int _signal, const std::function<void()>& _handler)
    {
        VSmartPointer<VSignalManager> manager = VSignalManager::Instance();
        manager->mHandler[_signal] = _handler;
        ::signal(_signal, VSignalManager::Callback);
    }
    
    //----------------------------------------------------------------------------------------------------
    VSmartPointer<VSignalManager> VSignalManager::Instance()
    {
        if (!VSignalManager::sInstance)
        {
            VSignalManager::sInstance = new VSignalManager();
        }
        return VSignalManager::sInstance;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VSignalManager::Callback(int _signal)
    {
        VSmartPointer<VSignalManager> manager = VSignalManager::Instance();
        auto it = manager->mHandler.find(_signal);
        if (it != manager->mHandler.end())
        {
            it->second();
        }
    }
    
    //----------------------------------------------------------------------------------------------------
    VSignalManager::VSignalManager()
    {
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VSignalTest()
    {
        int flag = true;
        VSignalManager::Bind(SIGINT, [&]() {
            VLogger::Info("Signal: %d", SIGINT);
            flag = false;
        });
        
        while (flag)
        {
            VLogger::Info("Please type control + c");
            sleep(1);
        }

        return;
    }
    
}
