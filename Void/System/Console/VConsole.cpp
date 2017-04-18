#include "VConsole.h"
#include "../../Utility/Logger/VLogger.h"
#include <stdlib.h>
#if defined(WIN32) || defined(WIN64) || defined(_WIN32_WCE)
#
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VConsole
    //----------------------------------------------------------------------------------------------------
    VConsole::VConsole()
    {
        Initialize();
    }
    
    //----------------------------------------------------------------------------------------------------
    VConsole::VConsole(const VConsole& _console)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VConsole::~VConsole()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    unsigned short VConsole::Width()
    {
        return mWidth;
    }
    
    //----------------------------------------------------------------------------------------------------
    unsigned short VConsole::Height()
    {
        return mHeight;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VConsole::RefreshSize()
    {
        #if defined(WIN32) || defined(WIN64) || defined(_WIN32_WCE)
        #
        #else
        struct winsize size;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
        mWidth = size.ws_col;
        mHeight = size.ws_row;
        #endif
    }
    
    
    //----------------------------------------------------------------------------------------------------
    void VConsole::Clear()
    {
        #if defined(WIN32) || defined(WIN64) || defined(_WIN32_WCE)
        system("cls");
        #else
        system("clear");
        #endif
    }
    
    //----------------------------------------------------------------------------------------------------
    void VConsole::Initialize()
    {
        RefreshSize();
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VConsoleTest()
    {
        VConsole console;
        console.Clear();
        VLogger::Info("Console width: %u", console.Width());
        VLogger::Info("Console height: %u", console.Height());
        
        return;
    }
    
}
