#pragma once
#ifndef _V_DECISIONTREEIMPURITY_H_
#define _V_DECISIONTREEIMPURITY_H_

#include "../../../../Structure/Any/VAny.h"
#include "../DecisionTreeType/VDecisionTreeType.h"
#include <vector>
#include <map>
#include <cmath>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VDecisionTreeImpurity
    // Classifier: Gini, Entropy, Error
    // Regressor: Mean Squared Error, Mean Absolute Error
    //----------------------------------------------------------------------------------------------------
    enum class VDecisionTreeImpurity
    {
        None = 0,
        Gini,
        Entropy,
        Error,
        MSE,
        MAE,
    };
    
    // VDecisionTreeImpurityOperator
    //----------------------------------------------------------------------------------------------------
    template<typename _T, VDecisionTreeImpurity _I>
    class VDecisionTreeImpurityOperator
    {
    };
    
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VDecisionTreeImpurityOperator<_T, VDecisionTreeImpurity::Gini> : public VDecisionTreeTypeOperator<_T, VDecisionTreeType::Classifier>
    {
    protected:
        // 1 - ∑(pi^2) = 1 - ∑((ni / n)^2) = 1 - ∑(ni^2) / n^2
        //----------------------------------------------------------------------------------------------------
        double CalculateImpurity(const std::vector<std::pair<std::vector<VAny>, _T>*>& _samples)
        {
            double result = 1;
            unsigned long size = _samples.size();
            std::map<_T, unsigned> counter = this->Count(_samples);
            for (auto it = counter.begin(); it != counter.end(); ++it)
            {
                result -= std::pow(1.0 * it->second / size, 2);
            }
            return result;
        }
    };
    
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VDecisionTreeImpurityOperator<_T, VDecisionTreeImpurity::Entropy> : public VDecisionTreeTypeOperator<_T, VDecisionTreeType::Classifier>
    {
    protected:
        // ∑(-pi * log(pi)) = -∑((ni / n) * log((ni / n)))
        //----------------------------------------------------------------------------------------------------
        double CalculateImpurity(const std::vector<std::pair<std::vector<VAny>, _T>*>& _samples)
        {
            double result = 0;
            unsigned long size = _samples.size();
            std::map<_T, unsigned> counter = this->Count(_samples);
            for (auto it = counter.begin(); it != counter.end(); ++it)
            {
                double p = 1.0 * it->second / size;
                result -= p * std::log(p);
            }
            return result;
        }
    };
    
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VDecisionTreeImpurityOperator<_T, VDecisionTreeImpurity::Error> : public VDecisionTreeTypeOperator<_T, VDecisionTreeType::Classifier>
    {
    protected:
        // 1 - max(pi)
        //----------------------------------------------------------------------------------------------------
        double CalculateImpurity(const std::vector<std::pair<std::vector<VAny>, _T>*>& _samples)
        {
            double result = 1;
            unsigned long size = _samples.size();
            std::map<_T, unsigned> counter = this->Count(_samples);
            double maxFit = 0;
            for (auto it = counter.begin(); it != counter.end(); ++it)
            {
                double p = 1.0 * it->second / size;
                if (maxFit < p)
                {
                    maxFit = p;
                }
            }
            result -= maxFit;
            return result;
        }
    };
    
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VDecisionTreeImpurityOperator<_T, VDecisionTreeImpurity::MSE> : public VDecisionTreeTypeOperator<_T, VDecisionTreeType::Regressor>
    {
    protected:
        // (1 / n) * ∑((xi - x)^2)
        //----------------------------------------------------------------------------------------------------
        double CalculateImpurity(const std::vector<std::pair<std::vector<VAny>, _T>*>& _samples)
        {
            double result = 0;
            unsigned long size = _samples.size();
            double mean = this->Mean(_samples);
            for (auto& sample : _samples)
            {
                result += std::pow(sample->second - mean, 2) / size;
            }
            return result;
        }
    };
    
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VDecisionTreeImpurityOperator<_T, VDecisionTreeImpurity::MAE> : public VDecisionTreeTypeOperator<_T, VDecisionTreeType::Regressor>
    {
    protected:
        // (1 / n) * ∑(|xi - x|)
        //----------------------------------------------------------------------------------------------------
        double CalculateImpurity(const std::vector<std::pair<std::vector<VAny>, _T>*>& _samples)
        {
            double result = 0;
            unsigned long size = _samples.size();
            double mean = this->Mean(_samples);
            for (auto& sample : _samples)
            {
                result += std::pow(sample->second - mean, 2) / size;
            }
            return result;
        }
    };

}

#endif
