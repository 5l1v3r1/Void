#include "VMemoryLeakDetector.h"

#ifdef _VOID_ENABLE_MEMORYLEAKDETECTOR_
#if defined(WIN32) || defined(WIN64) || defined(_WIN32_WCE)
#include <crtdbg.h>

//----------------------------------------------------------------------------------------------------
int before_main()
{
    //_CrtSetBreakAlloc(336);
    return 0;
}

//----------------------------------------------------------------------------------------------------
int after_main()
{
    _CrtDumpMemoryLeaks();
    return 0;
}

#else
//----------------------------------------------------------------------------------------------------
#endif
#endif
