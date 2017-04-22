#pragma once
#ifndef _V_BIGNUMBER_H_
#define _V_BIGNUMBER_H_

#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VBigNumber
    //----------------------------------------------------------------------------------------------------
    class VBigNumber
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VBigNumber();
        VBigNumber(const long long& _number);
        VBigNumber(const std::string& _number);
        VBigNumber(const VBigNumber& _number);
        ~VBigNumber();
        
        //----------------------------------------------------------------------------------------------------
        VBigNumber& operator=(const long long& _integer);
        VBigNumber& operator=(const std::string& _number);
        VBigNumber& operator=(const VBigNumber& _number);
        VBigNumber operator+(const VBigNumber& _number) const;
        VBigNumber& operator+=(const VBigNumber& _number);
        VBigNumber operator+(long long _integer) const;
        VBigNumber& operator+=(long long _integer);
        VBigNumber& operator++();
        VBigNumber operator++(int);
        friend VBigNumber operator+(long long _integer, const VBigNumber& _number);
        VBigNumber operator-() const;
        VBigNumber operator-(const VBigNumber& _number) const;
        VBigNumber& operator-=(const VBigNumber& _number);
        VBigNumber operator-(long long _integer) const;
        VBigNumber& operator-=(long long _integer);
        VBigNumber& operator--();
        VBigNumber operator--(int);
        friend VBigNumber operator-(long long _integer, const VBigNumber& _number);
        VBigNumber operator*(const VBigNumber& _number) const;
        VBigNumber& operator*=(const VBigNumber& _number);
        VBigNumber operator*(long long _integer) const;
        VBigNumber& operator*=(long long _integer);
        friend VBigNumber operator*(long long _integer, const VBigNumber& _number);
        VBigNumber operator/(const VBigNumber& _number) const;
        VBigNumber& operator/=(const VBigNumber& _number);
        VBigNumber operator/(long long _integer) const;
        VBigNumber& operator/=(long long _integer);
        friend VBigNumber operator/(long long _integer, const VBigNumber& _number);
        
        //----------------------------------------------------------------------------------------------------
        bool operator==(const VBigNumber& _number) const;
        bool operator>(const VBigNumber& _number) const;
        bool operator>=(const VBigNumber& _number) const;
        bool operator<(const VBigNumber& _number) const;
        bool operator<=(const VBigNumber& _number) const;
        
        //----------------------------------------------------------------------------------------------------
        bool IsNegative() const;
        VBigNumber Absolute() const;
        VBigNumber Shift(const long long int& _n) const;
        
    protected:
        //----------------------------------------------------------------------------------------------------
        VBigNumber& Fix();
        VBigNumber KaratsubaMultiply(const VBigNumber& _first, const VBigNumber& _second);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::string mNumber;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VBigNumberTest();
}

#endif
