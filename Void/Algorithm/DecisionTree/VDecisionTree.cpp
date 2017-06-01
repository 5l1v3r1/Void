#include "VDecisionTree.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VDecisionTree
    //----------------------------------------------------------------------------------------------------
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VDecisionTreeTest()
    {
        VDecisionTree<std::string, VDecisionTreeImpurity::Gini> tree;
        std::vector<VDecisionTreeSplit> featureTypes = { VDecisionTreeSplit::BinaryContinuous, VDecisionTreeSplit::Complete, VDecisionTreeSplit::Complete };
        tree.SetFeatureTypes(featureTypes);
        tree.Push({ 1.f, 5, std::string("happy") }, "good");
        tree.Push({ 2.f, 5, std::string("sad") }, "bad");
        tree.Build();
        auto result = tree.Predict({ 3.f, 5, std::string("happy") });
        
        return;
    }
    
}
