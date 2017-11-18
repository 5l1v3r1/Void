#include "VAudioStream.h"
#include "../AudioDevice/VAudioDeviceManager.h"
#include "../../Utility/Logger/VLogger.h"
#include <unistd.h>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAudioStream
    //----------------------------------------------------------------------------------------------------
    VAudioStream::VAudioStream()
        :
        mType(VAudioStreamType::Output),
        mStatus(VAudioStreamStatus::Default)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VAudioStream::~VAudioStream()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VAudioStreamStatus VAudioStream::Status() const
    {
        return mStatus;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VAudioStream::IsInputEnabled() const
    {
        return mType == VAudioStreamType::IO || mType == VAudioStreamType::Input;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VAudioStream::IsOutputEnabled() const
    {
        return mType == VAudioStreamType::IO || mType == VAudioStreamType::Output;
    }
    
    //----------------------------------------------------------------------------------------------------
    VAudioDevice& VAudioStream::Device()
    {
        return mDevice;
    }
    
    //----------------------------------------------------------------------------------------------------
    VAudioFormat& VAudioStream::InputFormat()
    {
        return mInputFormat;
    }
    
    //----------------------------------------------------------------------------------------------------
    VAudioFormat& VAudioStream::OutputFormat()
    {
        return mOutputFormat;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VAudioStream::Open(const VAudioDevice& _device)
    {
        auto handler = VAudioHandler::Instance();
        if (handler)
        {
            mHandle = handler;
            mDevice = _device;
            if (mHandle->Open(*this))
            {
                mStatus = VAudioStreamStatus::Opened;
            }
            return true;
        }
        return false;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VAudioStream::Start()
    {
        if (mHandle)
        {
            if (mHandle->Start(*this))
            {
                return true;
            }
        }
        return false;
    }
    
    //----------------------------------------------------------------------------------------------------
    VAudioStreamStatus VAudioStream::InputCallback(const void* _input, unsigned long _frameCount)
    {
        
        
        return VAudioStreamStatus::NoError;
    }
    
    //----------------------------------------------------------------------------------------------------
    VAudioStreamStatus VAudioStream::OutputCallback(void* _output, unsigned long _frameCount)
    {
        
        
        return VAudioStreamStatus::NoError;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VAudioStreamTest()
    {
        VAudioDeviceManager manager;
        VAudioStream stream;
        stream.Open(manager.DefaultOutputDevice());
        stream.Start();
        sleep(1000);
        
        return;
    }
    
}
