#include "VBigNumber.h"
#include "../../Utility/String/VString.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VMaze
    //----------------------------------------------------------------------------------------------------
    VBigNumber::VBigNumber()
        :
        mNumber("0")
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber::VBigNumber(const long long& _number)
        :
        mNumber(std::to_string(_number))
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber::VBigNumber(const std::string& _number)
        :
        mNumber(_number)
    {
        Fix();
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber::VBigNumber(const VBigNumber& _number)
        :
        mNumber(_number.mNumber)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber::~VBigNumber()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber& VBigNumber::operator=(const long long& _number)
    {
        this->mNumber = std::to_string(_number);
        return *this;
    }
    
    VBigNumber& VBigNumber::operator=(const std::string& _number)
    {
        this->mNumber = _number;
        Fix();
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber& VBigNumber::operator=(const VBigNumber& _number)
    {
        this->mNumber = _number.mNumber;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber VBigNumber::operator+(const VBigNumber& _number) const
    {
        VBigNumber big = *this < _number ? _number : *this;
        VBigNumber small = *this < _number ? *this : _number;
        if (big.IsNegative() && small.IsNegative())
        {
            return -((-big) + (-small));
        }
        else if (big.IsNegative())
        {
            return -((-big) - small);
        }
        else if (small.IsNegative())
        {
            return -((-small) - big);
        }
        
        std::string number;
        
        
        return VBigNumber(number);
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber& VBigNumber::operator+=(const VBigNumber& _number)
    {
        *this = *this + _number;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber VBigNumber::operator+(long long _integer) const
    {
        return *this + VBigNumber(_integer);
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber& VBigNumber::operator+=(long long _integer)
    {
        *this = *this + _integer;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber operator+(long long _integer, const VBigNumber& _number)
    {
        return VBigNumber(_integer) + _number;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber VBigNumber::operator-() const
    {
        std::string number = this->mNumber;
        if (number[0] == '-')
        {
            number.erase(0, 1);
        }
        // else if (number[0] == '+')
        // {
        //     number[0] = '-';
        // }
        else
        {
            number.insert(number.begin(), '-');
        }
        return VBigNumber(number);
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber VBigNumber::operator-(const VBigNumber& _number) const
    {
        // Todo
        return VBigNumber();
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber& VBigNumber::operator-=(const VBigNumber& _number)
    {
        *this = *this - _number;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber VBigNumber::operator-(long long _integer) const
    {
        return *this - VBigNumber(_integer);
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber& VBigNumber::operator-=(long long _integer)
    {
        *this = *this - _integer;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber operator-(long long _integer, const VBigNumber& _number)
    {
        return VBigNumber(_integer) - _number;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber VBigNumber::operator*(const VBigNumber& _number) const
    {
        // Todo
        return VBigNumber();
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber& VBigNumber::operator*=(const VBigNumber& _number)
    {
        *this = *this * _number;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber VBigNumber::operator*(long long _integer) const
    {
        return *this * VBigNumber(_integer);
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber& VBigNumber::operator*=(long long _integer)
    {
        *this = *this * _integer;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber operator*(long long _integer, const VBigNumber& _number)
    {
        return VBigNumber(_integer) * _number;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber VBigNumber::operator/(const VBigNumber& _number) const
    {
        // Todo
        return VBigNumber();
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber& VBigNumber::operator/=(const VBigNumber& _number)
    {
        *this = *this / _number;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber VBigNumber::operator/(long long _integer) const
    {
        return *this / VBigNumber(_integer);
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber& VBigNumber::operator/=(long long _integer)
    {
        *this = *this / _integer;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber operator/(long long _integer, const VBigNumber& _number)
    {
        return VBigNumber(_integer) / _number;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VBigNumber::operator==(const VBigNumber& _number) const
    {
        return this->mNumber == _number.mNumber;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VBigNumber::operator>(const VBigNumber& _number) const
    {
        // Sign
        if (this->IsNegative() && _number.IsNegative())
        {
            return (-*this) < (-_number);
        }
        else if (this->IsNegative())
        {
            return false;
        }
        else if (_number.IsNegative())
        {
            return true;
        }
        
        // Size
        if (this->mNumber.size() == _number.mNumber.size())
        {
            return this->mNumber > _number.mNumber;
        }
        else
        {
            return _number.mNumber.size() < this->mNumber.size();
        }
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VBigNumber::operator<(const VBigNumber& _number) const
    {
        return !(*this == _number) && !(*this > _number);
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VBigNumber::IsNegative() const
    {
        if (mNumber[0] == '-')
        {
            return true;
        }
        return false;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber VBigNumber::Absolute() const
    {
        std::string number = mNumber;
        if (number[0] == '-')
        {
            number.erase(0, 1);
        }
        return VBigNumber(number);
    }
    
    //----------------------------------------------------------------------------------------------------
    void VBigNumber::Fix()
    {
        auto result = Match(mNumber, std::regex("[-]?\\d+"));
        if (result.size())
        {
            mNumber = result[0];
            mNumber = Replace(mNumber, std::regex("^[-]?(0+)([1-9(0$)])"), "$2");
        }
        else
        {
            mNumber = "0";
        }
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VBigNumberTest()
    {
        VBigNumber number0("-00001");
        VBigNumber number1("-00000");
        VBigNumber number2("000000");
        VBigNumber number3("012345");
        VBigNumber number4("+12300");
        VBigNumber number5("+10305");
        
        return;
    }
    
}
