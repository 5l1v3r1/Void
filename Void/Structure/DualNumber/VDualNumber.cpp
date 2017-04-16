#include "VDualNumber.h"
#include "math.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VDualNumber
    //----------------------------------------------------------------------------------------------------
    VDualNumber::VDualNumber()
        :
        real(0),
        dual(1)
    {
    }
    
    VDualNumber::VDualNumber(double _real)
        :
        real(_real),
        dual(0)
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber::VDualNumber(double _real, double _dual)
        :
        real(_real),
        dual(_dual)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber::VDualNumber(const VDualNumber& _number)
        :
        real(_number.real),
        dual(_number.dual)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber::~VDualNumber()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber& VDualNumber::operator=(const VDualNumber& _number)
    {
        this->real = _number.real;
        this->dual = _number.dual;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber VDualNumber::operator+(const VDualNumber& _number) const
    {
        return VDualNumber(this->real + _number.real, this->dual + _number.dual);
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber& VDualNumber::operator+=(const VDualNumber& _number)
    {
        this->real += _number.real;
        this->dual += _number.dual;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber VDualNumber::operator-(const VDualNumber& _number) const
    {
        return VDualNumber(this->real - _number.real, this->dual - _number.dual);
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber& VDualNumber::operator-=(const VDualNumber& _number)
    {
        this->real -= _number.real;
        this->dual -= _number.dual;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber VDualNumber::operator*(const VDualNumber& _number) const
    {
        return VDualNumber(this->real * _number.real, this->real * _number.dual + this->dual * _number.real);
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber& VDualNumber::operator*=(const VDualNumber& _number)
    {
        this->real *= _number.real;
        this->dual = this->real * _number.dual + this->dual * _number.real;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber VDualNumber::operator/(const VDualNumber& _number) const
    {
        if (_number.real == 0) // Error: |_number| = 0
        {
            return VDualNumber();
        }
        return VDualNumber(this->real / _number.real, this->real * _number.dual + this->dual * _number.real);
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber& VDualNumber::operator/=(const VDualNumber& _number)
    {
        if (_number.real == 0) // Error: |_number| = 0
        {
            return *this;
        }
        this->real /= _number.real;
        this->dual = (this->dual - (this->real / _number.real) * _number.dual) / _number.real;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber VDualNumber::Sin()
    {
        return VDualNumber(::sin(this->real), this->dual * ::cos(this->real));
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber VDualNumber::Cos()
    {
        return VDualNumber(::cos(this->real), -this->dual * ::sin(this->real));
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber VDualNumber::Pow(double _n)
    {
        return VDualNumber(::pow(this->real, _n), this->dual * _n * ::pow(this->real, _n - 1));
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber VDualNumber::Exp()
    {
        return VDualNumber(::exp(this->real), this->dual * ::exp(this->real));
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber VDualNumber::Log()
    {
        if (this->real <= 0) // Error
        {
            return VDualNumber();
        }
        return VDualNumber(::log(this->real), this->dual / this->real);
    }

    // Test
    //----------------------------------------------------------------------------------------------------
    void VDualNumberTest()
    {
        VDualNumber number0(5, 1);
        number0 *= number0;
        number0 = number0.Log();
        
        VDualNumber number1;
        number1 = number1.Pow(2);
        
        return;
    }
}
