#pragma once
#ifndef _V_TFIDF_H_
#define _V_TFIDF_H_

#include <vector>
#include <map>
#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VTFIDF
    // Term Frequency - Inverse Document Frequency
    // TF = {word | word ∈ words} / words
    // IDF = log(documents / ({document | word ∈ document} + 1))
    // TF-IDF = TF * IDF
    //----------------------------------------------------------------------------------------------------
    class VTFIDF
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VTFIDF();
        virtual ~VTFIDF();
        
        //----------------------------------------------------------------------------------------------------
        void AddDocument(const std::string& _name, const std::vector<std::string>& _words);
        std::map<std::string, float> Calculate(const std::string& _name);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::map<std::string, std::map<std::string, float>> mTermFrequencies;
        std::map<std::string, unsigned int> mIDCounter;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VTFIDFTest();
}

#endif
