#include "VAudioHandler.h"
#include "MacOS/VAudioMacOSHandler.h"
#include "Windows/VAudioWindowsHandler.h"
#include "../AudioStream/VAudioStream.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAudioHandler
    //----------------------------------------------------------------------------------------------------
    VSmartPointer<VAudioHandler> VAudioHandler::Instance()
    {
        #ifdef _VOID_USE_COREAUDIO_
        return VSmartPointer<VAudioHandler>(new VAudioMacOSHandler());
		#elif _VOID_USE_WINMM_
		return VSmartPointer<VAudioHandler>(new VAudioWindowsHandler());
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
