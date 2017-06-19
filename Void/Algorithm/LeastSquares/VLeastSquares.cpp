#include "VLeastSquares.h"
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
    // z = min∑(εi^2) => min∑((a + b * xi - yi)^2)
    // ∂z/∂a = 2 * ∑(a + b * xi - yi)
    //       = 2 * (n * a + b * ∑(xi) - ∑(yi))
    //       = 0
    // ∂z/∂b = 2 * ∑(a + b * xi - yi) * xi
    //       = 2 * (a * ∑(xi) + b * ∑(xi ^ 2) - ∑(yi * xi))
    //       = 0
    // a = (∑(yi) * ∑(xi^2) - ∑(xi) * ∑(xi * yi)) / (n * ∑(xi^2) - ∑(xi)^2)
    //   = y - b * x
    // b = (n * ∑(xi * yi) - ∑(xi) * ∑(yi)) / (n * ∑(xi^2) - ∑(xi)^2)
    //
    // return: (a, b)
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
    // z = min∑(εi^2) => min∑(((a0 * xi^0 + a1 * xi^1 + ... + ak * xi^k) - yi)^2)
    // ∂z/∂a0 = 2 * ∑((a0 * xi^0 + a1 * xi^1 + ... + ak * xi^k) - yi)
    //        = 0
    // ∂z/∂ak = 2 * ∑((a0 * xi^0 + a1 * xi^1 + ... + ak * xi^k) - yi) * xi^k
    //        = 0
    //
    // return (a0, a1, a2 ...)
    //----------------------------------------------------------------------------------------------------
    std::vector<double> VLeastSquares::LinearEquationWithOneUnknown(std::vector<std::pair<double, double>> _xy, unsigned _degree)
    {
        
        
        return std::vector<double>();
    }
    
    // y = a + (w0 * x0 + w1 * x1 + ...) + ε
    // z = min∑(εi^2) => min∑((a + (w0 * x0 + w1 * x1 + ...) - yi)^2)
    // ∂z/∂a = 2 * ∑(a + (w0 * x0 + w1 * x1 + ...) - yi)
    //       = 0
    //
    // return: (a, w)
    //----------------------------------------------------------------------------------------------------
    std::pair<double, std::vector<double>> VLeastSquares::LinearEquationWithMultivariable(std::vector<std::pair<std::vector<double>, double>> _xy)
    {
        
        return std::pair<double, std::vector<double>>();
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VLeastSquaresTest()
    {
        VLeastSquares leastSquares;
        VRandom random;
        
        // y = 5 + 4 * x
        std::vector<std::pair<double, double>> simulatedData;
        for (int i = 0; i < 100000; ++i) {
            float e = random.Rand(-1.f, 1.f);
            simulatedData.push_back(std::pair<double, double>(i, 5 + 4 * i + e));
        }
        auto result = leastSquares.LinearEquationWithOneUnknown(simulatedData);
        
        // y = 2 - 2.5 x
        simulatedData.clear();
        for (int i = 0; i < 100000; ++i) {
            float e = random.Rand(-1.f, 1.f);
            simulatedData.push_back(std::pair<double, double>(i, 2 + -2.5 * i + e));
        }
        result = leastSquares.LinearEquationWithOneUnknown(simulatedData);
        
        return;
    }
    
}
