#pragma once
#ifndef _V_CORPUSGAMESKILL_H_
#define _V_CORPUSGAMESKILL_H_

#include "../../PartOfSpeech/VPartOfSpeech.h"
#include <map>
#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VCorpusGameSkill
    //----------------------------------------------------------------------------------------------------
    class VCorpusGameSkill
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VCorpusGameSkill();
        VCorpusGameSkill(const VCorpusGameSkill& _skill);
        ~VCorpusGameSkill();
        
        //----------------------------------------------------------------------------------------------------
        std::vector<std::string> RandomSkills(unsigned int count=1);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        bool LoadFromFile(const std::string& _fileName="./NaturalLanguageProcessing/Corpus/CorpusGameSkill/VGameSkill.vd");
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::map<VPartOfSpeech, std::vector<std::string>> mSkillComponents;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VCorpusGameSkillTest();
}

#endif
