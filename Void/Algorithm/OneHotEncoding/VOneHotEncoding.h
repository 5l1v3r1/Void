#pragma once
#ifndef _V_ONEHOTENCODING_H_
#define _V_ONEHOTENCODING_H_

#include "../../Structure/Any/VAny.h"
#include <vector>
#include <map>
#include <string>
#include <functional>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VOneHotEncoding
    // String-based: type map with lambda
    //----------------------------------------------------------------------------------------------------
    class VOneHotEncoding
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VOneHotEncoding();
        VOneHotEncoding(const VOneHotEncoding& _encoding);
        ~VOneHotEncoding();
        
        //----------------------------------------------------------------------------------------------------
        unsigned long Count() const;
        
        //----------------------------------------------------------------------------------------------------
        void Fit(const std::vector<VAny>& _features);
        void Fit(const unsigned long& _dimension, const std::vector<VAny>& _features);
        std::vector<float> TransformToFloats(const std::vector<VAny>& _features);
        std::string TransformToString(const std::vector<VAny>& _features);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        void Initialize();
        std::string ConvertFeature(const VAny& _feature);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        float mOnValue;
        float mOffValue;
        unsigned long mCount;
        std::map<unsigned long, std::map<std::string, unsigned long>> mCounters;
        std::map<std::string, std::function<std::string(const VAny&)>> mFeatureConverters;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VOneHotEncodingTest();
}

#endif
