#pragma once
#ifndef _V_WEAKPOINTER_H_
#define _V_WEAKPOINTER_H_

#include "../PointerCounter/VPointerCounter.h"
#include "../../../VDefine.h"
#ifdef _VOID_ENABLE_MEMORY_DEBUG_
#include "../../../Utility/Logger/VLogger.h"
#include <typeinfo>
#endif

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VSharePointer
    //----------------------------------------------------------------------------------------------------
    template <typename _T>
    class VSharePointer;
    
    // VWeakPointer
    // new -> counter(1) -> counter(...) -> counter(0) -> delete
    //----------------------------------------------------------------------------------------------------
    template <typename _T>
    class VWeakPointer
    {
        //----------------------------------------------------------------------------------------------------
        friend VSharePointer<_T>;
        
    public:
        //----------------------------------------------------------------------------------------------------
        VWeakPointer(_T* _value = nullptr)
            :
            mCounter(new VPointerCounter()),
            mValue(_value)
        {
            Increase();
        }
        
        //----------------------------------------------------------------------------------------------------
        VWeakPointer(const VWeakPointer& _pointer)
            :
            mCounter(_pointer.mCounter),
            mValue(_pointer.mValue)
        {
            Increase();
        }
        
        //----------------------------------------------------------------------------------------------------
        VWeakPointer(const VSharePointer<_T>& _pointer)
            :
            mCounter(_pointer.mCounter),
            mValue(_pointer.mValue)
        {
            Increase();
        }
        
        //----------------------------------------------------------------------------------------------------
        virtual ~VWeakPointer()
        {
            Decrease();
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        VWeakPointer& operator=(const VWeakPointer& _pointer)
        {
            Decrease();
            
            mCounter = _pointer.mCounter;
            mValue = _pointer.mValue;
            Increase();
            
            return *this;
        }
        
        //----------------------------------------------------------------------------------------------------
        bool operator==(const VWeakPointer& _pointer) const
        {
            return mCounter == _pointer.mCounter && mValue == _pointer.mValue;
        }
        
        //----------------------------------------------------------------------------------------------------
        bool operator!=(const VWeakPointer& _pointer) const
        {
            return !(*this == _pointer);
        }
        
        //----------------------------------------------------------------------------------------------------
        bool operator<(const VWeakPointer& _pointer) const
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
            mCounter->IncreaseWeak();
            #ifdef _VOID_ENABLE_MEMORY_DEBUG_
            VLogger::Print("WEAKPOINTER", "Increase: %s %x %d", typeid(*this).name(), mCounter, mCounter->WeakCount());
            #endif
        }
        
        //----------------------------------------------------------------------------------------------------
        void Decrease()
        {
            #ifdef _VOID_ENABLE_MEMORY_DEBUG_
            VLogger::Print("WEAKPOINTER", "Decrease: %s %x %d", typeid(*this).name(), mCounter, mCounter->WeakCount() - 1);
            #endif
            if (mCounter->DecreaseWeak() == 0)
            {
                if (mCounter->ShareCount() == 0)
                {
                    delete mCounter;
                    mCounter = nullptr;
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
