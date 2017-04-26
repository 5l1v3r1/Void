#include "VDynamicMatrix.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // Test
    //----------------------------------------------------------------------------------------------------
    void VDynamicMatrixTest()
    {
        VDynamicMatrix<double> matrix0(5, 5, 2); // 5 * 5
        auto matrix1 = matrix0.SubMatrix(2, 2); // 4 * 4
        auto matrix2 = matrix1.SubMatrix(1, 1); // 3 * 3
        auto matrix3 = matrix2.Copy(); // 3 * 3
        // matrix3(3, 3); // Throw
        
        double values[] = {1, 2, 3, 4, 4, 4, 5, 5, 6};
        VDynamicMatrix<double> matrix4(3, 3, values, 9); // 3 * 3
        double value = matrix4.Determinant();
        value = matrix3.DotProduct(matrix4);
        
        return;
    }
}
