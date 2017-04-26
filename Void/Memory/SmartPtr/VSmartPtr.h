#pragma once
#ifndef _V_SMARTPTR_H_
#define _V_SMARTPTR_H_

#include "../../VDefine.h"
#ifdef _VOID_ENABLE_DEBUG_
#include "../../Utility/Logger/VLogger.h"
#include <typeinfo>
#endif

//----------------------------------------------------------------------------------------------------
namespace Void
{
	// VSmartPtr
	// new -> counter(1) -> counter(...) -> counter(0) -> delete
	//----------------------------------------------------------------------------------------------------
	template <typename _T>
	class VSmartPtr
	{
	public:
		//----------------------------------------------------------------------------------------------------
		VSmartPtr(_T* _value = nullptr)
			:
			m_counter(new int(0)),
			m_value(_value)
		{
            Increase();
		}

		//----------------------------------------------------------------------------------------------------
		VSmartPtr(const VSmartPtr& _smartPtr)
			:
			m_counter(_smartPtr.m_counter),
			m_value(_smartPtr.m_value)
		{
			Increase();
		}

		//----------------------------------------------------------------------------------------------------
		virtual ~VSmartPtr()
		{
			Decrease();
		}

		//----------------------------------------------------------------------------------------------------
		VSmartPtr& operator=(const VSmartPtr& _smartPtr)
		{
			Decrease();

			m_counter = _smartPtr.m_counter;
			m_value = _smartPtr.m_value;
			Increase();

			return *this;
		}

		//----------------------------------------------------------------------------------------------------
		bool operator==(const VSmartPtr& _smartPtr) const
		{
			return m_counter == _smartPtr.m_counter && m_value == _smartPtr.m_value;
		}

		//----------------------------------------------------------------------------------------------------
		bool operator!=(const VSmartPtr& _smartPtr) const
		{
			return !(*this == _smartPtr);
		}

		//----------------------------------------------------------------------------------------------------
		bool operator<(const VSmartPtr& _smartPtr) const
		{
			return m_value < _smartPtr.m_value;
		}

		//----------------------------------------------------------------------------------------------------
		_T* operator->()
		{
			return m_value;
		}

		//----------------------------------------------------------------------------------------------------
		_T& operator*()
		{
			return *m_value;
		}
        
        //----------------------------------------------------------------------------------------------------
        const _T& operator*() const
        {
            return *m_value;
        }

		//----------------------------------------------------------------------------------------------------
		operator bool()
		{
			return m_value ? true : false;
		}

		// Dangerous
		//----------------------------------------------------------------------------------------------------
		/*
		operator _T* ()
		{
		return m_value;
		}
		*/

		//----------------------------------------------------------------------------------------------------
		void SetValue(_T* _value)
		{
			Decrease();

			m_counter = new int(0);
			m_value = _value;
            Increase();
		}

    protected:
		//----------------------------------------------------------------------------------------------------
		void Increase()
		{
			++*m_counter;
            #ifdef _VOID_ENABLE_DEBUG_
            VLogger::Print("SMARTPTR", "Increase: %s %x %d", typeid(*this).name(), m_counter, *m_counter);
            #endif
		}

		//----------------------------------------------------------------------------------------------------
		void Decrease()
		{
            #ifdef _VOID_ENABLE_DEBUG_
            VLogger::Print("SMARTPTR", "Decrease: %s %x %d", typeid(*this).name(), m_counter, *m_counter - 1);
            #endif
			if (--*m_counter == 0)
			{
				delete m_counter;
				m_counter = nullptr;
				if (m_value)
				{
					delete m_value;
					m_value = nullptr;
				}
			}
		}

	protected:
		//----------------------------------------------------------------------------------------------------
		int *m_counter;
		_T *m_value;
	};
}

#endif
