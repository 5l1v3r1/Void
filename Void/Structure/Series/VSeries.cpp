#include "VSeries.h"
#include <cmath>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VSeries
    //----------------------------------------------------------------------------------------------------
    
    // Arithmetic Series
    // a(n) = a(0) + d * n
    // d = a(n) - a(n-1) = difference
    // S(n) = ∑(a(0) + n * d) = (a(0) + a(n)) * n / 2 = a(0) * (n + 1) + (0 + n) * (n + 1) / 2 * d
    //----------------------------------------------------------------------------------------------------
    VSeries VSeries::ArithmeticSeries(double _a0, double _difference)
    {
        std::vector<double> factors;
        factors.push_back(_a0);
        factors.push_back(_difference);
        auto generalTermFormula = [](const std::vector<double>& _factors, const unsigned long& _n)->double
        {
            if (_factors.size() < 2)
            {
                return 0;
            }
            double a0 = _factors[0];
            double difference = _factors[1];
            return a0 + difference * _n;
        };
        auto summationFormula = [](const std::vector<double>& _factors, const unsigned long& _n)->double
        {
            if (_factors.size() < 2)
            {
                return 0;
            }
            double a0 = _factors[0];
            double difference = _factors[1];
            return a0 * (_n + 1) + _n * (_n + 1) / 2 * difference;
        };
        return VSeries(factors, generalTermFormula, summationFormula);
    }
    
    // Geometric Series
    // a(n) = a(0) * r^n
    // r = a(n) / a(n-1) = ratio
    // S(n) = ∑(a(0) * r^n) = (a(0) - a(0) * r^(n + 1)) / (1 - r), r ≠ 1
    //                      = a(0) * (n + 1), r = 1
    //----------------------------------------------------------------------------------------------------
    VSeries VSeries::GeometricSeries(double _a0, double _ratio)
    {
        std::vector<double> factors;
        factors.push_back(_a0);
        factors.push_back(_ratio);
        auto generalTermFormula = [](const std::vector<double>& _factors, const unsigned long& _n)->double
        {
            if (_factors.size() < 2)
            {
                return 0;
            }
            double a0 = _factors[0];
            double ratio = _factors[1];
            return a0 * std::pow(ratio, _n);
        };
        auto summationFormula = [](const std::vector<double>& _factors, const unsigned long& _n)->double
        {
            if (_factors.size() < 2)
            {
                return 0;
            }
            double a0 = _factors[0];
            double ratio = _factors[1];
            if (ratio == 1)
            {
                return ratio * (_n + 1);
            }
            else
            {
                return (a0 - a0 * std::pow(ratio, _n + 1)) / (1 - ratio);
            }
        };
        return VSeries(factors, generalTermFormula, summationFormula);
    }
    
    //----------------------------------------------------------------------------------------------------
    VSeries VSeries::TaylorSeries()
    {
        
        return VSeries();
    }
    
    //----------------------------------------------------------------------------------------------------
    VSeries::VSeries()
        :
        mFactors(),
        mGeneralTermFormula(),
        mSummationFormula()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VSeries::VSeries(const std::vector<double>& _factors, const std::function<double(const std::vector<double>&, const unsigned long&)>& _generalTermFormula, const std::function<double(const std::vector<double>&, const unsigned long&)>& _summationFormula)
        :
        mFactors(_factors),
        mGeneralTermFormula(_generalTermFormula),
        mSummationFormula(_summationFormula)
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    VSeries::VSeries(const VSeries& _series)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VSeries::~VSeries()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    double VSeries::Term(const unsigned long& _n)
    {
        if (mGeneralTermFormula)
        {
            return mGeneralTermFormula(mFactors, _n);
        }
        return 0;
    }
    
    //----------------------------------------------------------------------------------------------------
    double VSeries::Summation(const unsigned long& _n)
    {
        if (mGeneralTermFormula)
        {
            return mSummationFormula(mFactors, _n);
        }
        return 0;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VSeriesTest()
    {
        VSeries arithmetic = VSeries::ArithmeticSeries(5, 2);
        double value0 = arithmetic.Term(0);
        value0 = arithmetic.Term(3);
        value0 = arithmetic.Summation(3);
        
        VSeries geometric = VSeries::GeometricSeries(5, 2);
        value0 = geometric.Term(0);
        value0 = geometric.Term(3);
        value0 = geometric.Summation(3);
        
        return;
    }
    
}
