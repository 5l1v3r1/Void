#include "VOneHotEncoding.h"
#include <sstream>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VOneHotEncoding
    //----------------------------------------------------------------------------------------------------
    VOneHotEncoding::VOneHotEncoding()
        :
        mOnValue(1.f),
        mOffValue(0),
        mCount(0),
        mCounters(),
        mFeatureConverters()
    {
        Initialize();
    }
    
    //----------------------------------------------------------------------------------------------------
    VOneHotEncoding::VOneHotEncoding(const VOneHotEncoding& _encoding)
        :
        mOnValue(_encoding.mOnValue),
        mOffValue(_encoding.mOffValue),
        mCount(_encoding.mCount),
        mCounters(_encoding.mCounters),
        mFeatureConverters(_encoding.mFeatureConverters)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VOneHotEncoding::~VOneHotEncoding()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    unsigned long VOneHotEncoding::Count() const
    {
        return mCount;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VOneHotEncoding::Fit(const std::vector<VAny>& _features)
    {
        for (unsigned long dimension = 0; dimension < _features.size(); ++dimension)
        {
            const VAny& feature = _features[dimension];
            auto& counter = mCounters[dimension];
            std::string processedFeature = ConvertFeature(feature);
            if (!processedFeature.empty())
            {
                // Count
                if (counter.find(processedFeature) == counter.end())
                {
                    counter[processedFeature] = counter.size();
                    ++mCount;
                }
            }
        }
        
        return;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VOneHotEncoding::Fit(const unsigned long& _dimension, const std::vector<VAny>& _features)
    {
        auto& counter = mCounters[_dimension];
        for (const VAny& feature : _features)
        {
            std::string processedFeature = ConvertFeature(feature);
            if (!processedFeature.empty())
            {
                // Count
                if (counter.find(processedFeature) == counter.end())
                {
                    counter[processedFeature] = counter.size();
                    ++mCount;
                }
            }
        }
    }
    
    //----------------------------------------------------------------------------------------------------
    std::vector<float> VOneHotEncoding::TransformToFloats(const std::vector<VAny>& _features)
    {
        std::vector<float> result(mCount, mOffValue);
        unsigned long index = 0;
        for (unsigned long dimension = 0; dimension < _features.size(); ++dimension)
        {
            const VAny& feature = _features[dimension];
            auto& counter = mCounters[dimension];
            std::string processedFeature = ConvertFeature(feature);
            if (!processedFeature.empty())
            {
                auto code = counter.find(processedFeature);
                if (code != counter.end())
                {
                    result[index + code->second] = mOnValue;
                }
            }
            index += counter.size();
        }
        return result;
    }
    
    // On value: '0'
    // Off value: '1'
    //----------------------------------------------------------------------------------------------------
    std::string VOneHotEncoding::TransformToString(const std::vector<VAny>& _features)
    {
        std::string result(mCount, '0');
        unsigned long index = 0;
        for (unsigned long dimension = 0; dimension < _features.size(); ++dimension)
        {
            const VAny& feature = _features[dimension];
            auto& counter = mCounters[dimension];
            std::string processedFeature = ConvertFeature(feature);
            if (!processedFeature.empty())
            {
                auto code = counter.find(processedFeature);
                if (code != counter.end())
                {
                    result[index + code->second] = '1';
                }
            }
            index += counter.size();
        }
        return result;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VOneHotEncoding::Initialize()
    {
        mFeatureConverters[typeid(int).name()] = [](const VAny& _feature)->std::string
        {
            std::stringstream sstream;
            sstream << VAnyCast<int>(_feature);
            return sstream.str();
        };
        mFeatureConverters[typeid(unsigned).name()] = [](const VAny& _feature)->std::string
        {
            std::stringstream sstream;
            sstream << VAnyCast<unsigned>(_feature);
            return sstream.str();
        };
        mFeatureConverters[typeid(long).name()] = [](const VAny& _feature)->std::string
        {
            std::stringstream sstream;
            sstream << VAnyCast<long>(_feature);
            return sstream.str();
        };
        mFeatureConverters[typeid(unsigned long).name()] = [](const VAny& _feature)->std::string
        {
            std::stringstream sstream;
            sstream << VAnyCast<unsigned long>(_feature);
            return sstream.str();
        };
        mFeatureConverters[typeid(long long).name()] = [](const VAny& _feature)->std::string
        {
            std::stringstream sstream;
            sstream << VAnyCast<long long>(_feature);
            return sstream.str();
        };
        mFeatureConverters[typeid(unsigned long long).name()] = [](const VAny& _feature)->std::string
        {
            std::stringstream sstream;
            sstream << VAnyCast<unsigned long long>(_feature);
            return sstream.str();
        };
        mFeatureConverters[typeid(std::string).name()] = [](const VAny& _feature)->std::string
        {
            return VAnyCast<std::string>(_feature);
        };
        mFeatureConverters[typeid(bool).name()] = [](const VAny& _feature)->std::string
        {
            return VAnyCast<bool>(_feature) ? "true" : "false";
        };
    }
    
    //----------------------------------------------------------------------------------------------------
    std::string VOneHotEncoding::ConvertFeature(const VAny& _feature)
    {
        auto converter = mFeatureConverters.find(_feature.Type().name());
        if (converter != mFeatureConverters.end())
        {
            return converter->second(_feature);
        }
        return std::string();
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VOneHotEncodingTest()
    {
        VOneHotEncoding encoding;
        std::vector<VAny> features0;
        features0.push_back(-1);
        features0.push_back(123U);
        features0.push_back(123456L);
        features0.push_back(123456789LL);
        features0.push_back(std::string("xixi"));
        features0.push_back(true);
        features0.push_back(false);
        encoding.Fit(features0);
        std::vector<VAny> features1;
        features1.push_back(0);
        features1.push_back(123U);
        features1.push_back(123456L);
        features1.push_back(123456789LL);
        features1.push_back(std::string("hehe"));
        features1.push_back(false);
        features1.push_back(true);
        encoding.Fit(features1);
        encoding.Fit(0, features1);
        std::string stringCode = encoding.TransformToString(features1);
        stringCode = encoding.TransformToString(features0);
        
        return;
    }
    
}
