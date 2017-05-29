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
        std::vector<VDecisionTreeSplit> featureTypes = { VDecisionTreeSplit::Complete, VDecisionTreeSplit::Complete, VDecisionTreeSplit::Complete };
        tree.SetFeatureTypes(featureTypes);
        std::vector<VAny> sample = { 1, 5, std::string("happy") };
        tree.Push(sample, "good");
        sample = { 1, 5, std::string("sad") };
        tree.Push(sample, "bad");
        tree.Build();
        
        return;
    }
    
}
