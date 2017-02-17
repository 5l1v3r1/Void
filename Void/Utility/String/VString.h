#pragma once
#ifndef _V_STRING_H_
#define _V_STRING_H_

#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VString
    //----------------------------------------------------------------------------------------------------
    std::string& Trim(std::string& _str);
    std::vector<std::string> Split(std::string& _str, std::string& _delimiter);
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VStringTest();
}

#endif
