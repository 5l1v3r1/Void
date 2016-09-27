#pragma once
#ifndef _V_SMARTPTR_H_
#define _V_SMARTPTR_H_

//----------------------------------------------------------------------------------------------------
namespace Void
{
	// VSmartPtr
	//----------------------------------------------------------------------------------------------------
	template <typename _T>
	class VSmartPtr
	{
	public:
		//----------------------------------------------------------------------------------------------------
		VSmartPtr(_T *_value = nullptr)
			:
			m_counter(new int(1)),
			m_value(_value)
		{
		}

		//----------------------------------------------------------------------------------------------------
		VSmartPtr(const VSmartPtr &_smartPtr)
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
		VSmartPtr& operator= (const VSmartPtr &_smartPtr)
		{
			Decrease();

			m_counter = _smartPtr.m_counter;
			m_value = _smartPtr.m_value;
			Increase();

			return *this;
		}

		//----------------------------------------------------------------------------------------------------
		bool operator== (const VSmartPtr &_smartPtr) const
		{
			return m_counter == _smartPtr.m_counter && m_value == _smartPtr.m_value;
		}

		//----------------------------------------------------------------------------------------------------
		bool operator!= (const VSmartPtr &_smartPtr) const
		{
			return !(*this == _smartPtr);
		}

		//----------------------------------------------------------------------------------------------------
		bool operator< (const VSmartPtr &_smartPtr) const
		{
			return m_value < _smartPtr.m_value;
		}

		//----------------------------------------------------------------------------------------------------
		_T* operator-> ()
		{
			return m_value;
		}

		//----------------------------------------------------------------------------------------------------
		_T& operator* ()
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

	protected:
		//----------------------------------------------------------------------------------------------------
		void SetValue(_T *_value)
		{
			Decrease();

			m_counter = new int(1);
			m_value = _value;
		}

		//----------------------------------------------------------------------------------------------------
		void Increase()
		{
			++*m_counter;
		}

		//----------------------------------------------------------------------------------------------------
		void Decrease()
		{
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