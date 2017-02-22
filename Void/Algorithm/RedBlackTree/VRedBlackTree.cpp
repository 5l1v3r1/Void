#include "VRedBlackTree.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // Test
    //----------------------------------------------------------------------------------------------------
    void VRedBlackTreeTest()
    {
        VRedBlackTree<float, int> tree;
        tree.Insert(5.f, 5);
        tree.Insert(1.f, 6);
        tree.Insert(2.f, 7);
        
        int *target = tree.Find(1.f);
        target = nullptr;
        
        return;
    }
}
