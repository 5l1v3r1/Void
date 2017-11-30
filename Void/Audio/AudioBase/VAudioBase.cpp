#include "VAudioBase.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAudioBase
    //----------------------------------------------------------------------------------------------------
    VAudioBase::VAudioBase()
        :
        mFormat(),
        mData(new std::vector<char>())
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VAudioBase::VAudioBase(const VAudioFormat& _format)
        :
        mFormat(_format),
        mData(new std::vector<char>())
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VAudioBase::VAudioBase(const VAudioBase& _base)
        :
        mFormat(_base.mFormat),
        mData(_base.mData)
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
    VSharePointer<std::vector<char>>& VAudioBase::Data()
    {
        return mData;
    }
    
    //----------------------------------------------------------------------------------------------------
    const VSharePointer<std::vector<char>>& VAudioBase::Data() const
    {
        return mData;
    }
    
    //----------------------------------------------------------------------------------------------------
    char* VAudioBase::Block(const unsigned long& _originIndex, const unsigned long& _length)
    {
        if (mData)
        {
            unsigned long byteBegin = _originIndex * mFormat.BlockAlign();
            unsigned long byteEnd = (_originIndex + _length) * mFormat.BlockAlign();
            if (byteEnd <= mData->size())
            {
                return &(*mData)[byteBegin];
            }
        }
        return nullptr;
    }
    
    //----------------------------------------------------------------------------------------------------
    const char* VAudioBase::Block(const unsigned long& _originIndex, const unsigned long& _length) const
    {
        if (mData)
        {
            unsigned long byteBegin = _originIndex * mFormat.BlockAlign();
            unsigned long byteEnd = (_originIndex + _length) * mFormat.BlockAlign();
            if (byteEnd <= mData->size())
            {
                return &(*mData)[byteBegin];
            }
        }
        return nullptr;
    }
    
    //----------------------------------------------------------------------------------------------------
    unsigned long VAudioBase::BlockCount() const
    {
        if (mData)
        {
            return mData->size() / mFormat.BlockAlign();
        }
        return 0;
    }
    
    //----------------------------------------------------------------------------------------------------
    float VAudioBase::DurationSeconds() const
    {
        if (mData)
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
