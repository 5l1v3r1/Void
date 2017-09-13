#pragma once
#ifndef _V_JSONPARSER_H_
#define _V_JSONPARSER_H_

#include "./VJSONValue.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VJSONParserMode
    //----------------------------------------------------------------------------------------------------
    enum class VJSONParserMode
    {
        Strict = true,
        Permissive = false
    };
    
    // VJSONParser
    // JavaScript Object Notation
    // Request for Comments: 7159
    //----------------------------------------------------------------------------------------------------
    // Structural Characters: [ ] { } : ,
    // Whitespace: %x20 %x09 %x0A %x0D
    // Values: false / null / true / object / array / number / string
    //         ------------------------------------------------------
    //         Object: { [string: value]... }
    //         Array: [ value... ]
    //         Number: [ minus ] int [ frac ] [ exp ]
    //         String: quotation-mark char... quotation-mark
    //----------------------------------------------------------------------------------------------------
    class VJSONParser
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VJSONParser();
        VJSONParser(const VJSONParser& _parser);
        virtual ~VJSONParser();
        
        //----------------------------------------------------------------------------------------------------
        bool Parse(const std::string& _input, VJSONValue& _output);
        std::string Dump(const VJSONValue& _input);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        bool ParseValue(std::istream& _input, VJSONValue& _output);
        bool ParserNull(std::istream& _input, VJSONValue& _output);
        bool ParserBool(std::istream& _input, VJSONValue& _output);
        bool ParserObject(std::istream& _input, VJSONValue& _output);
        bool ParserArray(std::istream& _input, VJSONValue& _output);
        bool ParserNumber(std::istream& _input, VJSONValue& _output);
        bool ParserString(std::istream& _input, VJSONValue& _output);
        bool ParserIdentifier(std::istream& _input, VJSONValue& _ouput);
        
        //----------------------------------------------------------------------------------------------------
        void DumpValue(const VJSONValue& _input, std::string& _ouput);
        void DumpNull(const VJSONValue& _input, std::string& _ouput);
        void DumpBool(const VJSONValue& _input, std::string& _ouput);
        void DumpObject(const VJSONValue& _input, std::string& _ouput);
        void DumpArray(const VJSONValue& _input, std::string& _ouput);
        void DumpNumber(const VJSONValue& _input, std::string& _ouput);
        void DumpString(const VJSONValue& _input, std::string& _ouput);
        std::string EscapeString(const std::string& _input);
        
    protected:
        VJSONParserMode mMode;
        std::vector<std::string> mEscapeMap;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VJSONParserTest();
}

#endif
