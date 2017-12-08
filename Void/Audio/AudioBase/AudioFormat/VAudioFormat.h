#pragma once
#ifndef _V_AUDIOFORMAT_H_
#define _V_AUDIOFORMAT_H_

#include <stdint.h>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAudioSampleFormat
    //----------------------------------------------------------------------------------------------------
    enum class VAudioSampleFormat
    {
        Unknown = 0,
        UInt8,
        Int8,
        Int16,
        Int24,
        Int32,
        Float32,
        Double64,
    };
    
	// VAudioFormat
    //----------------------------------------------------------------------------------------------------
    // Sample Rate: 8000, 16000, 32000, 64000
    //              11025, 22050, 44100, 88200, 176400
    //              12000, 24000, 48000, 96000, 192000
	//----------------------------------------------------------------------------------------------------
	class VAudioFormat
	{
	public:
		//----------------------------------------------------------------------------------------------------
		VAudioFormat();
        VAudioFormat(VAudioSampleFormat _sampleFormat, int _channels, int _samplesPerSecond, int _bitsPerSample);
		VAudioFormat(const VAudioFormat& _format);
		~VAudioFormat();
        
        //----------------------------------------------------------------------------------------------------
        int BytesPerSample() const;
        int BlockAlign() const;
        int BytesPerSecond() const;
        float DurationSeconds(const unsigned long& _blockCount) const;

	public:
		//----------------------------------------------------------------------------------------------------
		VAudioSampleFormat sampleFormat;
		int channels; // number of channels (i.e. mono, stereo...)
		int samplesPerSecond; // sample rate (i.e. 8000, 44100, 48000, 192000...)
		int bitsPerSample; // number of bits per sample of mono data
        // int blockAlign = channels * bitsPerSample / 8;
		// int bytesPerSecond = samplesPerSecond * blockAlign;
	};
    
    // VAudioFormattedDataCore
    //----------------------------------------------------------------------------------------------------
    // Make sure the pointer of samples is avaliable
    //----------------------------------------------------------------------------------------------------
    template<typename _Type>
    class VAudioFormattedDataCore
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VAudioFormattedDataCore()
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        VAudioFormattedDataCore(const VAudioFormattedDataCore& _core)
            :
            mSamples(_core.mSamples),
            mByteOffset(_core.mByteOffset),
            mBlockAlign(_core.mBlockAlign),
            mBlockCount(_core.mBlockCount),
            mChannels(_core.mChannels)
        {
            
        }
        
        //----------------------------------------------------------------------------------------------------
        void Initialize(char *_samples, int _byteOffset, int _blockAlign, unsigned long _blockCount)
        {
            mSamples = _samples;
            mByteOffset = _byteOffset;
            mBlockAlign = _blockAlign;
            mBlockCount = _blockCount;
            mChannels = _blockAlign / sizeof(_Type);
        }
        
        //----------------------------------------------------------------------------------------------------
        _Type* Sample(unsigned long _index, int _channel=0)
        {
            if (_index < mBlockCount && _channel < mChannels)
            {
                return (_Type*)(mSamples + mByteOffset + mBlockAlign * _index) + _channel;
            }
            return nullptr;
        }
        
        //----------------------------------------------------------------------------------------------------
        _Type& operator[](unsigned long _index)
        {
            if (_index < mBlockCount)
            {
                return *(_Type*)(mSamples + mByteOffset + mBlockAlign * _index);
            }
            throw "VAudioFormattedDataCore: out of range";
        }
        
        //----------------------------------------------------------------------------------------------------
        const unsigned long& BlockCount()
        {
            return mBlockCount;
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        char *mSamples;
        // int mSampleOffset;
        int mByteOffset;
        int mBlockAlign;
        unsigned long mBlockCount;
        int mChannels;
    };
    
    // VAudioFormattedData
    //----------------------------------------------------------------------------------------------------
    template<VAudioSampleFormat _SampleFormat=VAudioSampleFormat::Unknown>
    class VAudioFormattedData : public VAudioFormattedDataCore<char>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        typedef char value_type;
        typedef char ValueType;
    };
    
    // VAudioFormattedData<VAudioSampleFormat::UInt8>
    //----------------------------------------------------------------------------------------------------
    template<>
    class VAudioFormattedData<VAudioSampleFormat::UInt8> : public VAudioFormattedDataCore<uint8_t>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        typedef uint8_t value_type;
        typedef uint8_t ValueType;
    };
    
    // VAudioFormattedData<VAudioSampleFormat::Int8>
    //----------------------------------------------------------------------------------------------------
    template<>
    class VAudioFormattedData<VAudioSampleFormat::Int8> : public VAudioFormattedDataCore<int8_t>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        typedef int8_t value_type;
        typedef int8_t ValueType;
    };
    
    // VAudioFormattedData<VAudioSampleFormat::Int16>
    //----------------------------------------------------------------------------------------------------
    template<>
    class VAudioFormattedData<VAudioSampleFormat::Int16> : public VAudioFormattedDataCore<int16_t>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        typedef int16_t value_type;
        typedef int16_t ValueType;
    };

	// Test
	//----------------------------------------------------------------------------------------------------
	void VAudioFormatTest();
}

#endif
