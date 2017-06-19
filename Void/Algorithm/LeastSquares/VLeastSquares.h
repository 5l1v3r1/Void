#pragma once
#ifndef _V_LEASTSQUARES_H_
#define _V_LEASTSQUARES_H_

#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VLeastSquares
    // min∑((yi - y)^2)
    // f(y, variable) is a convex function
    // find ∂f / ∂variable = 0
    //----------------------------------------------------------------------------------------------------
    class VLeastSquares
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VLeastSquares();
        VLeastSquares(const VLeastSquares& _leastSquares);
        ~VLeastSquares();
        
        //----------------------------------------------------------------------------------------------------
        std::pair<double, double> LinearEquationWithOneUnknown(std::vector<std::pair<double, double>> _xy);
        std::vector<double> LinearEquationWithOneUnknown(std::vector<std::pair<double, double>> _xy, unsigned _degree);
        std::pair<double, std::vector<double>> LinearEquationWithMultivariable(std::vector<std::pair<std::vector<double>, double>> _xy);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        
    protected:
        //----------------------------------------------------------------------------------------------------
        
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VLeastSquaresTest();
}

#endif
