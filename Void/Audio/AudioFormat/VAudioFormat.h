#pragma once
#ifndef _V_AUDIOFORMAT_H_
#define _V_AUDIOFORMAT_H_

//----------------------------------------------------------------------------------------------------
namespace Void
{
	// VAudioFormat
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
		int formatType; // WAV...
		int channels; // number of channels (i.e. mono, stereo...)
		int samplesPerSec; // sample rate
		int bitsPerSample; // number of bits per sample of mono data

		// int avgBytesPerSec = channels * samplesPerSec * bitsPerSample / 8;
		// int blockAlign = channels * bitsPerSample / 8;
	};

	// Test
	//----------------------------------------------------------------------------------------------------
	void VAudioFormatTest();
}

#endif
