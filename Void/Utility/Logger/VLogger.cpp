#include "VLogger.h"
#include "../Time/VTime.h"
#include <stdio.h>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VLogger
    //----------------------------------------------------------------------------------------------------
    bool VLogger::s_isEnabled = true;
    
    //----------------------------------------------------------------------------------------------------
    void VLogger::PrintV(const char* _tag, const char* _fmt, va_list _vp)
    {
        if (s_isEnabled)
        {
            // time
            VTime time = VTime::Now();
            printf("[%s %s] ", time.String().c_str(), _tag);
            
            // va
            vprintf(_fmt, _vp);
            
            // end
            printf("\n");
        }
    }
    
    //----------------------------------------------------------------------------------------------------
    void VLogger::Print(const char* _tag, const char* _fmt, ...)
    {
        va_list ap;
        va_start(ap, _fmt);
        PrintV(_tag, _fmt, ap);
        va_end(ap);
    }
    
    //----------------------------------------------------------------------------------------------------
    void VLogger::Info(const char* _fmt, ...)
    {
        va_list ap;
        va_start(ap, _fmt);
        PrintV("INFO", _fmt, ap);
        va_end(ap);
    }
    
    //----------------------------------------------------------------------------------------------------
    void VLogger::Error(const char* _fmt, ...)
    {
        va_list ap;
        va_start(ap, _fmt);
        PrintV("ERROR", _fmt, ap);
        va_end(ap);
    }
}
