#include "VMinHeap.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // Test
    //----------------------------------------------------------------------------------------------------
    void VMinHeapTest()
    {
        VMinHeap<int, char> heap;
        heap.Insert(10, '0');
        heap.Insert(6, '0');
        heap.Insert(10, '0');
        heap.Insert(234, '0');
        heap.Insert(10, '0');
        heap.Insert(6, '0');
        heap.Insert(5, '0');
        heap.Insert(1, '0');
        heap.PopFront();
        
        return;
    }
}
