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
    std::vector<std::string> Split(const std::string& _str, const std::string& _delimiter, bool isDiscardBlank=false)
    {
        std::vector<std::string> result;
        if (_delimiter.empty())
        {
            for (const char& ch : _str )
            {
                result.push_back(std::string(1, ch));
            }
            return result;
        }
        
        size_t last = 0;
        size_t index = _str.find_first_of(_delimiter, last);
        while (index != std::string::npos)
        {
            if (!isDiscardBlank || index != last)
            {
                result.push_back(_str.substr(last, index - last));
            }
            last = index + 1;
            index = _str.find_first_of(_delimiter, last);
        }
        if (0 < index - last)
        {
            result.push_back(_str.substr(last, index - last));
        }
        
        return result;
    }
    
    //----------------------------------------------------------------------------------------------------
    std::vector<std::string> Split(std::string _str, const std::regex& _delimiter, bool isDiscardBlank=false)
    {
        std::vector<std::string> result;
        std::smatch match;
        while (regex_search(_str, match, _delimiter))
        {
            size_t index = match.position();
            if (!isDiscardBlank || index != 0)
            {
                result.push_back(_str.substr(0, index));
            }
            _str = _str.substr(index + match.length());
        }
        if (_str.size())
        {
            result.push_back(_str);
        }
        
        return result;
    }
    
    //----------------------------------------------------------------------------------------------------
    std::vector<std::string> Match(const std::string& _str, const std::regex& _pattern)
    {
        std::vector<std::string> result;
        for (std::sregex_iterator it(_str.begin(), _str.end(), _pattern), end; it != end; ++it)
        {
            result.push_back(it->str());
        }
        
        return result;
    }
    
    //----------------------------------------------------------------------------------------------------
    std::string Replace(const std::string& _str, const std::regex& _pattern, const std::string& _new)
    {
        return std::regex_replace(_str, _pattern, _new);
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VStringTest()
    {
        std::string test("  1234   5  6   ");
        Trim(test);
        auto result = Split(test, std::string(" "), true);
        result = Split(test, std::regex("[ 3]"));
        result = Match(test, std::regex("[\\w]+"));
        
        return;
    }
}
