#include "VDecisionTree.h"
#include <cmath>
#include <map>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VDecisionTree
    //----------------------------------------------------------------------------------------------------
    VDecisionTree::VDecisionTree()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VDecisionTree::VDecisionTree(const VDecisionTree& _tree)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VDecisionTree::~VDecisionTree()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    void VDecisionTree::Build(VDecisionTreeImpurity _operator, unsigned maxDepth, double minGain)
    {

    }
    
    //----------------------------------------------------------------------------------------------------
    double VDecisionTree::CalculateImpurity(const std::vector<double>& _target, VDecisionTreeImpurity _operator)
    {
        switch (_operator) {
            case VDecisionTreeImpurity::GINI:
                return Gini(_target);
            case VDecisionTreeImpurity::ENTROPY:
                return Entropy(_target);
            case VDecisionTreeImpurity::ERROR:
                return Error(_target);
            case VDecisionTreeImpurity::MSE:
                return MeanSquaredError(_target);
            case VDecisionTreeImpurity::MAE:
                return MeanAbsoluteError(_target);
            default:
                break;
        }
		return 0;
    }
    
    // 1 - ∑(pi^2)
    //----------------------------------------------------------------------------------------------------
    double VDecisionTree::Gini(const std::vector<double>& _target)
    {
        double result = 1;
        unsigned long size = _target.size();
        if (size)
        {
            std::map<double, unsigned> counter;
            for (auto& number : _target)
            {
                counter[number] += 1;
            }
            for (auto it = counter.begin(); it != counter.end(); ++it)
            {
                result -= 1.0 * std::pow(it->second, 2) / size;
            }
        }
        return result;
    }
    
    // ∑(-pi * log(pi))
    //----------------------------------------------------------------------------------------------------
    double VDecisionTree::Entropy(const std::vector<double>& _target)
    {
        double result = 0;
        unsigned long size = _target.size();
        if (size)
        {
            std::map<double, unsigned> counter;
            for (auto& number : _target)
            {
                counter[number] += 1;
            }
            for (auto it = counter.begin(); it != counter.end(); ++it)
            {
                double p = 1.0 * it->second / size;
                result -= p * std::log(p);
            }
        }
        return result;
    }
    
    // 1 - max(pi)
    //----------------------------------------------------------------------------------------------------
    double VDecisionTree::Error(const std::vector<double>& _target)
    {
        double result = 1;
        unsigned long size = _target.size();
        if (size)
        {
            std::map<double, unsigned> counter;
            for (auto& number : _target)
            {
                counter[number] += 1;
            }
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
        }
        return result;
    }
    
    // (1 / n) * ∑(xi)
    //----------------------------------------------------------------------------------------------------
    double VDecisionTree::Mean(const std::vector<double>& _target)
    {
        double result = 0;
        unsigned long size = _target.size();
        if (size)
        {
            for (auto& number : _target)
            {
                result += number / size;
            }
        }
        return result;
    }
    
    // (1 / n) * ∑((xi - x)^2)
    //----------------------------------------------------------------------------------------------------
    double VDecisionTree::MeanSquaredError(const std::vector<double>& _target)
    {
        double result = 0;
        unsigned long size = _target.size();
        if (size)
        {
            double mean = Mean(_target);
            for (auto& number : _target)
            {
                result += std::pow(number - mean, 2) / size;
            }
        }
        return result;
    }
    
    // (1 / n) * ∑(|xi - x|)
    //----------------------------------------------------------------------------------------------------
    double VDecisionTree::MeanAbsoluteError(const std::vector<double>& _target)
    {
        double result = 0;
        unsigned long size = _target.size();
        if (size)
        {
            double mean = Mean(_target);
            for (auto& number : _target)
            {
                result += std::abs(number - mean) / size;
            }
        }
        return result;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VDecisionTreeTest()
    {
        
    }
    
}
