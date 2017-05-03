#include "VDynamicMatrix.h"
#include "../../Utility/Logger/VLogger.h"

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
        matrix3(1, 1) = 100;
        // matrix3(3, 3); // Throw
        
        double values0[] = {1, 2.2, 333, 4, -5555, 6, 77.77, 88, 9999};
        VDynamicMatrix<double> matrix4(3, 3, values0, 9); // 3 * 3
        double value = matrix4.Determinant();
        VLogger::Info("Matrix \n%s", matrix4.String().c_str());
        value = matrix3.DotProduct(matrix4);
        auto matrix5 = matrix4.Concatenate(matrix3); // 3 * 6
        matrix5 = matrix4;
        VLogger::Info("Matrix \n%s", matrix5.String().c_str());
        matrix5.RowSwitch(1, 2);
        VLogger::Info("Matrix \n%s", matrix5.String().c_str());
        matrix5.RowMultiply(1, 0.5);
        VLogger::Info("Matrix \n%s", matrix5.String().c_str());
        matrix5.RowAdd(0, 1, 2);
        VLogger::Info("Matrix \n%s", matrix5.String().c_str());
        matrix5.LUDecomposition(matrix0, matrix1);
        VLogger::Info("Matrix \n%s", matrix0.String().c_str());
        VLogger::Info("Matrix \n%s", matrix1.String().c_str());
        matrix5 = matrix0 * matrix1;
        VLogger::Info("Matrix \n%s", matrix5.String().c_str());
        value = matrix5.Determinant();
        value = matrix0.Determinant() * matrix1.Determinant();
        matrix5 += matrix5;
        VLogger::Info("Matrix \n%s", matrix5.String().c_str());
        matrix1.RowAdd(2, 0, 1);
        VLogger::Info("Matrix \n%s", matrix1.String().c_str());
        double values1[] = {1, 2, 3, 6, 3, 1, 4, 4, 4};
        VDynamicMatrix<double> matrix6(3, 3, values1, 9);
        VLogger::Info("Matrix \n%s", matrix6.String().c_str());
        matrix1 = matrix6.ReducedRowEchelonForm();
        VLogger::Info("Matrix \n%s", matrix1.String().c_str());
        matrix1 = matrix6.Inverse();
        VLogger::Info("Matrix \n%s", matrix1.String().c_str());
        matrix1 = matrix6 * matrix1;
        VLogger::Info("Matrix \n%s", matrix1.String().c_str());
        matrix1 = matrix6.Adjugate();
        VLogger::Info("Matrix \n%s", matrix1.String().c_str());
        matrix1 = matrix1 / matrix6.Determinant();
        VLogger::Info("Matrix \n%s", matrix1.String().c_str());
        matrix1 = matrix6 * matrix1;
        VLogger::Info("Matrix \n%s", matrix1.String().c_str());
        double values2[] = {0, 2};
        matrix1 = VDynamicMatrix<double>(1, 2, values2, 2);
        double values3[] = {2, 0};
        matrix2 = VDynamicMatrix<double>(1, 2, values3, 2);
        value = matrix1.Radian(matrix2);
        
        return;
    }
}
