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
        VBigNumber& operator=(const long long& _number);
        VBigNumber& operator=(const std::string& _number);
        VBigNumber& operator=(const VBigNumber& _number);
        VBigNumber operator+(const VBigNumber& _number) const;
        VBigNumber& operator+=(const VBigNumber& _number);
        VBigNumber operator+(long long _integer) const;
        VBigNumber& operator+=(long long _integer);
        friend VBigNumber operator+(long long _integer, const VBigNumber& _number);
        VBigNumber operator-() const;
        VBigNumber operator-(const VBigNumber& _number) const;
        VBigNumber& operator-=(const VBigNumber& _number);
        VBigNumber operator-(long long _integer) const;
        VBigNumber& operator-=(long long _integer);
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
        bool operator<(const VBigNumber& _number) const;
        
        //----------------------------------------------------------------------------------------------------
        bool IsNegative() const;
        VBigNumber Absolute() const;
        
    protected:
        //----------------------------------------------------------------------------------------------------
        void Fix();
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::string mNumber;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VBigNumberTest();
}

#endif
