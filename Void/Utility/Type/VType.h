#pragma once
#ifndef _V_TYPE_H_
#define _V_TYPE_H_

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VTypes
    //----------------------------------------------------------------------------------------------------
    template<typename _Head, typename... _Others>
    struct VTypes
    {
        template<typename... _Types>
        struct OtherTypes
        {
            typedef VTypes<_Types...> Self;
        };
        typedef _Head Type;
        typedef OtherTypes<_Others...> Next;
    };
    
    // VTypeIndex
    //----------------------------------------------------------------------------------------------------
    template<unsigned _Index, typename _VType>
    struct VTypeIndex
    {
        typedef typename VTypeIndex<_Index - 1, typename _VType::Next::Self>::Type Type;
    };
    
    template<typename _VType>
    struct VTypeIndex<0, _VType>
    {
        typedef typename _VType::Type Type;
    };
    
    // VTypeLambda
    //----------------------------------------------------------------------------------------------------
    template<class _T>
    struct VTypeLambda
    {
        typedef typename VTypeLambda<decltype(&_T::operator())>::Types Types;
    };
    
    template<typename _Return, class _Class, typename... _Args>
    struct VTypeLambda<_Return(_Class::*)(_Args...)>
    {
        typedef VTypes<_Return, _Args...> Types;
    };
    
    template<typename _Return, class _Class, typename... _Args>
    struct VTypeLambda<_Return(_Class::*)(_Args...)const>
    {
        typedef VTypes<_Return, _Args...> Types;
    };
    
    template<typename _Return, typename... _Args>
    struct VTypeLambda<_Return(*)(_Args...)>
    {
        typedef VTypes<_Return, _Args...> Type;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VTypeTest();
}

#endif
