#include "VPartOfSpeech.h"
#include "../../Utility/String/VString.h"
#include <algorithm>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VCorpusGameSkill
    //----------------------------------------------------------------------------------------------------
    VPartOfSpeechMapper::VPartOfSpeechMapper()
    {
        Initialize();
    }
    
    //----------------------------------------------------------------------------------------------------
    VPartOfSpeechMapper::VPartOfSpeechMapper(const VPartOfSpeechMapper& _mapper)
        :
        mMapper(_mapper.mMapper)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VPartOfSpeechMapper::~VPartOfSpeechMapper()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VPartOfSpeech VPartOfSpeechMapper::PartOfSpeech(std::string _string)
    {
        std::transform(_string.begin(), _string.end(), _string.begin(), ::tolower);
        _string = Replace(_string, std::regex("[^a-z]"), "");
        auto it = mMapper.find(_string);
        if (it != mMapper.end())
        {
            return it->second;
        }
        return VPartOfSpeech::NONE;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VPartOfSpeechMapper::Initialize()
    {
        mMapper["n"] = VPartOfSpeech::NOUN;
        mMapper["adj"] = VPartOfSpeech::ADJECTIVE;
        mMapper["v"] = VPartOfSpeech::VERB;
        mMapper["s"] = VPartOfSpeech::SUBJECT;
        mMapper["num"] = VPartOfSpeech::NUMERAL;
        mMapper["prep"] = VPartOfSpeech::PREPOSITION;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VPartOfSpeechTest()
    {
        VPartOfSpeechMapper mapper = VPartOfSpeechMapper();
        auto test = mapper.PartOfSpeech("n");
        test = mapper.PartOfSpeech("V");
        test = mapper.PartOfSpeech("!@num.!@");
        test = mapper.PartOfSpeech("");
        
        return;
    }
    
}
