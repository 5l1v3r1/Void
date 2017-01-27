#include "VLogger.h"
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
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
    void VLogger::Info(const char* fmt, ...)
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
            printf("[%d-%d-%d %d:%d:%d] ", currentTm.tm_year + 1900, currentTm.tm_mon + 1, currentTm.tm_mday, currentTm.tm_hour, currentTm.tm_min, currentTm.tm_sec);
            
            // va
            va_list ap;
            va_start(ap, fmt);
            vprintf(fmt, ap);
            va_end(ap);
            
            // end
            printf("\n");
        }
    }
}
