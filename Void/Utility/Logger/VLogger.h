#pragma once
#ifndef _V_LOGGER_H_
#define _V_LOGGER_H_
#include <stdarg.h>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VLogger
    //----------------------------------------------------------------------------------------------------
    class VLogger
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static void PrintV(const char* _tag, const char* _fmt, va_list _vp);
        static void Print(const char* _tag, const char* _fmt, ...);
        static void Info(const char* _fmt, ...);
        static void Error(const char* _fmt, ...);
        
    public:
        //----------------------------------------------------------------------------------------------------
        static bool s_isEnabled;
    };
}


#endif
