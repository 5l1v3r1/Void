#include "VSoundex.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VSoundex
    //----------------------------------------------------------------------------------------------------
    VSoundex::VSoundex()
    {
        Initialize();
    }
    
    //----------------------------------------------------------------------------------------------------
    VSoundex::~VSoundex()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    std::string VSoundex::Encode(const std::string& _content)
    {
        std::string result;
        if (1 <= _content.size())
        {
            result.reserve(_content.size());
            result.push_back(toupper(_content[0]));
            if (2 <= _content.size())
            {
                for (int i = 1; i < _content.size(); ++i)
                {
                    char lastCode = Encode(toupper(_content[i]));
                    if (lastCode == '\0')
                    {
                        continue;
                    }
                    result.push_back(lastCode);
                    for (; i < _content.size() && result.size() < 4; ++i)
                    {
                        char code = Encode(toupper(_content[i]));
                        if (code != '\0' && lastCode != code)
                        {
                            result.push_back(code);
                            lastCode = code;
                        }
                    }
                    result.resize(4, '0');
                    break;
                }
            }
            
        }
        return result;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VSoundex::Initialize()
    {
        mCodingTable = {
            {'B', '1'}, {'F', '1'}, {'P', '1'}, {'V', '1'},
            {'C', '2'}, {'G', '2'}, {'J', '2'}, {'K', '2'}, {'Q', '2'}, {'S', '2'}, {'Z', '2'},
            {'D', '3'}, {'T', '3'},
            {'L', '4'},
            {'M', '5'}, {'N', '5'},
            {'R', '6'}
        };
    }
    
    //----------------------------------------------------------------------------------------------------
    char VSoundex::Encode(char _character)
    {
        auto iterator = mCodingTable.find(toupper(_character));
        if (iterator != mCodingTable.end())
        {
            return iterator->second;
        }
        return '\0';
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VSoundexTest()
    {
        VSoundex soundex;
        auto result = soundex.Encode("Knuth");
        result = soundex.Encode("Kant");
        
        return;
    }
    
}
