#pragma once
#ifndef _V_DECISIONTREE_H_
#define _V_DECISIONTREE_H_

#include "../../Memory/SmartPtr/VSmartPtr.h"
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VDecisionTreeCriterion
    // Classifier: Gini, Entropy, Error
    // Regressor: Mean Squared Error, Mean Absolute Error
    //----------------------------------------------------------------------------------------------------
    enum class VDecisionTreeImpurity
    {
        GINI = 0,
        ENTROPY,
        ERROR,
        MSE,
        MAE,
    };
    
    // VDecisionTree
    //----------------------------------------------------------------------------------------------------
    class VDecisionTree
    {
    protected:
        // Node
        //----------------------------------------------------------------------------------------------------
        struct Node
        {
        public:
            //----------------------------------------------------------------------------------------------------
            inline Node() {}
            
            //----------------------------------------------------------------------------------------------------
            inline virtual ~Node() {}
            
        public:
            //----------------------------------------------------------------------------------------------------
            unsigned feature;
            double threshold; // Todo: option
            double informationGain;
            int depth;
            VSmartPtr<Node> left;
            VSmartPtr<Node> right;
        };
        
        // SmartNode
        //----------------------------------------------------------------------------------------------------
        typedef VSmartPtr<Node> SmartNode;
        
    public:
        //----------------------------------------------------------------------------------------------------
        VDecisionTree();
        VDecisionTree(const VDecisionTree& _tree);
        ~VDecisionTree();
        
        //----------------------------------------------------------------------------------------------------
        void Build(VDecisionTreeImpurity _operator, unsigned maxDepth, double minGain);
        void Predict();
        
    protected:
        //----------------------------------------------------------------------------------------------------
        
        double CalculateImpurity(const std::vector<double>& _target, VDecisionTreeImpurity _operator);
        double Gini(const std::vector<double>& _target);
        double Entropy(const std::vector<double>& _target);
        double Error(const std::vector<double>& _target);
        double Mean(const std::vector<double>& _target);
        double MeanSquaredError(const std::vector<double>& _target);
        double MeanAbsoluteError(const std::vector<double>& _target);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        SmartNode mRoot;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VDecisionTreeTest();
}

#endif
