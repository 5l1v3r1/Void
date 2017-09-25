#include "VSparseMatrix.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // Test
    //----------------------------------------------------------------------------------------------------
    void VSparseMatrixTest()
    {
        VSparseMatrix<double> matrix0(5, 5);
        matrix0(2, 4) = 1;
        auto size = matrix0.RealSize();
        matrix0(4, 3) = 2;
        size = matrix0.RealSize();

        return;
    }
}
