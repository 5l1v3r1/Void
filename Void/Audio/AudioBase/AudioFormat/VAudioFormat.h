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
        VAudioFormat(VAudioSampleFormat _format, int _channels, int _samplesPerSecond, int _bitsPerSample);
		VAudioFormat(const VAudioFormat& _format);
		~VAudioFormat();
        
        //----------------------------------------------------------------------------------------------------
        int BytesPerSample() const;
        int BlockAlign() const;
        int BytesPerSecond() const;
        float DurationSeconds(const unsigned long& _blockCount) const;

	public:
		//----------------------------------------------------------------------------------------------------
		VAudioSampleFormat format;
		int channels; // number of channels (i.e. mono, stereo...)
		int samplesPerSecond; // sample rate (i.e. 8000, 44100, 48000, 192000...)
		int bitsPerSample; // number of bits per sample of mono data
        // int blockAlign = channels * bitsPerSample / 8;
		// int bytesPerSecond = samplesPerSecond * blockAlign;
	};

	// Test
	//----------------------------------------------------------------------------------------------------
	void VAudioFormatTest();
}

#endif
