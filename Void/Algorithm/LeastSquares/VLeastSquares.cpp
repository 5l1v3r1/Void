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
    // min∑(εi)
    // (n) * a + (n * x) * b = n * y
    // (n * x) * a + ∑(xi^2) * b = ∑(xi * yi)
    // b = (∑(xi - yi) - n * x * y) / ∑(xi^2) - n * x^2 = ∑((xi - x) * (yi - y)) / ∑((xi - x)^2)
    //----------------------------------------------------------------------------------------------------
    std::pair<double, double> VLeastSquares::LinearEquationWithOneUnknown(std::vector<std::pair<double, double>> _xy)
    {
        double x = 0;
        double y = 0;
        double xx = 0;
        double xy = 0;
        for (int i = 0; i < _xy.size(); ++i)
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
