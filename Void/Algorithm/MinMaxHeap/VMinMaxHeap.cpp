#include "VMinMaxHeap.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // Test
    //----------------------------------------------------------------------------------------------------
    void VMinMaxHeapTest()
    {
        VMinMaxHeap<int, int> heap;
        heap.Insert(11, 11);
        heap.Insert(10, 10);
        heap.Insert(6, 6);
        heap.Insert(2, 2);
        heap.Insert(5, 5);
        heap.Insert(8, 8);
        heap.Insert(9, 9);
        heap.Insert(1, 1);
        heap.Insert(13, 13);
        heap.Insert(14, 14);
        heap.Insert(4, 4);
        heap.Insert(3, 3);
        heap.Insert(7, 7);
        heap.Insert(12, 12);
        heap.Insert(0, 0);
        
        int value = heap.MinFront();
        heap.PopMinFront();
        value = heap.MinFront();
        heap.PopMinFront();
        value = heap.MinFront();
        heap.PopMinFront();
        value = heap.MinFront();
        heap.PopMinFront();
        value = heap.MinFront();
        heap.PopMinFront();
        value = heap.MinFront();
        heap.PopMinFront();
        
        value = heap.MaxFront();
        heap.PopMaxFront();
        value = heap.MaxFront();
        heap.PopMaxFront();
        value = heap.MaxFront();
        heap.PopMaxFront();
        value = heap.MaxFront();
        heap.PopMaxFront();
        
        return;
    }
}
