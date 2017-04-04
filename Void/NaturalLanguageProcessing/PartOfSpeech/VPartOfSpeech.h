#pragma once
#ifndef _V_PARTOFSPEECH_H_
#define _V_PARTOFSPEECH_H_

#include <map>
#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VPartOfSpeech
    //----------------------------------------------------------------------------------------------------
    enum class VPartOfSpeech
    {
        NONE = 0,
        NOUN, // n.
        ADJECTIVE, // adj.
        VERB, // v.
        SUBJECT, // s.
        NUMERAL, // num.
        PREPOSITION, // prep.
    };
    
    // VPartOfSpeechMapper
    //----------------------------------------------------------------------------------------------------
    class VPartOfSpeechMapper
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VPartOfSpeechMapper();
        VPartOfSpeechMapper(const VPartOfSpeechMapper& _mapper);
        ~VPartOfSpeechMapper();
        
        //----------------------------------------------------------------------------------------------------
        VPartOfSpeech PartOfSpeech(std::string _string);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        void Initialize();
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::map<std::string, VPartOfSpeech> mMapper;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VPartOfSpeechTest();
}

#endif
