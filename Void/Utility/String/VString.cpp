#include "VString.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VString
    //----------------------------------------------------------------------------------------------------
    std::string& Trim(std::string& _str)
    {
        if (_str.empty())
        {
            return _str;
        }
        
        _str.erase(0, _str.find_first_not_of(" "));
        _str.erase(_str.find_last_not_of(" ") + 1);
        return _str;
    }
    
    //----------------------------------------------------------------------------------------------------
    std::vector<std::string> Split(std::string& _str, const std::string& _delimiter)
    {
        std::vector<std::string> result;
        if (_delimiter.empty())
        {
            for (char& ch : _str )
            {
                result.push_back(std::string(1, ch));
            }
            return result;
        }
        
        size_t last = 0;
        size_t index = _str.find_first_of(_delimiter, last);
        while (index != std::string::npos)
        {
            result.push_back(_str.substr(last, index - last));
            last = index + 1;
            index = _str.find_first_of(_delimiter, last);
        }
        if (0 < index - last)
        {
            result.push_back(_str.substr(last, index - last));
        }
        
        return result;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VStringTest()
    {
        std::string test(" 1234  5  6   ");
        Trim(test);
        auto result = Split(test, std::string(""));
        
        return;
    }
}
