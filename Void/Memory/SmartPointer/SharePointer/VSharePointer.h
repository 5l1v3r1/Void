#pragma once
#ifndef _V_SHAREPOINTER_H_
#define _V_SHAREPOINTER_H_

#include "../PointerCounter/VPointerCounter.h"
#include "../../../VDefine.h"
#ifdef _VOID_ENABLE_MEMORY_DEBUG_
#include "../../../Utility/Logger/VLogger.h"
#include <typeinfo>
#endif

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VWeakPointer
    //----------------------------------------------------------------------------------------------------
    template <typename _T>
    class VWeakPointer;
    
    // VSharePointer
    // new -> counter(1) -> counter(...) -> counter(0) -> delete
    //----------------------------------------------------------------------------------------------------
    template <typename _T>
    class VSharePointer
    {
        //----------------------------------------------------------------------------------------------------
        friend VWeakPointer<_T>;
        
    public:
        //----------------------------------------------------------------------------------------------------
        VSharePointer(_T* _value = nullptr)
            :
            mCounter(new VPointerCounter()),
            mValue(_value)
        {
            Increase();
        }
        
        //----------------------------------------------------------------------------------------------------
        VSharePointer(const VSharePointer& _pointer)
            :
            mCounter(_pointer.mCounter),
            mValue(_pointer.mValue)
        {
            Increase();
        }
        
        //----------------------------------------------------------------------------------------------------
        VSharePointer(const VWeakPointer<_T>& _pointer)
            :
            mCounter(_pointer.mCounter),
            mValue(_pointer.mValue)
        {
            Increase();
        }
        
        //----------------------------------------------------------------------------------------------------
        virtual ~VSharePointer()
        {
            Decrease();
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        VSharePointer& operator=(const VSharePointer& _pointer)
        {
            Decrease();
            
            mCounter = _pointer.mCounter;
            mValue = _pointer.mValue;
            Increase();
            
            return *this;
        }
        
        //----------------------------------------------------------------------------------------------------
        bool operator==(const VSharePointer& _pointer) const
        {
            return mCounter == _pointer.mCounter && mValue == _pointer.mValue;
        }
        
        //----------------------------------------------------------------------------------------------------
        bool operator!=(const VSharePointer& _pointer) const
        {
            return !(*this == _pointer);
        }
        
        //----------------------------------------------------------------------------------------------------
        bool operator<(const VSharePointer& _pointer) const
        {
            return mValue < _pointer.mValue;
        }
        
        //----------------------------------------------------------------------------------------------------
        _T* operator->()
        {
            return mValue;
        }
        
        //----------------------------------------------------------------------------------------------------
        _T& operator*()
        {
            return *mValue;
        }
        
        //----------------------------------------------------------------------------------------------------
        const _T& operator*() const
        {
            return *mValue;
        }
        
        //----------------------------------------------------------------------------------------------------
        operator bool()
        {
            return mValue ? true : false;
        }
        
        //----------------------------------------------------------------------------------------------------
        void SetValue(_T* _value)
        {
            Decrease();
            
            mCounter = new VPointerCounter();
            mValue = _value;
            Increase();
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        void Increase()
        {
            mCounter->IncreaseShare();
            #ifdef _VOID_ENABLE_MEMORY_DEBUG_
            VLogger::Print("SHAREPOINTER", "Increase: %s %x %d", typeid(*this).name(), mCounter, mCounter->ShareCount());
            #endif
        }
        
        //----------------------------------------------------------------------------------------------------
        void Decrease()
        {
            #ifdef _VOID_ENABLE_MEMORY_DEBUG_
            VLogger::Print("SHAREPOINTER", "Decrease: %s %x %d", typeid(*this).name(), mCounter, mCounter->ShareCount() - 1);
            #endif
            if (mCounter->DecreaseShare() == 0)
            {
                if (mCounter->WeakCount() == 0)
                {
                    delete mCounter;
                    mCounter = nullptr;
                }
                if (mValue)
                {
                    delete mValue;
                    mValue = nullptr;
                }
            }
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        VPointerCounter *mCounter;
        _T *mValue;
    };
}

#endif
