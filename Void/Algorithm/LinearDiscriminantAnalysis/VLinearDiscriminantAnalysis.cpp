#include "VLinearDiscriminantAnalysis.h"
#include "../../Structure/DynamicMatrix/VDynamicMatrix.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VLinearDiscriminantAnalysis
    //----------------------------------------------------------------------------------------------------
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VLinearDiscriminantAnalysisTest()
    {
        VLinearDiscriminantAnalysis<float, bool> analysis;
        analysis.Push({2, 1}, true);
        analysis.Push({3, 2}, true);
        analysis.Push({4, 3}, true);
        analysis.Push({2, 6}, true);
        analysis.Push({1, 4}, true);
        analysis.Push({10, 10}, false);
        analysis.Push({6, 5}, false);
        analysis.Push({12, 9}, false);
        analysis.Push({4, 7}, false);
        analysis.Push({10, 2}, false);
        analysis.Build();
        
        return;
    }
    
}
