#pragma once
#ifndef _V_ANY_H_
#define _V_ANY_H_
#include <typeinfo>
#include <type_traits>
#include <algorithm>
#include <memory>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAny
    //----------------------------------------------------------------------------------------------------
    class VAny
    {
    public:
        //----------------------------------------------------------------------------------------------------
        inline VAny()
            :
            content(nullptr)
        {
        }
        
        template <typename _T>
        inline VAny(const _T& _t)
            :
            content(new Holder<_T>(_t))
        {
        }

        
        inline VAny(const VAny& _any)
            :
            content(_any.content ? _any.content->Clone() : 0)
        {
        }
        
        inline VAny(VAny&& _any)
            :
            content(_any.content)
        {
            _any.content = nullptr;
        }
        
        inline virtual ~VAny()
        {
            if (content != nullptr) { delete content; }
        }
        
        //----------------------------------------------------------------------------------------------------
        inline VAny& Swap(VAny& _any)
        {
            std::swap(content, _any.content);
            return *this;
        }
        
        bool Empty() const
        {
            return !content;
        }
        
        void Clear()
        {
            VAny().Swap(*this);
        }
        
        const std::type_info& Type() const
        {
            return content ? content->Type() : typeid(void);
        }
        
        //----------------------------------------------------------------------------------------------------
        VAny& operator=(const VAny& _any)
        {
            VAny(_any).Swap(*this);
            return *this;
        }
        
        VAny& operator=(VAny&& _any)
        {
            _any.Swap(*this);
            VAny().Swap(_any);
            return *this;
        }
        
        template <class _T>
        VAny& operator=(_T&& _t)
        {
            VAny(static_cast<_T&&>(_t)).Swap(*this);
            return *this;
        }
        
    private: // representation
        //----------------------------------------------------------------------------------------------------
        template<typename _T>
        friend _T* VAnyCast(VAny*) noexcept;
        
        template<typename _T>
        friend _T* VAnyUnsafeCast(VAny*) noexcept;
        
    protected:
        //----------------------------------------------------------------------------------------------------
        class Placeholder
        {
        public:
            //----------------------------------------------------------------------------------------------------
            virtual ~Placeholder()
            {
            }
            
        public:
            //----------------------------------------------------------------------------------------------------
            virtual const std::type_info& Type() const = 0;
            virtual Placeholder* Clone() const = 0;
        };
        
        //----------------------------------------------------------------------------------------------------
        template <typename _T>
        class Holder : public Placeholder
        {
        public:
            //----------------------------------------------------------------------------------------------------
            Holder(const _T& _t)
                :
                held(_t)
            {
            }
            
            //----------------------------------------------------------------------------------------------------
            Holder(const _T&& _t)
                :
                held(static_cast<_T&&>(_t))
            {
            }

            //----------------------------------------------------------------------------------------------------
            virtual const std::type_info& Type() const
            {
                return typeid(_T);
            }
            
            virtual Placeholder* Clone() const
            {
                return new Holder(held);
            }
            
        private: // Intentionally left unimplemented
             //----------------------------------------------------------------------------------------------------
            Holder& operator=(const Holder&);
            
        public:
            //----------------------------------------------------------------------------------------------------
            _T held;
        };
        
    public:
        //----------------------------------------------------------------------------------------------------
        Placeholder *content;
    };
    
    // VAnyBadCast
    //----------------------------------------------------------------------------------------------------
    class VAnyBadCast : public std::bad_cast
    {
    public:
        //----------------------------------------------------------------------------------------------------
        virtual const char* what() const noexcept
        {
            return "Failed conversion using VAnyCast";
        }
    };
    
    
    // VAnyCast
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    inline _T VAnyCast(VAny& _operand)
    {
        typedef typename std::remove_reference<_T>::type NonrefType;
        
        NonrefType* result = VAnyCast<NonrefType>(std::addressof(_operand));
        if(!result) { throw VAnyBadCast(); }
        
        if (std::is_reference<_T>::value)
        {
            return static_cast<_T>(*result);
        }
        else
        {
            typedef typename std::add_lvalue_reference<_T>::type RefType;
            return static_cast<RefType>(*result);
        }
    }
    
    template<typename _T>
    inline _T VAnyCast(const VAny& _operand)
    {
        typedef typename std::remove_reference<_T>::type NonrefType;
        return VAnyCast<const NonrefType &>(const_cast<VAny&>(_operand));
    }
    
    template<typename _T>
    inline _T* VAnyCast(VAny* _operand) noexcept
    {
        return _operand && _operand->Type() == typeid(_T) ? std::addressof(static_cast<VAny::Holder<typename std::remove_cv<_T>::type>*>(_operand->content)->held): 0;
    }
    
    template<typename _T>
    inline const _T* VAnyCast(const VAny* _operand) noexcept
    {
        return VAnyCast<_T>(const_cast<_T*>(_operand));
    }
    
    // VAnyUnsafeCast
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    inline _T* VAnyUnsafeCast(VAny* _operand) noexcept
    {
        return std::addressof(static_cast<VAny::Holder<_T>*>(_operand->content)->held);
    }
    
    template<typename _T>
    inline const _T* VAnyUnsafeCast(const VAny* _operand) noexcept
    {
        return VAnyUnsafeCast<_T>(const_cast<VAny*>(_operand));
    }

    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VAnyTest();
}

#endif
