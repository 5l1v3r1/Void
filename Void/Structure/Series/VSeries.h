#pragma once
#ifndef _V_SERIES_H_
#define _V_SERIES_H_

#include <functional>
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VSeries
    //----------------------------------------------------------------------------------------------------
    class VSeries
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static VSeries ArithmeticSeries(double _a0, double _difference);
        static VSeries GeometricSeries(double _a0, double _ratio);
        static VSeries TaylorSeries();
        
    public:
        //----------------------------------------------------------------------------------------------------
        VSeries();
        VSeries(const std::vector<double>& _factors, const std::function<double(const std::vector<double>&, const unsigned long&)>& _generalTermFormula, const std::function<double(const std::vector<double>&, const unsigned long&)>& _summationFormula);
        VSeries(const VSeries& _series);
        ~VSeries();
        
        //----------------------------------------------------------------------------------------------------
        double Term(const unsigned long& _n);
        double Summation(const unsigned long& _n);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::vector<double> mFactors;
        std::function<double(const std::vector<double>&, const unsigned long&)> mGeneralTermFormula;
        std::function<double(const std::vector<double>&, const unsigned long&)> mSummationFormula;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VSeriesTest();
}

#endif
