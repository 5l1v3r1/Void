#include "VAudioMacOSHandler.h"
#ifdef _VOID_USE_COREAUDIO_
#include "../../../Utility/Logger/VLogger.h"
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAudioMacOSHandler
    //----------------------------------------------------------------------------------------------------
    OSStatus VAudioMacOSHandler::AudioIOProcCallback(AudioDeviceID _inDevice, const AudioTimeStamp* _inNow, const AudioBufferList* _inInputData, const AudioTimeStamp* _inInputTime, AudioBufferList* _outOutputData, const AudioTimeStamp* _inOutputTime, void* _inClientData)
    {
        VAudioStream *stream = (VAudioStream*)_inClientData;
        
        // Input
        if (stream->IsInputEnabled())
        {
            
        }
        // Output
        if (stream->IsOutputEnabled())
        {
            // AudioBuffer *outputBuffer = &_outOutputData->mBuffers[0];
            // unsigned long frameCount = outputBuffer->mDataByteSize / (outputBuffer->mNumberChannels * sizeof(Float32)); // Float32 format
        }
        
        return kAudioHardwareNoError;
    }
    
    //----------------------------------------------------------------------------------------------------
    OSStatus VAudioMacOSHandler::AudioRenderCallback(void* _inRefCon, AudioUnitRenderActionFlags* _ioActionFlags, const AudioTimeStamp* _inTimeStamp, UInt32 _inBusNumber, UInt32 _inNumberFrames, AudioBufferList* __nullable _ioData)
    {
        VAudioStream *stream = (VAudioStream*)_inRefCon;
        
        // Output
        if (stream->IsOutputEnabled())
        {
            VAudioFormat format = stream->OutputFormat();
            std::vector<char> data(format.bitsPerSample * format.channels / 8 * _inNumberFrames);
            stream->OutputCallback(data.data(), _inNumberFrames);
        }
        
        return kAudioHardwareNoError;
    }
    
    //----------------------------------------------------------------------------------------------------
    VAudioMacOSHandler::VAudioMacOSHandler()
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    VAudioMacOSHandler::VAudioMacOSHandler(const VAudioMacOSHandler& _handler)
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    std::map<int, VAudioDevice> VAudioMacOSHandler::LoadDevice()
    {
        #ifdef __MAC_10_0
        std::map<int, VAudioDevice> result;
        AudioObjectPropertyAddress address = { kAudioHardwarePropertyDevices, kAudioObjectPropertyScopeGlobal, kAudioObjectPropertyElementMaster };
        UInt32 size(0);
        if (AudioObjectGetPropertyDataSize(kAudioObjectSystemObject, &address, 0, nullptr, &size) != kAudioHardwareNoError) { return std::map<int, VAudioDevice>(); };
        int deviceCount = size / sizeof(AudioDeviceID);
        if (deviceCount)
        {
            // DeviceIds
            std::vector<AudioDeviceID> deviceIds(deviceCount);
            if (AudioObjectGetPropertyData(kAudioObjectSystemObject, &address, 0, nullptr, &size, deviceIds.data()) != kAudioHardwareNoError) { return std::map<int, VAudioDevice>(); };
            for (int i = 0; i < deviceCount; ++i)
            {
                VAudioDevice device;
                // Device id
                device.deviceId = deviceIds[i];
                // Device name
                address.mSelector = kAudioDevicePropertyDeviceName;
                if (AudioObjectGetPropertyDataSize(device.deviceId, &address, 0, nullptr, &size) == kAudioHardwareNoError)
                {
                    device.deviceName.resize(size);
                    AudioObjectGetPropertyData(device.deviceId, &address, 0, nullptr, &size, (void*)device.deviceName.data());
                }
                // Sample rate
                size = sizeof(Float64);
                address.mSelector = kAudioDevicePropertyNominalSampleRate;
                AudioObjectGetPropertyData(device.deviceId, &address, 0, nullptr, &size, &device.sampleRate);
                // Channels
                address = { kAudioDevicePropertyStreamConfiguration, kAudioDevicePropertyScopeInput };
                if (AudioObjectGetPropertyDataSize(device.deviceId, &address, 0, nullptr, &size) == kAudioHardwareNoError)
                {
                    std::vector<AudioBufferList> bufferList(size / sizeof(AudioBufferList) + 1);
                    if (AudioObjectGetPropertyData(device.deviceId, &address, 0, nullptr, &size, bufferList.data()) == kAudioHardwareNoError)
                    {
                        for (UInt32 i = 0; i < bufferList[0].mNumberBuffers; ++i)
                        {
                            device.maxInputChannels += bufferList[0].mBuffers[i].mNumberChannels;
                        }
                    }
                }
                address = { kAudioDevicePropertyStreamConfiguration, kAudioDevicePropertyScopeOutput };
                if (AudioObjectGetPropertyDataSize(device.deviceId, &address, 0, nullptr, &size) == kAudioHardwareNoError)
                {
                    std::vector<AudioBufferList> bufferList(size / sizeof(AudioBufferList) == 0 ? 1 : size / sizeof(AudioBufferList));
                    if (AudioObjectGetPropertyData(device.deviceId, &address, 0, nullptr, &size, bufferList.data()) == kAudioHardwareNoError)
                    {
                        for (UInt32 i = 0; i < bufferList[0].mNumberBuffers; ++i)
                        {
                            device.maxOutputChannels += bufferList[0].mBuffers[i].mNumberChannels;
                        }
                    }
                }
                // Frame latency
                size = sizeof(UInt32);
                address = { kAudioDevicePropertyLatency, kAudioDevicePropertyScopeInput };
                AudioObjectGetPropertyData(device.deviceId, &address, 0, nullptr, &size, &device.frameLatency);
                address = { kAudioDevicePropertyLatency, kAudioDevicePropertyScopeOutput };
                AudioObjectGetPropertyData(device.deviceId, &address, 0, nullptr, &size, &device.frameLatency);
                // Push
                result[device.deviceId] = device;
            }
        }
        return result;
        #else
        #pragma clang diagnostic push
        #pragma clang diagnostic ignored "-Wdeprecated-declarations"
        std::map<int, VAudioDevice> result;
        UInt32 size(0);
        if (AudioHardwareGetPropertyInfo(kAudioHardwarePropertyDevices, &size, nullptr) != kAudioHardwareNoError) { return std::map<int, VAudioDevice>(); };
        int deviceCount = size / sizeof(AudioDeviceID);
        if (deviceCount)
        {
            // DeviceIds
            std::vector<AudioDeviceID> deviceIds(deviceCount);
            if (AudioHardwareGetProperty(kAudioHardwarePropertyDevices, &size, deviceIds.data()) != kAudioHardwareNoError) { return std::map<int, VAudioDevice>(); };
            for (int i = 0; i < deviceCount; ++i)
            {
                VAudioDevice device;
                // Device id
                device.deviceId = deviceIds[i];
                // Device name
                if (AudioDeviceGetPropertyInfo(device.deviceId, 0, 0, kAudioDevicePropertyDeviceName, &size, nullptr) == kAudioHardwareNoError)
                {
                    device.deviceName.resize(size);
                    AudioDeviceGetProperty(device.deviceId, 0, 0, kAudioDevicePropertyDeviceName, &size, (void*)device.deviceName.data());
                }
                // Sample rate
                size = sizeof(Float64);
                AudioDeviceGetProperty(device.deviceId, 0, 0, kAudioDevicePropertyNominalSampleRate, &size, &device.sampleRate);
                // Channels
                if (AudioDeviceGetPropertyInfo(device.deviceId, 0, 1, kAudioDevicePropertyStreamConfiguration, &size, nullptr) == kAudioHardwareNoError)
                {
                    std::vector<AudioBufferList> bufferList(size / sizeof(AudioBufferList) + 1);
                    if (AudioDeviceGetProperty(device.deviceId, 0, 1, kAudioDevicePropertyStreamConfiguration, &size, bufferList.data()) == kAudioHardwareNoError)
                    {
                        for (UInt32 i = 0; i < bufferList[0].mNumberBuffers; ++i)
                        {
                            device.maxInputChannels += bufferList[0].mBuffers[i].mNumberChannels;
                        }
                    }
                }
                if (AudioDeviceGetPropertyInfo(device.deviceId, 0, 0, kAudioDevicePropertyStreamConfiguration, &size, nullptr) == kAudioHardwareNoError)
                {
                    std::vector<AudioBufferList> bufferList(size / sizeof(AudioBufferList) == 0 ? 1 : size / sizeof(AudioBufferList));
                    if (AudioDeviceGetProperty(device.deviceId, 0, 0, kAudioDevicePropertyStreamConfiguration, &size, bufferList.data()) == kAudioHardwareNoError)
                    {
                        for (UInt32 i = 0; i < bufferList[0].mNumberBuffers; ++i)
                        {
                            device.maxOutputChannels += bufferList[0].mBuffers[i].mNumberChannels;
                        }
                    }
                }
                // Frame latency
                size = sizeof(UInt32);
                AudioDeviceGetProperty(device.deviceId, 0, 1, kAudioDevicePropertyLatency, &size, &device.frameLatency);
                AudioDeviceGetProperty(device.deviceId, 0, 0, kAudioDevicePropertyLatency, &size, &device.frameLatency);
                // Push
                result[device.deviceId] = device;
            }
        }
        return result;
        #pragma clang diagnostic pop
        #endif
        return std::map<int, VAudioDevice>();
    }
    
    //----------------------------------------------------------------------------------------------------
    int VAudioMacOSHandler::DefaultInputDeviceId()
    {
        #ifdef __MAC_10_0
        AudioObjectPropertyAddress address = { kAudioHardwarePropertyDefaultInputDevice, kAudioObjectPropertyScopeGlobal, kAudioObjectPropertyElementMaster };
        UInt32 size = sizeof(AudioDeviceID);
        AudioDeviceID result;
        if (AudioObjectGetPropertyData(kAudioObjectSystemObject, &address, 0, nullptr, &size, &result) == kAudioHardwareNoError)
        {
            return result;
        }
        #else
        UInt32 size = sizeof(AudioDeviceID);
        AudioDeviceID result;
        if (AudioHardwareGetProperty(kAudioHardwarePropertyDefaultInputDevice, &size, &result) == kAudioHardwareNoError)
        {
            return result;
        }
        #endif
        return -1;
    }
    
    //----------------------------------------------------------------------------------------------------
    int VAudioMacOSHandler::DefaultOutputDeviceId()
    {
        #ifdef __MAC_10_0
        AudioObjectPropertyAddress address = { kAudioHardwarePropertyDefaultOutputDevice, kAudioObjectPropertyScopeGlobal, kAudioObjectPropertyElementMaster };
        UInt32 size = sizeof(AudioDeviceID);
        AudioDeviceID result;
        if (AudioObjectGetPropertyData(kAudioObjectSystemObject, &address, 0, nullptr, &size, &result) == kAudioHardwareNoError)
        {
            return result;
        }
        #else
        UInt32 size = sizeof(AudioDeviceID);
        AudioDeviceID result;
        if (AudioHardwareGetProperty(kAudioHardwarePropertyDefaultOutputDevice, &size, &result) == kAudioHardwareNoError)
        {
            return result;
        }
        #endif
        return -1;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VAudioMacOSHandler::Open(VAudioStream& _stream)
    {
        #ifdef __MAC_10_0
        // Component description
        AudioComponentDescription description;
        description.componentType = kAudioUnitType_Output;
        description.componentSubType = kAudioUnitSubType_HALOutput;
        description.componentManufacturer = kAudioUnitManufacturer_Apple;
        description.componentFlags = 0;
        description.componentFlagsMask = 0;
        // Component
        AudioComponent component = AudioComponentFindNext(nullptr, &description);
        if (!component)
        {
            return false;
        }
        // Open
        if (AudioComponentInstanceNew(component, &mAudioUnit) != kAudioHardwareNoError)
        {
            mAudioUnit = nullptr;
            return false;
        }
        // Enable input && disable output if needed
        if (_stream.IsInputEnabled())
        {
            UInt32 enableIO = 1;
            if (AudioUnitSetProperty(mAudioUnit, kAudioOutputUnitProperty_EnableIO, kAudioUnitScope_Input, 1, &enableIO, sizeof(enableIO)) != kAudioHardwareNoError)
            {
                return false;
            }
        }
        if (!_stream.IsOutputEnabled())
        {
            UInt32 enableIO = 1;
            if (AudioUnitSetProperty(mAudioUnit, kAudioOutputUnitProperty_EnableIO, kAudioUnitScope_Output, 0, &enableIO, sizeof(enableIO)) != kAudioHardwareNoError)
            {
                return false;
            }
        }
        // Set Device
        AudioDeviceID deviceId = _stream.Device().deviceId;
        if (_stream.IsInputEnabled())
        {
            if (AudioUnitSetProperty(mAudioUnit, kAudioOutputUnitProperty_CurrentDevice, kAudioUnitScope_Global, 1, &deviceId, sizeof(deviceId)) != kAudioHardwareNoError)
            {
                return false;
            }
        }
        if (_stream.IsOutputEnabled())
        {
            if (AudioUnitSetProperty(mAudioUnit, kAudioOutputUnitProperty_CurrentDevice, kAudioUnitScope_Global, 0, &deviceId, sizeof(deviceId)) != kAudioHardwareNoError)
            {
                return false;
            }
        }
        // Add listener for dropouts
        // OSStatus status = AudioDeviceAddPropertyListener(deviceId, 0, _stream.IsOutputEnabled() ? false : true, kAudioDeviceProcessorOverload, nullptr, nullptr);
        // if (status != kAudioHardwareNoError || status != kAudioHardwareIllegalOperationError)
        // {
        //     return false;
        // }
        // Add listener for stream start and stop
        // if (AudioUnitAddPropertyListener(mAudioUnit, kAudioOutputUnitProperty_IsRunning, nullptr, nullptr) != kAudioHardwareNoError);
        // {
        //     return false;
        // }
        // Set input conversion
        //
        // Set output conversion quality
        if (_stream.IsOutputEnabled())
        {
            UInt32 quality = kAudioConverterQuality_Max; // Option
            if (AudioUnitSetProperty(mAudioUnit, kAudioUnitProperty_RenderQuality, kAudioUnitScope_Global, 0, &quality, sizeof(quality)) != kAudioHardwareNoError)
            {
                return false;
            }
        }
        // Set format
        AudioStreamBasicDescription targetFormat;
        targetFormat.mFormatID = kAudioFormatLinearPCM;
        targetFormat.mFormatFlags = kAudioFormatFlagsNativeFloatPacked;
        targetFormat.mReserved = 0;
        if (_stream.IsInputEnabled())
        {
            // AudioStreamBasicDescription currentFormat;
            // UInt32 size = sizeof(AudioStreamBasicDescription);
            // if (AudioUnitGetProperty(mAudioUnit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, 1, &currentFormat, &size) != kAudioHardwareNoError)
            // {
            //     return false;
            // }
            VAudioFormat format = _stream.InputFormat();
            targetFormat.mSampleRate = format.samplesPerSecond;
            targetFormat.mChannelsPerFrame = format.channels;
            targetFormat.mBitsPerChannel = format.bitsPerSample;
            targetFormat.mBytesPerFrame = targetFormat.mBitsPerChannel * targetFormat.mChannelsPerFrame / 8;
            targetFormat.mFramesPerPacket = 1;
            targetFormat.mBytesPerPacket = targetFormat.mBytesPerFrame * targetFormat.mFramesPerPacket;
            if (AudioUnitSetProperty(mAudioUnit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Output, 1, &targetFormat, sizeof(targetFormat)) != kAudioHardwareNoError)
            {
                return false;
            }
        }
        if (_stream.IsOutputEnabled())
        {
            VAudioFormat format = _stream.OutputFormat();
            targetFormat.mSampleRate = format.samplesPerSecond;
            targetFormat.mChannelsPerFrame = format.channels;
            targetFormat.mBitsPerChannel = format.bitsPerSample;
            targetFormat.mBytesPerFrame = targetFormat.mBitsPerChannel * targetFormat.mChannelsPerFrame / 8;
            targetFormat.mFramesPerPacket = 1;
            targetFormat.mBytesPerPacket = targetFormat.mBytesPerFrame * targetFormat.mFramesPerPacket;
            if (AudioUnitSetProperty(mAudioUnit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, 0, &targetFormat, sizeof(targetFormat)) != kAudioHardwareNoError)
            {
                return false;
            }
        }
        // Set frames per buffer and slice
        //
        // Render callback
        if (_stream.IsInputEnabled())
        {
            AURenderCallbackStruct callbackStruct;
            callbackStruct.inputProc = VAudioMacOSHandler::AudioRenderCallback;
            callbackStruct.inputProcRefCon = &_stream;
            if (AudioUnitSetProperty(mAudioUnit, kAudioOutputUnitProperty_SetInputCallback, kAudioUnitScope_Global, 1, &callbackStruct, sizeof(callbackStruct)) != kAudioHardwareNoError)
            {
                return false;
            }
        }
        if (_stream.IsOutputEnabled())
        {
            AURenderCallbackStruct callbackStruct;
            callbackStruct.inputProc = VAudioMacOSHandler::AudioRenderCallback;
            callbackStruct.inputProcRefCon = &_stream;
            if (AudioUnitSetProperty(mAudioUnit, kAudioUnitProperty_SetRenderCallback, kAudioUnitScope_Global, 0, &callbackStruct, sizeof(callbackStruct)) != kAudioHardwareNoError)
            {
                return false;
            }
        }
        // Init
        if (AudioUnitInitialize(mAudioUnit) != kAudioHardwareNoError)
        {
            return false;
        }
        
        return true;
        #endif
        return false;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VAudioMacOSHandler::Start(VAudioStream& _stream)
    {
        if (_stream.Status() == VAudioStreamStatus::Opened)
        {
            if (_stream.IsInputEnabled())
            {
                if (AudioOutputUnitStart(mAudioUnit) != kAudioHardwareNoError)
                {
                    return false;
                }
            }
            if (_stream.IsOutputEnabled())
            {
                if (AudioOutputUnitStart(mAudioUnit) != kAudioHardwareNoError)
                {
                    return false;
                }
            }
            return true;
        }
        
        return false;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VAudioMacOSHandlerTest()
    {
        
        return;
    }
    
}

#endif
