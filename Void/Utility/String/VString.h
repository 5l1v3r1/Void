#pragma once
#ifndef _V_STRING_H_
#define _V_STRING_H_

#include <string>
#include <vector>
#include <regex>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VString
    //----------------------------------------------------------------------------------------------------
    std::string& Trim(std::string& _str); // strip
    std::vector<std::string> Split(const std::string& _str, const std::string& _delimiter);
    std::vector<std::string> Match(const std::string& _str, const std::regex& _pattern);
    std::string Replace(const std::string& _str, const std::regex& _pattern, const std::string& _new);
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VStringTest();
}

#endif
