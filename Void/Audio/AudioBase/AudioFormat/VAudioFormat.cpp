#include "VAudioFormat.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
	// VAudioFormat
	//----------------------------------------------------------------------------------------------------
	VAudioFormat::VAudioFormat()
		:
        sampleFormat(VAudioSampleFormat::Unknown),
		channels(0),
		samplesPerSecond(0),
		bitsPerSample(0)
	{
	}
    
    //----------------------------------------------------------------------------------------------------
    VAudioFormat::VAudioFormat(VAudioSampleFormat _sampleFormat, int _channels, int _samplesPerSecond, int _bitsPerSample)
        :
        sampleFormat(_sampleFormat),
        channels(_channels),
        samplesPerSecond(_samplesPerSecond),
        bitsPerSample(_bitsPerSample)
    {
        
    }

	//----------------------------------------------------------------------------------------------------
	VAudioFormat::VAudioFormat(const VAudioFormat& _format)
		:
        sampleFormat(_format.sampleFormat),
		channels(_format.channels),
		samplesPerSecond(_format.samplesPerSecond),
		bitsPerSample(_format.bitsPerSample)
	{
	}

	//----------------------------------------------------------------------------------------------------
	VAudioFormat::~VAudioFormat()
	{
	}
    
    //----------------------------------------------------------------------------------------------------
    int VAudioFormat::BytesPerSample() const
    {
        return bitsPerSample / 8;
    }
    
    //----------------------------------------------------------------------------------------------------
    int VAudioFormat::BlockAlign() const
    {
        return channels * BytesPerSample();
    }
    
    //----------------------------------------------------------------------------------------------------
    int VAudioFormat::BytesPerSecond() const
    {
        return samplesPerSecond * BlockAlign();
    }
    
    //----------------------------------------------------------------------------------------------------
    float VAudioFormat::DurationSeconds(const unsigned long& _blockCount) const
    {
        return _blockCount / (float)samplesPerSecond;
    }

	// Test
	//----------------------------------------------------------------------------------------------------
	void VAudioFormatTest()
	{

		return;
	}

}
