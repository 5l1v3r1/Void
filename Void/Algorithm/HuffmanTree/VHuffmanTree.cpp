#include "VHuffmanTree.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // Test
    //----------------------------------------------------------------------------------------------------
    void VHuffmanTreeTest()
    {
        VHuffmanTree<int> tree;
        tree.Insert(10);
        tree.Insert(6);
        tree.Insert(10);
        tree.Insert(234);
        tree.Insert(10);
        tree.Insert(6);
        tree.Insert(6);
        tree.Insert(7);
        tree.Generate();
        
        return;
    }
}
