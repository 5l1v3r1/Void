#include "VCorpusGameSkill.h"
#include "../../../Utility/Random/VRandom.h"
#include <fstream>
#include <vector>

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
    std::vector<std::string> VCorpusGameSkill::RandomSkills(unsigned int _count)
    {
        std::vector<std::string> result;
        unsigned int maxPrefix = (unsigned int)mSkillComponents[VPartOfSpeech::ADJECTIVE].size();
        unsigned int maxNSuffix = (unsigned int)mSkillComponents[VPartOfSpeech::NOUN].size();
        unsigned int maxVSuffix = (unsigned int)mSkillComponents[VPartOfSpeech::VERB].size();
        unsigned int maxSuffix = maxNSuffix + maxVSuffix;
        unsigned int maxSize = maxPrefix * maxSuffix;
        if (maxSize < _count)
        {
            _count = maxSize;
        }
        
        VRandom random;
        std::vector<int> indexes = random.MultipleUniqueRand(_count, 0, maxSize - 1);
        for (int index : indexes)
        {
            std::string prefix = mSkillComponents[VPartOfSpeech::ADJECTIVE][index / maxSuffix];
            std::string suffix = index % maxSuffix < maxNSuffix ? mSkillComponents[VPartOfSpeech::NOUN][index % maxSuffix] : mSkillComponents[VPartOfSpeech::VERB][index % maxSuffix - maxNSuffix];
            result.push_back(prefix + suffix);
        }
        
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
        randomSkills = skill.RandomSkills(3);
        randomSkills = skill.RandomSkills(5);
        randomSkills = skill.RandomSkills(15);
        randomSkills = skill.RandomSkills(100);
        
        return;
    }
    
}
