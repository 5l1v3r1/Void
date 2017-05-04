#pragma once
#ifndef _V_COMPLEXNUMBER_H_
#define _V_COMPLEXNUMBER_H_

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VComplexNumber
    // i^2 = -1
    //----------------------------------------------------------------------------------------------------
    struct VComplexNumber
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VComplexNumber();
        VComplexNumber(double _real);
        VComplexNumber(double _real, double _imaginary);
        VComplexNumber(const VComplexNumber& _number);
        ~VComplexNumber();
        
        //----------------------------------------------------------------------------------------------------
        VComplexNumber& operator=(const VComplexNumber& _number);
        VComplexNumber operator+(const VComplexNumber& _number) const;
        VComplexNumber& operator+=(const VComplexNumber& _number);
        VComplexNumber operator+(double _scalar);
        VComplexNumber& operator+=(double _scalar);
        friend VComplexNumber operator+(double _scalar, const VComplexNumber& _number);
        VComplexNumber operator-(const VComplexNumber& _number) const;
        VComplexNumber& operator-=(const VComplexNumber& _number);
        VComplexNumber operator-(double _scalar);
        VComplexNumber& operator-=(double _scalar);
        friend VComplexNumber operator-(double _scalar, const VComplexNumber& _number);
        VComplexNumber operator*(const VComplexNumber& _number) const;
        VComplexNumber& operator*=(const VComplexNumber& _number);
        VComplexNumber operator*(double _scalar);
        VComplexNumber& operator*=(double _scalar);
        friend VComplexNumber operator*(double _scalar, const VComplexNumber& _number);
        VComplexNumber operator/(const VComplexNumber& _number) const;
        VComplexNumber& operator/=(const VComplexNumber& _number);
        VComplexNumber operator/(double _scalar);
        VComplexNumber& operator/=(double _scalar);
        friend VComplexNumber operator/(double _scalar, const VComplexNumber& _number);
        
        //----------------------------------------------------------------------------------------------------
        bool operator==(const VComplexNumber& _number) const;
        
        //----------------------------------------------------------------------------------------------------
        VComplexNumber Conjugate() const;
        double Absolute() const;
        VComplexNumber SquareRoot() const;
        
    public:
        //----------------------------------------------------------------------------------------------------
        double real;
        double imaginary;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VComplexNumberTest();
}

#endif
