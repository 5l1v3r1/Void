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
    template<unsigned _Index, typename _VTypes>
    struct VTypeIndex
    {
        typedef typename VTypeIndex<_Index - 1, typename _VTypes::Next::Self>::Type Type;
    };
    
    template<typename _VTypes>
    struct VTypeIndex<0, _VTypes>
    {
        typedef typename _VTypes::Type Type;
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
