#include "VAudioHandler.h"
#include "MacOS/VAudioMacOSHandler.h"
#include "Windows/VAudioWindowsHandler.h"
#include "../AudioStream/VAudioStream.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAudioHandler
    //----------------------------------------------------------------------------------------------------
    VSharePointer<VAudioHandler> VAudioHandler::Instance()
    {
        #ifdef _VOID_USE_COREAUDIO_
        return VSharePointer<VAudioHandler>(new VAudioMacOSHandler());
		#elif defined _VOID_USE_WINMM_
		return VSharePointer<VAudioHandler>(new VAudioWindowsHandler());
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
