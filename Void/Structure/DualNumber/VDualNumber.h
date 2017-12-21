#pragma once
#ifndef _V_DUALNUMBER_H_
#define _V_DUALNUMBER_H_

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VDualNumber
    //----------------------------------------------------------------------------------------------------
    // Implemental option: matrix
    // (real dual)
    // (   0 real)
    //----------------------------------------------------------------------------------------------------
    // Operator | Pattern                                                 |
    //----------------------------------------------------------------------------------------------------
    //        + | (x + y)' = x' + y'                                      |
    //----------------------------------------------------------------------------------------------------
    //        - | (x - y)' = x' - y'                                      |
    //----------------------------------------------------------------------------------------------------
    //        * | (x * y)' = x * y' + x' * y                              |
    //----------------------------------------------------------------------------------------------------
    //        / | (x / y)' = x * (y^-1)' + x' * (y^-1)                    |
    //          |          = x * -(y^-2) * y' + x' * (y^-1)               |
    //          |          = (x' * y - x * y') / y^2                      |
    //----------------------------------------------------------------------------------------------------
    //      pow | (x^n)' = (x * x * ... * x)'                             |
    //          |        = x * (x * ... * x)' + x' * (x * ... * x)        |
    //          |        = x * (x^(n-1))' + x' * x^(n-1)                  |
    //          |        = x^2 * (x^(n-2))' + x' * x^(n-1) + x' * x^(n-1) |
    //          |        = ...                                            |
    //          |        = n * x^(n-1) * x'                               |
    //          |-----------------------------------------------------------------------------------------
    //          | (a^y)' = (a * a * ...)'                                 |
    //          |        = (a^(y + Δy) - a^y) / Δy                        |
    //          |        = a^y * (a^Δy - 1) / Δy                          |
    //          |        = a^y * (a^Δy - 1) / loga(a^Δy)                  |
    //          |        = a^y * 1 / loga((a^Δy)^(a^Δy - 1))              |
    //          |        = a^y * ln(a) * y', Δy -> 0                      |
    //          | (option: use ln)                                        |
    //          |-----------------------------------------------------------------------------------------
    //          | (x^y)' = (y * ln(x))' * x^y                             |
    //          |        = (y' * ln(x) + y / x * x') * x^y                |
    //----------------------------------------------------------------------------------------------------
    //      log | loga(x) = 1 / x * ln(a) * x'                            |
    //----------------------------------------------------------------------------------------------------
    //          |                                                         |
    //----------------------------------------------------------------------------------------------------
    struct VDualNumber
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VDualNumber(); // Nilpotent
        VDualNumber(double _real);
        VDualNumber(double _real, double _dual);
        VDualNumber(const VDualNumber& _number);
        ~VDualNumber();
        
        //----------------------------------------------------------------------------------------------------
        VDualNumber& operator=(const VDualNumber& _number);
        VDualNumber operator+(const VDualNumber& _number) const;
        VDualNumber& operator+=(const VDualNumber& _number);
        VDualNumber operator+(double _scalar);
        VDualNumber& operator+=(double _scalar);
        friend VDualNumber operator+(double _scalar, const VDualNumber& _number);
        VDualNumber operator-() const;
        VDualNumber operator-(const VDualNumber& _number) const;
        VDualNumber& operator-=(const VDualNumber& _number);
        VDualNumber operator-(double _scalar);
        VDualNumber& operator-=(double _scalar);
        friend VDualNumber operator-(double _scalar, const VDualNumber& _number);
        VDualNumber operator*(const VDualNumber& _number) const;
        VDualNumber& operator*=(const VDualNumber& _number);
        VDualNumber operator*(double _scalar);
        VDualNumber& operator*=(double _scalar);
        friend VDualNumber operator*(double _scalar, const VDualNumber& _number);
        VDualNumber operator/(const VDualNumber& _number) const;
        VDualNumber& operator/=(const VDualNumber& _number);
        VDualNumber operator/(double _scalar);
        VDualNumber& operator/=(double _scalar);
        friend VDualNumber operator/(double _scalar, const VDualNumber& _number);
        
        //----------------------------------------------------------------------------------------------------
        VDualNumber Sin();
        VDualNumber Cos();
        VDualNumber Pow(double _n);
        VDualNumber Pow(const VDualNumber& _number);
        VDualNumber Exp();
        VDualNumber Ln();
        
    public:
        //----------------------------------------------------------------------------------------------------
        double real;
        double dual;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VDualNumberTest();
}

#endif
