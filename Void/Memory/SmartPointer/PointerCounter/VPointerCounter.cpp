#include "VPointerCounter.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VPointerCounter
    //----------------------------------------------------------------------------------------------------
    #ifdef _VOID_ENABLE_MEMORY_DEBUG_
    int VPointerCounter::sTotalShareCount = 0;
    int VPointerCounter::sTotalWeakCount = 0;
    #endif
    
}
