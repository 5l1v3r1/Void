#include "VConsole.h"
#include "../../Utility/Logger/VLogger.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#if defined(_WIN32) || defined(_WIN64) || defined(_WIN32_WCE)
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
    void VConsole::SetColor(VConsoleColor _color)
    {
        #if defined(WIN32) || defined(WIN64) || defined(_WIN32_WCE)
        #
        #else
        switch (_color) {
            case VConsoleColor::BLACK:
                fputs("\033[30m", stderr);
                break;
            case VConsoleColor::RED:
                fputs("\033[31m", stderr);
                break;
            case VConsoleColor::GREEN:
                fputs("\033[32m", stderr);
                break;
            case VConsoleColor::YELLOW:
                fputs("\033[33m", stderr);
                break;
            case VConsoleColor::BLUE:
                fputs("\033[34m", stderr);
                break;
            case VConsoleColor::PURPLE:
                fputs("\033[35m", stderr);
                break;
            case VConsoleColor::DARK_GREEN:
                fputs("\033[36m", stderr);
                break;
            case VConsoleColor::WHITE:
                fputs("\033[37m", stderr);
                break;
            case VConsoleColor::NONE:
            default:
                fputs("\033[39m", stderr);
                break;
        }
        #endif
    }
    
    //----------------------------------------------------------------------------------------------------
    void VConsole::SetBackgroundColor(VConsoleBackgroundColor _color)
    {
        #if defined(WIN32) || defined(WIN64) || defined(_WIN32_WCE)
        #
        #else
        switch (_color) {
            case VConsoleBackgroundColor::BLACK:
                fputs("\033[40m", stderr);
                break;
            case VConsoleBackgroundColor::DARK_RED:
                fputs("\033[41m", stderr);
                break;
            case VConsoleBackgroundColor::GREEN:
                fputs("\033[42m", stderr);
                break;
            case VConsoleBackgroundColor::YELLOW:
                fputs("\033[43m", stderr);
                break;
            case VConsoleBackgroundColor::BLUE:
                fputs("\033[44m", stderr);
                break;
            case VConsoleBackgroundColor::PURPLE:
                fputs("\033[45m", stderr);
                break;
            case VConsoleBackgroundColor::DARK_GREEN:
                fputs("\033[46m", stderr);
                break;
            case VConsoleBackgroundColor::WHITE:
                fputs("\033[47m", stderr);
                break;
            case VConsoleBackgroundColor::NONE:
            default:
                fputs("\033[49m", stderr);
                break;
        }
        #endif
    }
    
    //----------------------------------------------------------------------------------------------------
    void VConsole::Goto(unsigned short _x, unsigned short _y)
    {
        #if defined(WIN32) || defined(WIN64) || defined(_WIN32_WCE)
        #
        #else
        std::stringstream sstream;
        sstream << "\033[" << _x << ';' << _y << 'H';
        fputs(sstream.str().c_str(), stderr);
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
        // console.SetColor(VConsoleColor::RED);
        // console.SetBackgroundColor(VConsoleBackgroundColor::DARK_GREEN);
        // console.Clear();
        // console.Goto(1, 1);
        VLogger::Info("Console width: %u", console.Width());
        VLogger::Info("Console height: %u", console.Height());
        // console.SetColor();
        // console.SetBackgroundColor();
        
        return;
    }
    
}
