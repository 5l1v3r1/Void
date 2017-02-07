#include "VMatrix.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // Test
    //----------------------------------------------------------------------------------------------------
    void VMatrixTest()
    {
        float array[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        VMatrix<float, 3, 3> test(array, 9);
        VMatrix<float, 3, 3> test1 = VMatrix<float, 3, 3>::Identity();
        //VMatrix<float, 4, 4> test2 = VMatrixPerspectiveLH();
        
        int size = sizeof(test);
        size += 0;

        
        return;
    }
}
