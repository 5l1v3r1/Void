#include "VBigNumber.h"
#include "../../Utility/String/VString.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VBigNumber
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
    VBigNumber& VBigNumber::operator=(const long long& _integer)
    {
        this->mNumber = std::to_string(_integer);
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
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
        
        // Remove sign
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
        
        // Balance
        unsigned long distance = big.mNumber.size() - small.mNumber.size();
        small.mNumber.insert(0, std::string(distance, '0'));
        
        // Calculate
        int carry = 0;
        std::string number;
        unsigned long index = big.mNumber.size();
        while (index != 0)
        {
            index -= 1;
            int sum = (big.mNumber[index] - '0') + (small.mNumber[index] - '0') + carry;
            carry = 0;
            if (sum <= 9 || index == 0)
            {
                number.insert(0, std::to_string(sum));
            }
            else
            {
                number.insert(0, std::to_string(sum % 10));
                carry = 1;
            }
        }
        
        return VBigNumber(number);
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber& VBigNumber::operator+=(const VBigNumber& _number)
    {
        *this = *this + _number;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber VBigNumber::operator+(const long long& _integer) const
    {
        return *this + VBigNumber(_integer);
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber& VBigNumber::operator+=(const long long& _integer)
    {
        *this = *this + _integer;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber& VBigNumber::operator++()
    {
        *this += 1;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber VBigNumber::operator++(int)
    {
        VBigNumber result(*this);
        ++(*this);
        return result;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber operator+(const long long& _integer, const VBigNumber& _number)
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
        else
        {
            number.insert(number.begin(), '-');
        }
        return VBigNumber(number);
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber VBigNumber::operator-(const VBigNumber& _number) const
    {
        VBigNumber first = *this;
        VBigNumber second = _number;
        
        // Remove sign
        if (first.IsNegative() && second.IsNegative())
        {
            return -((-first) - (-second));
        }
        else if (first.IsNegative())
        {
            return -((-first) + second);
        }
        else if (second.IsNegative())
        {
            return first + (-second);
        }
        
        // Negative result
        if (first < second)
        {
            return -(second - first);
        }
        
        // Balance
        unsigned long distance = first.mNumber.size() - second.mNumber.size();
        second.mNumber.insert(0, std::string(distance, '0'));
        
        // Calculate
        int borrow = 0;
        std::string number;
        unsigned long index = first.mNumber.size();
        while (index != 0)
        {
            index -= 1;
            if (first.mNumber[index] - borrow < second.mNumber[index])
            {
                number.insert(0, std::to_string(first.mNumber[index] + 10 - second.mNumber[index] - borrow));
                borrow = 1;
            }
            else
            {
                number.insert(0, std::to_string(first.mNumber[index] - second.mNumber[index] - borrow));
                borrow = 0;
            }
        }
        
        return VBigNumber(number).Fix();
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber& VBigNumber::operator-=(const VBigNumber& _number)
    {
        *this = *this - _number;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber VBigNumber::operator-(const long long& _integer) const
    {
        return *this - VBigNumber(_integer);
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber& VBigNumber::operator-=(const long long& _integer)
    {
        *this = *this - _integer;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber& VBigNumber::operator--()
    {
        *this -= 1;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber VBigNumber::operator--(int)
    {
        VBigNumber result(*this);
        --(*this);
        return result;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber operator-(const long long& _integer, const VBigNumber& _number)
    {
        return VBigNumber(_integer) - _number;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber VBigNumber::operator*(const VBigNumber& _number) const
    {
        VBigNumber big = *this < _number ? _number : *this;
        VBigNumber small = *this < _number ? *this : _number;
        
        // Remove sign
        if (big.IsNegative() && small.IsNegative())
        {
            return (-big) * (-small);
        }
        else if (big.IsNegative())
        {
            return -((-big) * small);
        }
        else if (small.IsNegative())
        {
            return -(big * (-small));
        }
        
        // Zero
        if (big == 0 || small == 0)
        {
            return VBigNumber(0);
        }
        
        // Reverse
        std::reverse(big.mNumber.begin(), big.mNumber.end());
        std::reverse(small.mNumber.begin(), small.mNumber.end());
        
        // Calculate
        unsigned carry = 0;
        std::string number;
        for (unsigned long smallIndex = 0; smallIndex < small.mNumber.size(); ++smallIndex)
        {
            for (unsigned long bigIndex = 0; bigIndex < big.mNumber.size(); ++bigIndex)
            {
                if (number.size() <= smallIndex + bigIndex)
                {
                    unsigned product = (big.mNumber[bigIndex] - '0') * (small.mNumber[smallIndex] - '0') + carry;
                    carry = product / 10;
                    number.push_back(product % 10 + '0');
                }
                else
                {
                    unsigned product = (big.mNumber[bigIndex] - '0') * (small.mNumber[smallIndex] - '0') + carry + (number[smallIndex + bigIndex] - '0');
                    carry = product / 10;
                    number[smallIndex + bigIndex] = product % 10 + '0';
                }
            }
            if (carry)
            {
                if (number.size() <= smallIndex + big.mNumber.size())
                {
                    number.push_back(carry + '0');
                }
                else
                {
                    number[smallIndex + big.mNumber.size()] = carry + '0';
                }
                carry = 0;
            }
        }
        std::reverse(number.begin(), number.end());
        
        return VBigNumber(number);
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber& VBigNumber::operator*=(const VBigNumber& _number)
    {
        *this = *this * _number;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber VBigNumber::operator*(const long long& _integer) const
    {
        return *this * VBigNumber(_integer);
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber& VBigNumber::operator*=(const long long& _integer)
    {
        *this = *this * _integer;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber operator*(const long long& _integer, const VBigNumber& _number)
    {
        return VBigNumber(_integer) * _number;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber VBigNumber::operator/(const VBigNumber& _number) const
    {
        VBigNumber first = *this;
        VBigNumber second = _number;
        
        // Invalid
        if (second == 0)
        {
            return VBigNumber(0);
        }
        
        // Remove sign
        if (first.IsNegative() && second.IsNegative())
        {
            return (-first) / (-second);
        }
        else if (first.IsNegative())
        {
            return -((-first) / second);
        }
        else if (second.IsNegative())
        {
            return -(first / (-second));
        }
        
        // Calculate (Todo: optimize)
        VBigNumber number = 0;
        while (second <= first)
        {
            unsigned long distance = first.mNumber.size() - second.mNumber.size();
            if (distance)
            {
                if (second.Shift(distance) <= first)
                {
                    first -= second.Shift(distance);
					number += std::string("1") + std::string(distance, '0');
                }
                else
                {
                    first -= second.Shift(distance - 1);
                    number += std::string("1") + std::string(distance - 1, '0');
                }
            }
            else
            {
                first -= second;
                ++number;
            }
        }
        
        return VBigNumber(number);
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber& VBigNumber::operator/=(const VBigNumber& _number)
    {
        *this = *this / _number;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber VBigNumber::operator/(const long long& _integer) const
    {
        return *this / VBigNumber(_integer);
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber& VBigNumber::operator/=(const long long& _integer)
    {
        *this = *this / _integer;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber operator/(const long long& _integer, const VBigNumber& _number)
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
    bool VBigNumber::operator>=(const VBigNumber& _number) const
    {
        return *this > _number || *this == _number;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VBigNumber::operator<(const VBigNumber& _number) const
    {
        return !(*this == _number || *this > _number);
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VBigNumber::operator<=(const VBigNumber& _number) const
    {
        return !(*this > _number);
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
    VBigNumber VBigNumber::Shift(const long long int& _n) const
    {
        std::string number = mNumber;
        if (_n < 0)
        {
            if (number.size() < -_n)
            {
                number = "0";
            }
            else
            {
                number.erase(number.size() + _n, -_n);
            }
        }
        else if (0 < _n)
        {
            number += std::string(_n, '0');
        }
        
        return VBigNumber(number).Fix();
    }
    
    //----------------------------------------------------------------------------------------------------
    VBigNumber& VBigNumber::Fix()
    {
        auto result = Match(mNumber, std::regex("[-]?\\d+"));
        if (result.size())
        {
            mNumber = result[0];
            mNumber = Replace(mNumber, std::regex("^([-]?)(0+)([1-9(0$)])"), "$1$3");
            if (mNumber == "-0")
            {
                mNumber = "0";
            }
        }
        else
        {
            mNumber = "0";
        }
        return *this;
    }
    
    // Karatsuba
    // O(3n^log3)
    //----------------------------------------------------------------------------------------------------
    VBigNumber VBigNumber::KaratsubaMultiply(const VBigNumber& _first, const VBigNumber& _second)
    {
        // Todo
        return VBigNumber();
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VBigNumberTest()
    {
        VBigNumber number0("-00001");
        VBigNumber number1("-00000");
        VBigNumber number2("000000");
        VBigNumber number3("012345");
        VBigNumber number4("512300");
        VBigNumber number5("+90305");
        VBigNumber number6("-90305");
        VBigNumber number7("-01205");
        VBigNumber number8("-0");
        VBigNumber number9("+0");
        VBigNumber number10("-");
        VBigNumber number11("-123456789");
        number0 = number4 + number5; // 602605
        number0 -= 123; // 602482
        number0 = number4 - number5; // 421995
        number0 = number7 - number6; // 89100
        number0 = number6 * number7; // 108817525
        number0 *= number7; // -131125117625
        --number0;
        number0--;
        number0 = number11.Shift(5);
        number0 = number11.Shift(-1);
        number0 = number11.Shift(-5);
        number0 = number11.Shift(-9);
        number0 = number11.Shift(-1000);
        number0 = number11 / VBigNumber("1");
        number0 = number11 / number7; // 102453
        
        return;
    }
    
}
