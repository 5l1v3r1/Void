#pragma once
#ifndef _V_CONSOLE_H_
#define _V_CONSOLE_H_

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VConsoleColor
    //----------------------------------------------------------------------------------------------------
    enum class VConsoleColor
    {
        NONE = 0, // Linux(39)
        BLACK, // Linux(30)
        RED, // Linux(31)
        GREEN, // Linux(32)
        YELLOW, // Linux(33)
        BLUE, // Linux(34)
        PURPLE, // Linux(35)
        DARK_GREEN, // Linux(36)
        WHITE,  // Linux(37)
    };
    
    // VConsoleBackgroundColor
    //----------------------------------------------------------------------------------------------------
    enum class VConsoleBackgroundColor
    {
        NONE = 0, // Linux(49)
        BLACK, // Linux(40)
        DARK_RED, // Linux(41)
        GREEN, // Linux(42)
        YELLOW, // Linux(43)
        BLUE, // Linux(44)
        PURPLE, // Linux(45)
        DARK_GREEN, // Linux(46)
        WHITE,  // Linux(47)
    };
    
    // VConsole
    //----------------------------------------------------------------------------------------------------
    class VConsole
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VConsole();
        VConsole(const VConsole& _console);
        ~VConsole();
        
        //----------------------------------------------------------------------------------------------------
        unsigned short Width();
        unsigned short Height();
        
        //----------------------------------------------------------------------------------------------------
        void RefreshSize();
        void Clear();
        void SetColor(VConsoleColor _color=VConsoleColor::NONE);
        void SetBackgroundColor(VConsoleBackgroundColor _color=VConsoleBackgroundColor::NONE);
        void Goto(unsigned short _x, unsigned short _y);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        void Initialize();
        
    protected:
        //----------------------------------------------------------------------------------------------------
        unsigned short mWidth;
        unsigned short mHeight;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VConsoleTest();
}

#endif
