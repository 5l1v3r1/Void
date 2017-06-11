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
        None = 0,
        
        Noun, // n.
        Pronoun, // pron.
        Adjective, // adj.
        Verb, // v.
        Adverb, // ad.
        Preposition, // prep.
        Conjunction, // conj.
        Interjection, // int.
        Article, // art.
        Numeral, // num.
        
        Subject, // s.
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
