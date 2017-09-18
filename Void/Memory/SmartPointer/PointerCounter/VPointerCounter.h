#pragma once
#ifndef _V_POINTERCOUNTER_H_
#define _V_POINTERCOUNTER_H_

#include "../../../VDefine.h"
#ifdef _VOID_ENABLE_MEMORY_DEBUG_
#include "../../../Utility/Logger/VLogger.h"
#endif

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VPointerCounter
    //----------------------------------------------------------------------------------------------------
    class VPointerCounter
    {
        #ifdef _VOID_ENABLE_MEMORY_DEBUG_
        static int sTotalShareCount;
        static int sTotalWeakCount;
        #endif
    public:
        //----------------------------------------------------------------------------------------------------
        VPointerCounter()
            :
            mShareCount(0),
            mWeakCount(0)
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        VPointerCounter(int _shareCount, int _weakCount)
            :
            mShareCount(_shareCount),
            mWeakCount(_weakCount)
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        virtual ~VPointerCounter()
        {
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        int ShareCount()
        {
            return mShareCount;
        }
        
        //----------------------------------------------------------------------------------------------------
        int WeakCount()
        {
            return mWeakCount;
        }
        
        //----------------------------------------------------------------------------------------------------
        void IncreaseShare()
        {
            #ifdef _VOID_ENABLE_MEMORY_DEBUG_
            VLogger::Print("SMARTPOINTER", "Share Increase: %d", ++sTotalShareCount);
            #endif
            ++mShareCount;
        }
        
        //----------------------------------------------------------------------------------------------------
        void IncreaseWeak()
        {
            #ifdef _VOID_ENABLE_MEMORY_DEBUG_
            VLogger::Print("SMARTPOINTER", "Weak Increase: %d", ++sTotalWeakCount);
            #endif
            ++mWeakCount;
        }
        
        //----------------------------------------------------------------------------------------------------
        int DecreaseShare()
        {
            #ifdef _VOID_ENABLE_MEMORY_DEBUG_
            VLogger::Print("SMARTPOINTER", "Share Decrease: %d", --sTotalShareCount);
            #endif
            return --mShareCount;
        }
        
        //----------------------------------------------------------------------------------------------------
        int DecreaseWeak()
        {
            #ifdef _VOID_ENABLE_MEMORY_DEBUG_
            VLogger::Print("SMARTPOINTER", "Weak Decrease: %d", --sTotalWeakCount);
            #endif
            return --mWeakCount;
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        int mShareCount;
        int mWeakCount;
    };
}

#endif
