#pragma once
#ifndef _V_DUALNUMBER_H_
#define _V_DUALNUMBER_H_

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VDualNumber
    // Implemental option: matrix
    // (real dual)
    // (   0 real)
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
        VDualNumber operator+=(const VDualNumber& _number);
        VDualNumber operator-(const VDualNumber& _number) const;
        VDualNumber operator-=(const VDualNumber& _number);
        VDualNumber operator*(const VDualNumber& _number) const;
        VDualNumber operator*=(const VDualNumber& _number);
        VDualNumber operator/(const VDualNumber& _number) const;
        VDualNumber operator/=(const VDualNumber& _number);
        
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
