#pragma once
#ifndef _V_DECISIONTREE_H_
#define _V_DECISIONTREE_H_

#include "DecisionTreeOperator/DecisionTreeImpurity/VDecisionTreeImpurity.h"
#include "DecisionTreeOperator/VDecisionTreeSplit/VDecisionTreeSplit.h"
#include "../../Structure/Any/VAny.h"
#include "../../Memory/SmartPtr/VSmartPtr.h"
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <cmath>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VDecisionTree
    // ID3 (Iterative Dichotomiser 3, greedy manner, require categorical feature, Entropy)
    // C4.5 (support numerical variable)
    // CART (Classification and Regression Tree, support regressor)
    //----------------------------------------------------------------------------------------------------
    template<typename _T, VDecisionTreeImpurity _I>
    class VDecisionTree : public VDecisionTreeImpurityOperator<_T, _I>
    {
    protected:
        // Node
        //----------------------------------------------------------------------------------------------------
        struct Node
        {
        public:
            //----------------------------------------------------------------------------------------------------
            inline Node() {}
            
        public:
            //----------------------------------------------------------------------------------------------------
            // int depth;
            // double gain;
            _T label;
            // unsigned feature;
            std::vector<VSmartPtr<Node>> children;
            std::function<unsigned(const VAny&)> routes;
        };
        
        // SmartNode
        //----------------------------------------------------------------------------------------------------
        typedef VSmartPtr<Node> SmartNode;
        
    public:
        //----------------------------------------------------------------------------------------------------
        inline VDecisionTree() {}
        inline virtual ~VDecisionTree() {}
        
        //----------------------------------------------------------------------------------------------------
        inline void SetFeatureTypes(const std::vector<VDecisionTreeSplit>& _featureTypes)
        {
            mFeatureTypes = _featureTypes;
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void Push(std::vector<VAny> _features, _T _target)
        {
            mData.push_back(std::pair<std::vector<VAny>, _T>(_features, _target));
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void Build()
        {
            mRoot = VSmartPtr<Node>(new Node());
            std::vector<std::pair<std::vector<VAny>, _T>*> samples;
            samples.reserve(mData.size());
            for (auto& sample : mData)
            {
                samples.push_back(&sample);
            }
            Build(mRoot, samples);
        }
        
    protected:
        // Recursion
        //----------------------------------------------------------------------------------------------------
        inline void Build(VSmartPtr<Node> _node, std::vector<std::pair<std::vector<VAny>, _T>*>& _samples)
        {
            if (!_samples.size())
            {
                return;
            }
            
            // Label
            _node->label = this->Label(_samples);
            
            // Split
            double impurity = this->CalculateImpurity(_samples);
            double bestInformationGain = 0; // Todo: option
            VDecisionTreeSplitResult<_T> bestFeature;
            VDecisionTreeSplitHelper<_T> splitHelper;
            for (unsigned i = 0; i < mFeatureTypes.size(); ++i)
            {
                VDecisionTreeSplitParameter<_T> parameter(_samples, i);
                if (splitHelper.Process(parameter, mFeatureTypes[i]))
                {
                    VDecisionTreeSplitResult<_T> result;
                    while (splitHelper.Next(result))
                    {
                        double informationGain = impurity;
                        for (auto& branch : result.branches)
                        {
                            informationGain -= 1.0 * branch.size() / _samples.size() * this->CalculateImpurity(branch);
                        }
                        if (bestInformationGain < informationGain)
                        {
                            bestInformationGain = informationGain;
                            bestFeature.Swap(result);
                        }
                    }
                }
            }
            if (bestInformationGain)
            {
                for (auto& branch : bestFeature.branches)
                {
                    VSmartPtr<Node> node = VSmartPtr<Node>(new Node());
                    _node->children.push_back(node);
                    Build(node, branch);
                }
                _node->routes = bestFeature.routes;
            }
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        SmartNode mRoot;
        std::vector<VDecisionTreeSplit> mFeatureTypes;
        std::vector<std::pair<std::vector<VAny>, _T>> mData;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VDecisionTreeTest();
}

#endif
