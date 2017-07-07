#include "VLeastSquares.h"
#include "../../Structure/DynamicMatrix/VDynamicMatrix.h"
#include "../../Utility/Random/VRandom.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VLeastSquares
    //----------------------------------------------------------------------------------------------------
    VLeastSquares::VLeastSquares()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VLeastSquares::VLeastSquares(const VLeastSquares& _leastSquares)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VLeastSquares::~VLeastSquares()
    {
    }
    
    // y = a + b * x + ε
    // min(z) = min∑(εi^2) => min∑((a + b * xi - yi)^2)
    // ∂z/∂a = 2 * ∑(a + b * xi - yi)
    //       = 2 * (n * a + b * ∑(xi) - ∑(yi))
    //       = 0
    // ∂z/∂b = 2 * ∑((a + b * xi - yi) * xi)
    //       = 2 * (a * ∑(xi) + b * ∑(xi ^ 2) - ∑(yi * xi))
    //       = 0
    // a = (∑(yi) * ∑(xi^2) - ∑(xi) * ∑(xi * yi)) / (n * ∑(xi^2) - ∑(xi)^2)
    //   = y - b * x
    // b = (n * ∑(xi * yi) - ∑(xi) * ∑(yi)) / (n * ∑(xi^2) - ∑(xi)^2)
    //
    // Return: (a, b)
    // See also: LinearEquationWithOneUnknown(xy, 1)
    //----------------------------------------------------------------------------------------------------
    std::pair<double, double> VLeastSquares::LinearEquationWithOneUnknown(std::vector<std::pair<double, double>> _xy)
    {
        double x = 0;
        double y = 0;
        double xx = 0;
        double xy = 0;
        for (unsigned int i = 0; i < _xy.size(); ++i)
        {
            x += _xy[i].first;
            y += _xy[i].second;
            xx += _xy[i].first * _xy[i].first;
            xy += _xy[i].first * _xy[i].second;
        }
        double a = (y * xx - x * xy) / (_xy.size() * xx - x * x);
        double b = (_xy.size() * xy - x * y) / (_xy.size() * xx - x * x);
        return std::pair<double, double>(a, b);
    }
    
    // y = (a0 * x^0 + a1 * x^1 + ... + ak * x^k) + ε
    // min(z) = min∑(εi^2) => min∑(((a0 * xi^0 + a1 * xi^1 + ... + ak * xi^k) - yi)^2)
    // ∂z/∂a0 = 2 * ∑((a0 * xi^0 + a1 * xi^1 + ... + ak * xi^k) - yi)
    //        = 2 * (n * a0 + a1 * ∑(xi) + ... + ak * ∑(xi^k) - ∑(yi))
    //        = 0
    // ∂z/∂ak = 2 * ∑(((a0 * xi^0 + a1 * xi^1 + ... + ak * xi^k) - yi) * xi^k)
    //        = 2 * (a0 * ∑(xi^k) + a1 * ∑(xi^(k + 1)) + ... + ak * ∑(xi^(k * 2)) - ∑(yi * xi^k))
    //        = 0
    // matrix = [      n       ∑(xi^1) ...      ∑(xi^k)] [a0] = [∑(yi * xi^0)]
    //          [∑(xi^1)       ∑(xi^2) ... ∑(xi^(k + 1)] [a1]   [∑(yi * xi^1)]
    //          [    ...           ... ...          ...] [..]   [         ...]
    //          [∑(xi^k) ∑(xi^(k + 1)) ... ∑(xi^(k * 2)] [ak]   [∑(yi * xi^k)]
    //
    // Return (a0, a1, a2 ...)
    //----------------------------------------------------------------------------------------------------
    std::vector<double> VLeastSquares::LinearEquationWithOneUnknown(std::vector<std::pair<double, double>> _xy, unsigned _order)
    {
        std::vector<double> coefficients(_order * 2 + 1, 0); // x^k
        VDynamicMatrix<double> constantMatrix(_order + 1, 1, 0); // y * x^k
        for (unsigned int i = 0; i < _xy.size(); ++i)
        {
            double xk = 1;
            for (unsigned long k = 0; k < constantMatrix.Rows(); ++k)
            {
                coefficients[k] += xk;
                constantMatrix(k, 0) += _xy[i].second * xk;
                xk *= _xy[i].first;
            }
            for (unsigned long k = constantMatrix.Rows(); k < coefficients.size(); ++k)
            {
                coefficients[k] += xk;
                xk *= _xy[i].first;
            }
        }
        VDynamicMatrix<double> coefficientMatrix(_order + 1, _order + 1, 0);
        for (unsigned long row = 0; row < coefficientMatrix.Rows(); ++row)
        {
            for (unsigned long column = 0; column < coefficientMatrix.Columns(); ++column)
            {
                coefficientMatrix(row, column) = coefficients[row + column];
            }
        }
        VDynamicMatrix<double> unknownMatrix = coefficientMatrix.Inverse() * constantMatrix;
        std::vector<double> result(_order + 1);
        for (unsigned int i = 0; i < result.size(); ++i)
        {
            result[i] = unknownMatrix(i, 0);
        }
        return result;
    }
    
    // y = a + (w0 * x0 + w1 * x1 + ... + wk * xk) + ε
    // min(z) = min∑(εi^2) => min∑((a + (w0 * x0 + w1 * x1 + ... + wk * xk) - yi)^2)
    // ∂z/∂a  = 2 * ∑(a + (w0 * x0 + w1 * x1 + ... + wk * xk) - yi)
    //        = 2 * (n * a + w0 * ∑(x0) + w1 * ∑(x1) + ... + wk * ∑(xl) - ∑(yi))
    //        = 0
    // ∂z/∂wk = 2 * ∑((a + (w0 * x0 + w1 * x1 + ... + wk * xk) - yi) * xk)
    //        = 2 * (a * ∑(xk) + w0 * ∑(x0 * xk) + w1 * ∑(x1 * xk) + ... + wk * ∑(xk * xk) - ∑(yi * xk))
    //        = 0
    // matrix = [    n      ∑(x0)      ∑(x1) ...      ∑(xk)] [ a] = [     ∑(yi)]
    //          [∑(x0) ∑(x0 * x0) ∑(x1 * x0) ... ∑(xk * x0)] [w0]   [∑(yi * x0)]
    //          [  ...        ...        ... ...        ...] [..]   [       ...]
    //          [∑(xk) ∑(x0 * xk) ∑(x1 * xk) ... ∑(xk * xk)] [wk]   [∑(yi * xk)]
    //
    // return: (a, w)
    //----------------------------------------------------------------------------------------------------
    std::pair<double, std::vector<double>> VLeastSquares::LinearEquationWithMultivariable(std::vector<std::pair<std::vector<double>, double>> _xy)
    {
        if (!_xy.size())
        {
            return std::pair<double, std::vector<double>>();
        }
        
        unsigned long variableCount = _xy[0].first.size();
        VDynamicMatrix<double> coefficientMatrix(variableCount + 1, variableCount + 1, 0);
        VDynamicMatrix<double> constantMatrix(variableCount + 1, 1, 0);
        for (unsigned int i = 0; i < _xy.size(); ++i)
        {
            std::vector<double> &x = _xy[i].first;
            double y = _xy[i].second;
            coefficientMatrix(0, 0) += 1;
            for (unsigned long row = 1; row < coefficientMatrix.Rows(); ++row)
            {
                coefficientMatrix(row, 0) += x[row - 1];
            }
            for (unsigned long row = 1; row < coefficientMatrix.Rows(); ++row)
            {
                for (unsigned long column = 1; column <= row; ++column)
                {
                    coefficientMatrix(row, column) += x[row - 1] * x[column - 1];
                }
            }
            constantMatrix(0, 0) += y;
            for (unsigned long row = 1; row < constantMatrix.Rows(); ++row)
            {
                constantMatrix(row, 0) += y * x[row - 1];
            }
        }
        for (unsigned long row = 1; row < coefficientMatrix.Rows(); ++row)
        {
            for (unsigned long column = row + 1; column < coefficientMatrix.Columns(); ++column)
            {
                coefficientMatrix(row, column) = coefficientMatrix(column, row);
            }
        }
        VDynamicMatrix<double> unknownMatrix = coefficientMatrix.Inverse() * constantMatrix;
        std::pair<double, std::vector<double>> result(unknownMatrix(0, 0), std::vector<double>(variableCount));
        for (unsigned int i = 0; i < variableCount; ++i)
        {
            result.second[i] = unknownMatrix(i + 1, 0);
        }
        return result;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VLeastSquaresTest()
    {
        VLeastSquares leastSquares;
        VRandom random;
        
        // y = 5 + 4 * x
        std::vector<std::pair<double, double>> simulatedData;
        for (int i = 0; i < 10000; ++i)
        {
            float e = random.Rand(-1.f, 1.f);
            simulatedData.push_back(std::pair<double, double>(i, 5 + 4 * i + e));
        }
        std::pair<double, double> ab = leastSquares.LinearEquationWithOneUnknown(simulatedData);
        
        // y = 2 - 2.5 * x
        simulatedData.clear();
        for (int i = 0; i < 10000; ++i)
        {
            float e = random.Rand(-1.f, 1.f);
            simulatedData.push_back(std::pair<double, double>(i, 2 + -2.5 * i + e));
        }
        ab = leastSquares.LinearEquationWithOneUnknown(simulatedData);
        std::vector<double> result = leastSquares.LinearEquationWithOneUnknown(simulatedData, 1);
        
        // y = 100 - 3.5 * x + 2 * x^2
        simulatedData.clear();
        for (float i = 0; i < 10; i += 0.02)
        {
            float e = random.Rand(-1.f, 1.f);
            simulatedData.push_back(std::pair<double, double>(i, 100 + -3.5 * i + 2 * i * i + e));
        }
        result = leastSquares.LinearEquationWithOneUnknown(simulatedData, 2);
        
        // y = 100 - 3.5 * x0 + 2 * x1
        std::vector<std::pair<std::vector<double>, double>> multiSimulatedData;
        for (float i = -10; i < 10; i += 0.1)
        {
            for (float j = -10; j < 10; j += 0.1)
            {
                float e = random.Rand(-0.2f, 0.2f);
                multiSimulatedData.push_back(std::pair<std::vector<double>, double>({i, j}, 100 + -3.5 * i + 2 * j + e));
            }
        }
        auto multiResult = leastSquares.LinearEquationWithMultivariable(multiSimulatedData);
        
        // xxx
        multiSimulatedData.clear();
        
        return;
    }
    
}
