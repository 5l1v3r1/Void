#include "VLogger.h"
#include <stdio.h>
#include <time.h>
#if defined(WIN32) || defined(WIN64) || defined(_WIN32_WCE)
#include <windows.h>
#else
#include <errno.h>
#endif


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
            time_t currentTime;
            struct tm currentTm;
            time(&currentTime);
            #if defined(WIN32) || defined(WIN64) || defined(_WIN32_WCE)
            localtime_s(&currentTm, &currentTime);
            #else
            localtime_r(&currentTime, &currentTm);
            #endif
            printf("[%d-%d-%d %d:%d:%d %s] ", currentTm.tm_year + 1900, currentTm.tm_mon + 1, currentTm.tm_mday, currentTm.tm_hour, currentTm.tm_min, currentTm.tm_sec, _tag);
            
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
