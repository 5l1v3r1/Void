#include "VCorpusGameSkill.h"
#include <fstream>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VCorpusGameSkill
    //----------------------------------------------------------------------------------------------------
    VCorpusGameSkill::VCorpusGameSkill()
    {
        LoadFromFile();
    }
    
    //----------------------------------------------------------------------------------------------------
    VCorpusGameSkill::VCorpusGameSkill(const VCorpusGameSkill& _skill)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VCorpusGameSkill::~VCorpusGameSkill()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    std::vector<std::string> VCorpusGameSkill::RandomSkills(unsigned int count)
    {
        std::vector<std::string> result;
        //auto maxSize = mSkillComponents[VPartOfSpeech::ADJECTIVE].size() * (mSkillComponents[VPartOfSpeech::NOUN].size() + mSkillComponents[VPartOfSpeech::VERB].size());
        
        return result;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VCorpusGameSkill::LoadFromFile(const std::string& _fileName)
    {
        std::ifstream fin(_fileName);
        if (fin.is_open())
        {
            VPartOfSpeechMapper mapper;
            while (!fin.eof())
            {
                std::string partOfSpeech;
                std::string component;
                fin >> partOfSpeech >> component;
                if (!component.empty())
                {
                    mSkillComponents[mapper.PartOfSpeech(partOfSpeech)].push_back(component);
                }
            }
            
            fin.close();
            return true;
        }
        
        return false;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VCorpusGameSkillTest()
    {
        VCorpusGameSkill skill = VCorpusGameSkill();
        auto randomSkills = skill.RandomSkills();
        
        return;
    }
    
}
