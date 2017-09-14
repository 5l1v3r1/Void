#pragma once
#ifndef _V_SMARTPOINTER_H_
#define _V_SMARTPOINTER_H_

#include "../../VDefine.h"
#ifdef _VOID_ENABLE_DEBUG_
#include "../../Utility/Logger/VLogger.h"
#include <typeinfo>
#endif

//----------------------------------------------------------------------------------------------------
namespace Void
{
	// VSmartPointer
	// new -> counter(1) -> counter(...) -> counter(0) -> delete
	//----------------------------------------------------------------------------------------------------
	template <typename _T>
	class VSmartPointer
	{
	public:
		//----------------------------------------------------------------------------------------------------
		VSmartPointer(_T* _value = nullptr)
			:
			mCounter(new int(0)),
			mValue(_value)
		{
            Increase();
		}

		//----------------------------------------------------------------------------------------------------
		VSmartPointer(const VSmartPointer& _smartPtr)
			:
			mCounter(_smartPtr.mCounter),
			mValue(_smartPtr.mValue)
		{
			Increase();
		}

		//----------------------------------------------------------------------------------------------------
		virtual ~VSmartPointer()
		{
			Decrease();
		}

		//----------------------------------------------------------------------------------------------------
		VSmartPointer& operator=(const VSmartPointer& _smartPtr)
		{
			Decrease();

			mCounter = _smartPtr.mCounter;
			mValue = _smartPtr.mValue;
			Increase();

			return *this;
		}

		//----------------------------------------------------------------------------------------------------
		bool operator==(const VSmartPointer& _smartPtr) const
		{
			return mCounter == _smartPtr.mCounter && mValue == _smartPtr.mValue;
		}

		//----------------------------------------------------------------------------------------------------
		bool operator!=(const VSmartPointer& _smartPtr) const
		{
			return !(*this == _smartPtr);
		}

		//----------------------------------------------------------------------------------------------------
		bool operator<(const VSmartPointer& _smartPtr) const
		{
			return mValue < _smartPtr.mValue;
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

		// Dangerous
		//----------------------------------------------------------------------------------------------------
		/*
		operator _T* ()
		{
		return mValue;
		}
		*/

		//----------------------------------------------------------------------------------------------------
		void SetValue(_T* _value)
		{
			Decrease();

			mCounter = new int(0);
			mValue = _value;
            Increase();
		}

    protected:
		//----------------------------------------------------------------------------------------------------
		void Increase()
		{
			++*mCounter;
            #ifdef _VOID_ENABLE_DEBUG_
            VLogger::Print("SMARTPTR", "Increase: %s %x %d", typeid(*this).name(), mCounter, *mCounter);
            #endif
		}

		//----------------------------------------------------------------------------------------------------
		void Decrease()
		{
            #ifdef _VOID_ENABLE_DEBUG_
            VLogger::Print("SMARTPTR", "Decrease: %s %x %d", typeid(*this).name(), mCounter, *mCounter - 1);
            #endif
			if (--*mCounter == 0)
			{
				delete mCounter;
				mCounter = nullptr;
				if (mValue)
				{
					delete mValue;
					mValue = nullptr;
				}
			}
		}

	protected:
		//----------------------------------------------------------------------------------------------------
		int *mCounter;
		_T *mValue;
	};
}

#endif
