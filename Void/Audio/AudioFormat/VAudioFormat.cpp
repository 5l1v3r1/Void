#include "VAudioFormat.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
	// VAudioFormat
	//----------------------------------------------------------------------------------------------------
	VAudioFormat::VAudioFormat()
		:
		formatType(0),
		channels(2),
		samplesPerSec(44100),
		bitsPerSample(16)
	{
	}

	//----------------------------------------------------------------------------------------------------
	VAudioFormat::VAudioFormat(const VAudioFormat& _stream)
		:
		formatType(_stream.formatType),
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
