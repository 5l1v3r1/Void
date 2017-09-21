#include "VTFIDF.h"
#include "../../Utility/String/VString.h"
#include <cmath>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VTFIDF
    //----------------------------------------------------------------------------------------------------
    VTFIDF::VTFIDF()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VTFIDF::~VTFIDF()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    void VTFIDF::AddDocument(const std::string& _name, const std::vector<std::string>& _words)
    {
        std::map<std::string, float>& termFrequency = mTermFrequencies[_name];
        if (termFrequency.size())
        {
            for (auto& item : termFrequency)
            {
                auto count = mIDCounter.find(item.first);
                count->second -= 1;
                if (count->second == 0)
                {
                    mIDCounter.erase(count);
                }
            }
        }
        termFrequency.clear();
        
        // Count
        for (const std::string& word : _words)
        {
            auto term = termFrequency.find(word);
            if (term == termFrequency.end())
            {
                termFrequency.insert(std::pair<std::string, float>(word, 1.f));
                auto count = mIDCounter.find(word);
                if (count == mIDCounter.end())
                {
                    mIDCounter.insert(std::pair<std::string, float>(word, 1));
                }
                else
                {
                    count->second += 1;
                }
            }
            else
            {
                term->second += 1.f;
            }
        }
        // Normalize
        if (!_words.empty())
        {
            float reciprocalSize = 1.f / _words.size();
            for (auto& item : termFrequency)
            {
                item.second *= reciprocalSize;
            }
        }
    }
    
    //----------------------------------------------------------------------------------------------------
    std::map<std::string, float> VTFIDF::Calculate(const std::string& _name)
    {
        std::map<std::string, float>& termFrequency = mTermFrequencies[_name];
        std::map<std::string, float> result;
        float logDocuments = std::logf(mTermFrequencies.size());
        for (auto& item : termFrequency)
        {
            result[item.first] = item.second * (logDocuments - std::logf(mIDCounter[item.first]));
        }
        return result;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VTFIDFTest()
    {
        VTFIDF tfidf;
        tfidf.AddDocument("document0", Split("You've got to be careful with this delicacy or you might end up in the morgue.", std::regex("[ .]+"), true));
        tfidf.AddDocument("document1", Split("The deadly puffer fish is the ultimate delicacy in Japan, even though its skin and insides contain the poisonous toxin tetrodotoxin, which is 1250 times stronger than cyanide.", std::regex("[ .]+"), true));
        auto result = tfidf.Calculate("document0");
        return;
    }
    
}
