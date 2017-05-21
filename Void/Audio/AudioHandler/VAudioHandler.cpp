#include "VAudioHandler.h"
#include "MacOS/VAudioMacOSHandler.h"
#include "Windows/VAudioWindowsHandler.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAudioHandler
    //----------------------------------------------------------------------------------------------------
    VSmartPtr<VAudioHandler> VAudioHandler::Instance()
    {
        #ifdef _VOID_USE_COREAUDIO_
        return VSmartPtr<VAudioHandler>(new VAudioMacOSHandler());
		#elif defined(_WIN32) || defined(_WIN64)
		return VSmartPtr<VAudioHandler>(new VAudioWindowsHandler());
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
