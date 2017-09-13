#include "VJSONParser.h"
#include <sstream>
#include <iomanip>
#include <assert.h>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VJSONParser
    //----------------------------------------------------------------------------------------------------
    VJSONParser::VJSONParser()
        :
        mMode(VJSONParserMode::Permissive)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VJSONParser::VJSONParser(const VJSONParser& _parser)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VJSONParser::~VJSONParser()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VJSONParser::Parse(const std::string& _input, VJSONValue& _output)
    {
        std::istringstream stream(_input);
        if (ParserBool(stream, _output) || ParserNull(stream, _output) || ParserObject(stream, _output) || ParserArray(stream, _output) || ParserNumber(stream, _output) || ParserString(stream, _output))
        {
            stream >> std::ws;
            if (!stream.eof())
            {
                return false;
            }
            return true;
        }
        return false;
    }
    
    // Detect loop
    //----------------------------------------------------------------------------------------------------
    std::string VJSONParser::Dump(const VJSONValue& _input)
    {
        std::string output;
        DumpValue(_input, output);
        return output;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VJSONParser::ParseValue(std::istream& _input, VJSONValue& _output)
    {
        if (ParserBool(_input, _output) || ParserNull(_input, _output) || ParserObject(_input, _output) || ParserArray(_input, _output) || ParserNumber(_input, _output) || ParserString(_input, _output))
        {
            return true;
        }
        return false;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VJSONParser::ParserNull(std::istream& _input, VJSONValue& _output)
    {
        _input >> std::ws;
        std::streampos rollback = _input.tellg();
        char character = _input.peek();
        if (character == 'n')
        {
            for (int i = 0; i < 4; ++i)
            {
                _input.get(character);
                if (character != "null"[i])
                {
                    _input.clear();
                    _input.seekg(rollback);
                    return false;
                }
            }
        }
        else
        {
            return false;
        }
        _output.Clear();
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VJSONParser::ParserBool(std::istream& _input, VJSONValue& _output)
    {
        _input >> std::ws;
        std::streampos rollback = _input.tellg();
        char character = _input.peek();
        if (character == 't')
        {
            for (int i = 0; i < 4; ++i)
            {
                _input.get(character);
                if (character != "true"[i])
                {
                    _input.clear();
                    _input.seekg(rollback);
                    return false;
                }
            }
            _output = true;
        }
        else if (character == 'f')
        {
            for (int i = 0; i < 5; ++i)
            {
                _input.get(character);
                if (character != "false"[i])
                {
                    _input.clear();
                    _input.seekg(rollback);
                    return false;
                }
            }
            _output = false;
        }
        else
        {
            return false;
        }
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VJSONParser::ParserObject(std::istream& _input, VJSONValue& _output)
    {
        // Prepare
        _input >> std::ws;
        std::streampos rollback = _input.tellg();
        char character = _input.peek();
        if (character != '{')
        {
            return false;
        }
        _output = std::map<std::string, VJSONValue>();
        
        // Process
        _input.get(character);
        _input >> std::ws;
        if (_input.peek() == '}')
        {
            _input.get(character);
            return true;
        }
        while (!_input.eof() && _input.good())
        {
            // Identifier
            VJSONValue identifier;
            if (!((mMode == VJSONParserMode::Permissive && ParserIdentifier(_input, identifier)) || ParserString(_input, identifier)))
            {
                break;
            }
            // ':'
            _input >> std::ws;
            _input.get(character);
            if (character != ':')
            {
                break;
            }
            // Value
            if (!ParseValue(_input, _output[identifier.String()]))
            {
                break;
            }
            // ',' or '}'
            _input >> std::ws;
            _input.get(character);
            if (character == ',')
            {
                continue;
            }
            else if (character == '}')
            {
                // Close
                return true;
            }
            else
            {
                break;
            }
        }
        _input.clear();
        _input.seekg(rollback);
        return false;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VJSONParser::ParserArray(std::istream& _input, VJSONValue& _output)
    {
        // Prepare
        _input >> std::ws;
        std::streampos rollback = _input.tellg();
        char character = _input.peek();
        if (character != '[')
        {
            return false;
        }
        _output = std::vector<VJSONValue>();
        
        // Process
        _input.get(character);
        _input >> std::ws;
        if (_input.peek() == ']')
        {
            _input.get(character);
            return true;
        }
        while (!_input.eof() && _input.good())
        {
            // Value
            VJSONValue value;
            if (!ParseValue(_input, value))
            {
                break;
            }
            _output.PushBack(value);
            // ',' or ']'
            _input >> std::ws;
            _input.get(character);
            if (character == ',')
            {
                continue;
            }
            else if (character == ']')
            {
                // Close
                return true;
            }
            else
            {
                break;
            }
        }
        _input.clear();
        _input.seekg(rollback);
        return false;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VJSONParser::ParserNumber(std::istream& _input, VJSONValue& _output)
    {
        _input >> std::ws;
        std::streampos rollback = _input.tellg();
        _output = (long double)(0);
        _input >> _output.Number();
        if (_input.fail())
        {
            _input.clear();
            _input.seekg(rollback);
            return false;
        }
        return true;
    }
    
    // Strict: wx "character..." wx
    // Permissive:  wx ("character..." or 'character...') wx
    //----------------------------------------------------------------------------------------------------
    bool VJSONParser::ParserString(std::istream& _input, VJSONValue& _output)
    {
        // Prepare
        _input >> std::ws;
        std::streampos rollback = _input.tellg();
        char delimiter = _input.peek();
        if (delimiter != '"' && (mMode == VJSONParserMode::Permissive && delimiter != '\''))
        {
            return false;
        }
        _output = std::string();
        
        // Process
        char character = 0;
        _input.get(character);
        while (!_input.eof() && _input.good())
        {
            _input.get(character);
            if (character == delimiter)
            {
                // Close
                return true;
            }
            else if (character == '\\')
            {
                _input.get(character);
                switch (character)
                {
                    case '\\':
                    case '/':
                        _output.PushBack(character);
                        break;
                    case 'b':
                        _output.PushBack('\b');
                        break;
                    case 'f':
                        _output.PushBack('\f');
                        break;
                    case 'n':
                        _output.PushBack('\n');
                        break;
                    case 'r':
                        _output.PushBack('\r');
                        break;
                    case 't':
                        _output.PushBack('\t');
                        break;
                    case 'u':
                    {
                        std::stringstream ss;
                        for(int i = 0; i < 4 && !_input.eof() && _input.good(); ++i)
                        {
                            _input.get(character);
                            ss << std::hex << character;
                        }
                        int value = 0;
                        ss >> value;
                        _output.PushBack(static_cast<char>(value));
                        break;
                    }
                    default:
                        if (character != delimiter)
                        {
                            _output.PushBack('\\');
                        }
                        _output.PushBack(character);
                        break;
                }
            }
            else
            {
                _output.PushBack(character);
            }
        }
        _input.clear();
        _input.seekg(rollback);
        return false;
    }
    
    // For permissive mode
    //----------------------------------------------------------------------------------------------------
    bool VJSONParser::ParserIdentifier(std::istream& _input, VJSONValue& _output)
    {
        // Prepare
        _input >> std::ws;
        std::streampos rollback = _input.tellg();
        char character = _input.peek();
        if (!(character == '_' || character == '$' || ('a' <= character && character <= 'z') || ('A' <= character && character <= 'Z')))
        {
            return false;
        }
        _output = std::string();
        
        // Process
        while (!_input.eof() && _input.good())
        {
            _input.get(character);
            if (character == ':')
            {
                // Close
                _input.unget();
                return true;
            }
            else if (character == '_' || character == '$' || ('a' <= character && character <= 'z') || ('A' <= character && character <= 'Z') || ('0' <= character && character <= '9'))
            {
                _output.PushBack(character);
            }
            else if (character == ' ' || character == '\t')
            {
                _input >> std::ws;
                if (_input.peek() == ':')
                {
                    return true;
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        _input.clear();
        _input.seekg(rollback);
        return false;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VJSONParser::DumpValue(const VJSONValue& _input, std::string& _ouput)
    {
        switch (_input.Type())
        {
            case VJSONValueType::Null:
                DumpNull(_input, _ouput);
                break;
            case VJSONValueType::Boolean:
                DumpBool(_input, _ouput);
                break;
            case VJSONValueType::Object:
                DumpObject(_input, _ouput);
                break;
            case VJSONValueType::Array:
                DumpArray(_input, _ouput);
                break;
            case VJSONValueType::Number:
                DumpNumber(_input, _ouput);
                break;
            case VJSONValueType::String:
                DumpString(_input, _ouput);
                break;
            default:
                // Error
                break;
        }
    }
    
    //----------------------------------------------------------------------------------------------------
    void VJSONParser::DumpNull(const VJSONValue& _input, std::string& _ouput)
    {
        if (_input.Null())
        {
            _ouput += "null";
        }
        // Throw
    }
    
    //----------------------------------------------------------------------------------------------------
    void VJSONParser::DumpBool(const VJSONValue& _input, std::string& _ouput)
    {
        _ouput += _input.Boolean() ? "true" : "false";
    }
    
    //----------------------------------------------------------------------------------------------------
    void VJSONParser::DumpObject(const VJSONValue& _input, std::string& _ouput)
    {
        const std::map<std::string, VJSONValue>& object = _input.Object();
        _ouput += '{';
        if (object.size())
        {
            for (auto pair : object)
            {
                _ouput += '"' + EscapeString(pair.first) + '"';
                _ouput += ':';
                DumpValue(pair.second, _ouput);
                _ouput += ',';
            }
            _ouput.pop_back();
        }
        _ouput += '}';
    }
    
    //----------------------------------------------------------------------------------------------------
    void VJSONParser::DumpArray(const VJSONValue& _input, std::string& _ouput)
    {
        const std::vector<VJSONValue>& array = _input.Array();
        _ouput += '[';
        if (array.size())
        {
            for (auto value : array)
            {
                DumpValue(value, _ouput);
                _ouput += ',';
            }
            _ouput.pop_back();
        }
        _ouput += ']';

    }
    
    //----------------------------------------------------------------------------------------------------
    void VJSONParser::DumpNumber(const VJSONValue& _input, std::string& _ouput)
    {
        std::stringstream ss;
        ss << std::setprecision(std::numeric_limits<long double>::digits10 + 1) << _input.Number();
        _ouput += ss.str();
    }
    
    //----------------------------------------------------------------------------------------------------
    void VJSONParser::DumpString(const VJSONValue& _input, std::string& _ouput)
    {
        _ouput += '"' + EscapeString(_input.String()) + '"';
    }
    
    //----------------------------------------------------------------------------------------------------
    std::string VJSONParser::EscapeString(const std::string& _input)
    {
        // Prepare
        if (mEscapeMap.size() < 256)
        {
            mEscapeMap.clear();
            mEscapeMap.reserve(256);
            for (int i = 0; i < 255; ++i)
            {
                mEscapeMap.push_back(std::string(1, static_cast<char>(i)));
            }
            for (int i = 0; i < 32; ++i)
            {
                std::stringstream ss;
                ss << "\\u" << std::hex << std::setw(4) << std::setfill('0') << i;
                mEscapeMap[i] = ss.str();
            }
            mEscapeMap[(int)'"'] = "\\\"";
            mEscapeMap[(int)'\\'] = "\\\\";
            mEscapeMap[(int)'/'] = "\\/";
            mEscapeMap[(int)'\b'] = "\\b";
            mEscapeMap[(int)'\f'] = "\\f";
            mEscapeMap[(int)'\n'] = "\\n";
            mEscapeMap[(int)'\r'] = "\\r";
            mEscapeMap[(int)'\r'] = "\\t";
        }
        
        // Process
        std::string output;
        output.reserve(_input.size() * 2 + 2);
        for (auto it = _input.begin(); it != _input.end(); ++it)
        {
            output += mEscapeMap[(int)*it];
        }
        return output;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VJSONParserTest()
    {
        std::string string;
        VJSONParser parser;
        VJSONValue value;
        string = "";
        assert(!parser.Parse(string, value));
        string = " null";
        assert(parser.Parse(string, value));
        string = "true";
        assert(parser.Parse(string, value));
        string = "false ";
        assert(parser.Parse(string, value));
        string = " \"xixixixi\\u0011\\n\\r\"  ";
        assert(parser.Parse(string, value));
        string = parser.Dump(value);
        string =
        "{demo:{"
        "string_test:\"xixixi 123\","
        "object_test:{},"
        "array_test:[1.2345,5.4321]"
        "}}";
        assert(parser.Parse(string, value));
        string = parser.Dump(value);
        
        return;
    }
    
}
