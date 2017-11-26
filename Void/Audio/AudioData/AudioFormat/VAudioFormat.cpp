#include "VAudioFormat.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
	// VAudioFormat
	//----------------------------------------------------------------------------------------------------
	VAudioFormat::VAudioFormat()
		:
        format(VAudioSampleFormat::Float32),
		channels(2),
		samplesPerSec(44100),
		bitsPerSample(16)
	{
	}

	//----------------------------------------------------------------------------------------------------
	VAudioFormat::VAudioFormat(const VAudioFormat& _stream)
		:
		format(_stream.format),
		channels(_stream.channels),
		samplesPerSec(_stream.samplesPerSec),
		bitsPerSample(_stream.bitsPerSample)
	{
		
	}

	//----------------------------------------------------------------------------------------------------
	VAudioFormat::~VAudioFormat()
	{
	}

	// Test
	//----------------------------------------------------------------------------------------------------
	void VAudioFormatTest()
	{

		return;
	}

}
