#include "VAudioBase.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAudioBase
    //----------------------------------------------------------------------------------------------------
    VAudioBase::VAudioBase()
        :
        mFormat(),
        mSamples(new std::vector<char>())
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VAudioBase::VAudioBase(const VAudioFormat& _format)
        :
        mFormat(_format),
        mSamples(new std::vector<char>())
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VAudioBase::VAudioBase(const VAudioBase& _base)
        :
        mFormat(_base.mFormat),
        mSamples(_base.mSamples)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VAudioBase::~VAudioBase()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    const VAudioFormat& VAudioBase::Format() const
    {
        return mFormat;
    }
    
    //----------------------------------------------------------------------------------------------------
    VSharePointer<std::vector<char>>& VAudioBase::Samples()
    {
        return mSamples;
    }
    
    //----------------------------------------------------------------------------------------------------
    const VSharePointer<std::vector<char>>& VAudioBase::Samples() const
    {
        return mSamples;
    }
    
    //----------------------------------------------------------------------------------------------------
    char* VAudioBase::Block(const unsigned long& _originIndex, const unsigned long& _length)
    {
        if (mSamples)
        {
            unsigned long byteBegin = _originIndex * mFormat.BlockAlign();
            unsigned long byteEnd = (_originIndex + _length) * mFormat.BlockAlign();
            if (byteEnd <= mSamples->size())
            {
                return &(*mSamples)[byteBegin];
            }
        }
        return nullptr;
    }
    
    //----------------------------------------------------------------------------------------------------
    const char* VAudioBase::Block(const unsigned long& _originIndex, const unsigned long& _length) const
    {
        if (mSamples)
        {
            unsigned long byteBegin = _originIndex * mFormat.BlockAlign();
            unsigned long byteEnd = (_originIndex + _length) * mFormat.BlockAlign();
            if (byteEnd <= mSamples->size())
            {
                return &(*mSamples)[byteBegin];
            }
        }
        return nullptr;
    }
    
    //----------------------------------------------------------------------------------------------------
    unsigned long VAudioBase::BlockCount() const
    {
        if (mSamples)
        {
            return mSamples->size() / mFormat.BlockAlign();
        }
        return 0;
    }
    
    //----------------------------------------------------------------------------------------------------
    float VAudioBase::DurationSeconds() const
    {
        if (mSamples)
        {
            return mFormat.DurationSeconds(BlockCount());
        }
        return 0;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VAudioBaseTest()
    {
        
    }
}
