#pragma once
#ifndef _V_AUDIOSTREAM_H_
#define _V_AUDIOSTREAM_H_

#include "../AudioDevice/VAudioDevice.h"
#include "../AudioBase/AudioFormat/VAudioFormat.h"
#include "../AudioHandler/VAudioHandler.h"
#include <functional>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAudioStreamType
    //----------------------------------------------------------------------------------------------------
    enum class VAudioStreamType
    {
        IO = 0,
        Input,
        Output,
    };
    
    // VAudioStreamStatus
    //----------------------------------------------------------------------------------------------------
    enum class VAudioStreamStatus
    {
        NoError = 0,
        
        Default,
        Opened,
        Playing,
        NoBuffer,
        Paused,
        Finished,
    };
    
    // VAudioStream
    //----------------------------------------------------------------------------------------------------
    class VAudioStream
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VAudioStream();
        ~VAudioStream();
        
        //----------------------------------------------------------------------------------------------------
        VAudioStreamStatus Status() const;
        bool IsInputEnabled() const;
        bool IsOutputEnabled() const;
        VAudioDevice& Device();
        VAudioFormat& InputFormat();
        VAudioFormat& OutputFormat();
        
        //----------------------------------------------------------------------------------------------------
        bool Open(const VAudioDevice& _device);
        bool Start();
        
        //----------------------------------------------------------------------------------------------------
        VAudioStreamStatus InputCallback(const void* _input, unsigned long _frameCount);
        VAudioStreamStatus OutputCallback(void* _output, unsigned long _frameCount);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        VSharePointer<VAudioHandler> mHandle;
        VAudioStreamType mType;
        VAudioStreamStatus mStatus;
        VAudioDevice mDevice;
        VAudioFormat mInputFormat;
        VAudioFormat mOutputFormat;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VAudioStreamTest();
}

#endif
