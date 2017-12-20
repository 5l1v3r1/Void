#include "VDualNumber.h"
#include <cmath>
#include <assert.h>

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
    VDualNumber VDualNumber::operator+(double _scalar)
    {
        return VDualNumber(this->real + _scalar, this->dual);
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber& VDualNumber::operator+=(double _scalar)
    {
        this->real += _scalar;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber operator+(double _scalar, const VDualNumber& _number)
    {
        return VDualNumber(_scalar + _number.real, _number.dual);
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber VDualNumber::operator-() const
    {
        return VDualNumber(-this->real, -this->dual);
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
    VDualNumber VDualNumber::operator-(double _scalar)
    {
         return VDualNumber(this->real - _scalar, this->dual);
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber& VDualNumber::operator-=(double _scalar)
    {
        this->real -= _scalar;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber operator-(double _scalar, const VDualNumber& _number)
    {
        return VDualNumber(_scalar - _number.real, -_number.dual);
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
    VDualNumber VDualNumber::operator*(double _scalar)
    {
        return VDualNumber(this->real * _scalar, this->dual * _scalar);
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber& VDualNumber::operator*=(double _scalar)
    {
        this->real *= _scalar;
        this->dual *= _scalar;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber operator*(double _scalar, const VDualNumber& _number)
    {
        return VDualNumber(_number.real * _scalar, _number.dual * _scalar);
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber VDualNumber::operator/(const VDualNumber& _number) const
    {
        if (_number.real == 0) // Error: |_number| = 0
        {
            return VDualNumber();
        }
        return VDualNumber(this->real / _number.real, (this->dual - (this->real / _number.real) * _number.dual) / _number.real);
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
    VDualNumber VDualNumber::operator/(double _scalar)
    {
        if (_scalar == 0) // Error
        {
            return VDualNumber();
        }
        return VDualNumber(this->real / _scalar, this->dual / _scalar);
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber& VDualNumber::operator/=(double _scalar)
    {
        if (this->real == 0) // Error
        {
            return *this;
        }
        this->real /= _scalar;
        this->dual /= _scalar;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber operator/(double _scalar, const VDualNumber& _number)
    {
        if (_number.real == 0) // Error
        {
            return VDualNumber();
        }
        return VDualNumber(_scalar / _number.real, -(_scalar / _number.real) * _number.dual / _number.real);
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber VDualNumber::Sin()
    {
        return VDualNumber(std::sin(this->real), this->dual * std::cos(this->real));
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber VDualNumber::Cos()
    {
        return VDualNumber(std::cos(this->real), -this->dual * std::sin(this->real));
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber VDualNumber::Pow(double _n)
    {
        return VDualNumber(std::pow(this->real, _n), this->dual * _n * std::pow(this->real, _n - 1));
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber VDualNumber::Exp()
    {
        return VDualNumber(std::exp(this->real), this->dual * std::exp(this->real));
    }
    
    //----------------------------------------------------------------------------------------------------
    VDualNumber VDualNumber::Ln()
    {
        if (this->real <= 0) // Error
        {
            return VDualNumber();
        }
        return VDualNumber(std::log(this->real), this->dual / this->real);
    }

    // Test
    //----------------------------------------------------------------------------------------------------
    void VDualNumberTest()
    {
        // y = 3x
        VDualNumber var0(5, 1);
        auto result = 3 * var0;
        
        // y = (2x + 1)^2
        var0 = VDualNumber(5, 1);
        result = (2 * var0 + 1).Pow(2);
        
        // y = 2 / x
        var0 = VDualNumber(5, 1);
        result = 2 / var0;
        
        // z = 5 * x + y
        var0 = VDualNumber(5, 1);
        VDualNumber const0(5, 0);
        result = 5 * var0 + const0;
        
        // y = (2x + 1)^2 / e^x
        var0 = VDualNumber(5, 1);
        result = (2 * var0 + 1).Pow(2) / var0.Exp();
        
        // y = ln(x)
        var0 = VDualNumber(5, 1);
        result = var0.Ln();
        
        // output = 1 / (1 + e^-(w * x + b))
        // y = -ln((output^y * (1 - output)^(1 - y)))
        // ∂y/∂b = -(y - 1 / (1 + e^-(w * x + b)))
        double y = 0;
        double x = 5;
        VDualNumber w(1, 0);
        VDualNumber b(-5, 1);
        auto output = 1 / (1 + (-(w * x + b)).Exp());
        result = -(output.Pow(y) * (1 - output).Pow(1 - y)).Ln();
        double verification = -(y - 1 / (1 + std::exp(-(1 * x - 5))));
        assert(result.dual == verification);
        
        return;
    }
}
