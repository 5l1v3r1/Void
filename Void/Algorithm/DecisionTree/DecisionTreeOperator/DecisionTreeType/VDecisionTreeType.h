#pragma once
#ifndef _V_DECISIONTREETYPE_H_
#define _V_DECISIONTREETYPE_H_

#include "../../../../Structure/Any/VAny.h"
#include <vector>
#include <map>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VDecisionTreeType
    // Classifier, Regressor
    //----------------------------------------------------------------------------------------------------
    enum class VDecisionTreeType
    {
        Classifier,
        Regressor
    };
    
    // VDecisionTreeTypeOperator
    //----------------------------------------------------------------------------------------------------
    template<typename _T, VDecisionTreeType _I>
    class VDecisionTreeTypeOperator
    {
    };
    
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VDecisionTreeTypeOperator<_T, VDecisionTreeType::Classifier>
    {
    protected:
        //----------------------------------------------------------------------------------------------------
        std::map<_T, unsigned> Count(const std::vector<std::pair<std::vector<VAny>, _T>*>& _samples)
        {
            std::map<_T, unsigned> counter;
            for (auto& sample : _samples)
            {
                counter[sample->second] += 1;
            }
            return counter; // Move
        }
        
        //----------------------------------------------------------------------------------------------------
        _T Label(const std::vector<std::pair<std::vector<VAny>, _T>*>& _samples)
        {
            std::map<_T, unsigned> counter = Count(_samples);
            _T label;
            unsigned maxCount = 0;
            for (auto& pair : counter)
            {
                if (maxCount < pair.second)
                {
                    maxCount = pair.second;
                    label = pair.first;
                }
            }
            return label;
        }
    };
    
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VDecisionTreeTypeOperator<_T, VDecisionTreeType::Regressor>
    {
    protected:
        // (1 / n) * ∑(xi)
        //----------------------------------------------------------------------------------------------------
        double Mean(const std::vector<std::pair<std::vector<VAny>, _T>*>& _samples)
        {
            double result = 0;
            unsigned long size = _samples.size();
            for (auto& sample : _samples)
            {
                result += sample->second / size;
            }
            return result;
        }
        
        //----------------------------------------------------------------------------------------------------
        _T Label(const std::vector<std::pair<std::vector<VAny>, _T>*>& _samples)
        {
            return static_cast<_T>(Mean(_samples));
        }
    };

}

#endif
