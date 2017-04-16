#include "VVector.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // Test
    //----------------------------------------------------------------------------------------------------
    void VVectorTest()
    {
        float array[5] = {1, 2, 3, 4, 5};
        
        VVector<float, 5> test0(array, 5);
        int size = sizeof(test0);
        test0[2] = 5;
        
        VVector<float, 5> test1(test0);
        test1[1] = 5;
        test1 = test1 + 5;
        test1 += test0;
        
        VVector<unsigned char, 2> test2(1, 2, 3, 4);
        size = sizeof(test2);
        
        VVector<float, 1> test3;
        test3.x = 5;
        test3 = test3 * test3;
        
        return;
    }
}
