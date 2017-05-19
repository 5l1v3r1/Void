#include "VAudioHandler.h"
#include "MacOS/VAudioMacOSHandler.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAudioHandler
    //----------------------------------------------------------------------------------------------------
    VSmartPtr<VAudioHandler> VAudioHandler::Instance()
    {
        #ifdef _VOID_USE_COREAUDIO_
        return VSmartPtr<VAudioHandler>(new VAudioMacOSHandler());
        #endif
        return nullptr;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VAudioHandlerTest()
    {
        
        return;
    }
    
}
