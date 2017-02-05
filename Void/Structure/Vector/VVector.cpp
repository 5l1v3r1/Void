#include "VVector.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // Test
    //----------------------------------------------------------------------------------------------------
    void VVectorTest()
    {
        float array[5] = {1, 2, 3, 4, 5};
        VVector<float, 5> test(array, 1);
        test[2] = 5;
        VVector<float, 5> test1(test);
        test[1] = 5;
        VVector<unsigned char, 2> test2(1, 2, 3, 4);
        VVector<float, 1> test3;
        test3.x = 5;
        test3 = test3 * test3;
        
        int size = sizeof(test);
        int size1 = sizeof(test2);
        size += size1;
        
        return;
    }
}
