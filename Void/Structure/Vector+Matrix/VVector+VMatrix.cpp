#include "VVector+VMatrix.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // Test
    //----------------------------------------------------------------------------------------------------
    void VVectorVMatrixTest()
    {
        float vectorArray[2] = {1, 2};
        VVector<float, 2> vector(vectorArray, 2);
        float matrixArray[8] = {1, 2, 3, 4, 5, 6, 7, 8};
        VMatrix<float, 2, 4> matrix(matrixArray, 8);
        VMatrix<float, 2, 2> matrix1(matrixArray, 4);
        
        auto result = vector * matrix;
        vector *= matrix1;
        
        return;
    }
}
