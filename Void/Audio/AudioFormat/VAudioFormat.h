#pragma once
#ifndef _V_AUDIOFORMAT_H_
#define _V_AUDIOFORMAT_H_

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAudioSampleFormat
    //----------------------------------------------------------------------------------------------------
    enum class VAudioSampleFormat
    {
        Float32 = 0,
        Int32,
        Int24,
        Int16,
        Int8,
        UInt8,
    };
    
	// VAudioFormat
    //----------------------------------------------------------------------------------------------------
    // Sample Rate: 11025, 22050, (44100), 88200, 176400
    //              12000, 24000, (48000), 96000, 192000
    //              8000, 16000, 32000, 64000
	//----------------------------------------------------------------------------------------------------
	class VAudioFormat
	{
	public:
		//----------------------------------------------------------------------------------------------------
		VAudioFormat();
		VAudioFormat(const VAudioFormat& _format);
		~VAudioFormat();

	public:
		//----------------------------------------------------------------------------------------------------
		VAudioSampleFormat format; // PCM...
		int channels; // number of channels (i.e. mono, stereo...)
		int samplesPerSec; // sample rate (i.e. 8000, 44100, 48000, 192000...)
		int bitsPerSample; // number of bits per sample of mono data

        // int blockAlign = channels * bitsPerSample / 8;
		// int avgBytesPerSec = samplesPerSec * blockAlign;
	};

	// Test
	//----------------------------------------------------------------------------------------------------
	void VAudioFormatTest();
}

#endif
