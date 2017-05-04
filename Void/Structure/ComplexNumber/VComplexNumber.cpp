#include "VComplexNumber.h"
#include "cmath"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VComplexNumber
    //----------------------------------------------------------------------------------------------------
    VComplexNumber::VComplexNumber()
        :
        real(0),
        imaginary(1)
    {
    }
    
    VComplexNumber::VComplexNumber(double _real)
        :
        real(_real),
        imaginary(0)
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber::VComplexNumber(double _real, double _imaginary)
        :
        real(_real),
        imaginary(_imaginary)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber::VComplexNumber(const VComplexNumber& _number)
        :
        real(_number.real),
        imaginary(_number.imaginary)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber::~VComplexNumber()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber& VComplexNumber::operator=(const VComplexNumber& _number)
    {
        this->real = _number.real;
        this->imaginary = _number.imaginary;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber VComplexNumber::operator+(const VComplexNumber& _number) const
    {
        return VComplexNumber(this->real + _number.real, this->imaginary + _number.imaginary);
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber& VComplexNumber::operator+=(const VComplexNumber& _number)
    {
        this->real += _number.real;
        this->imaginary += _number.imaginary;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber VComplexNumber::operator+(double _scalar)
    {
        return VComplexNumber(this->real + _scalar, this->imaginary);
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber& VComplexNumber::operator+=(double _scalar)
    {
        this->real += _scalar;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber operator+(double _scalar, const VComplexNumber& _number)
    {
        return VComplexNumber(_scalar + _number.real, _number.imaginary);
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber VComplexNumber::operator-(const VComplexNumber& _number) const
    {
        return VComplexNumber(this->real - _number.real, this->imaginary - _number.imaginary);
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber& VComplexNumber::operator-=(const VComplexNumber& _number)
    {
        this->real -= _number.real;
        this->imaginary -= _number.imaginary;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber VComplexNumber::operator-(double _scalar)
    {
        return VComplexNumber(this->real - _scalar, this->imaginary);
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber& VComplexNumber::operator-=(double _scalar)
    {
        this->real -= _scalar;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber operator-(double _scalar, const VComplexNumber& _number)
    {
        return VComplexNumber(_scalar - _number.real, -_number.imaginary);
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber VComplexNumber::operator*(const VComplexNumber& _number) const
    {
        return VComplexNumber(this->real * _number.real - this->imaginary * _number.imaginary, this->real * _number.imaginary + this->imaginary * _number.real);
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber& VComplexNumber::operator*=(const VComplexNumber& _number)
    {
        *this = *this * _number;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber VComplexNumber::operator*(double _scalar)
    {
        return VComplexNumber(this->real * _scalar, this->imaginary * _scalar);
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber& VComplexNumber::operator*=(double _scalar)
    {
        *this = *this * _scalar;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber operator*(double _scalar, const VComplexNumber& _number)
    {
        return VComplexNumber(_number.real * _scalar, _number.imaginary * _scalar);
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber VComplexNumber::operator/(const VComplexNumber& _number) const
    {
        if (_number.real == 0 && _number.imaginary == 0) // Error
        {
            return VComplexNumber();
        }
        double value = _number.real * _number.real + _number.imaginary * _number.imaginary;
        return VComplexNumber((this->real * _number.real + this->imaginary * _number.imaginary) / value, (this->imaginary * _number.real - this->real * _number.imaginary) / value);
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber& VComplexNumber::operator/=(const VComplexNumber& _number)
    {
        *this = *this / _number;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber VComplexNumber::operator/(double _scalar)
    {
        if (_scalar == 0) // Error
        {
            return VComplexNumber();
        }
        return VComplexNumber(this->real / _scalar, this->imaginary / _scalar);
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber& VComplexNumber::operator/=(double _scalar)
    {
        *this = *this / _scalar;
        return *this;
    }
    
    //
    //----------------------------------------------------------------------------------------------------
    VComplexNumber operator/(double _scalar, const VComplexNumber& _number)
    {
        return VComplexNumber(_scalar, 0) / _number;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VComplexNumber::operator==(const VComplexNumber& _number) const
    {
        return real == _number.real && imaginary == _number.imaginary;
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber VComplexNumber::Conjugate() const
    {
        return VComplexNumber(this->real, -this->imaginary);
    }
    
    //----------------------------------------------------------------------------------------------------
    double VComplexNumber::Absolute() const
    {
        return std::sqrt(real * real + imaginary * imaginary);
    }
    
    //----------------------------------------------------------------------------------------------------
    VComplexNumber VComplexNumber::SquareRoot() const
    {
        double value = std::sqrt(real * real + imaginary * imaginary);
        return VComplexNumber(std::sqrt((real + value) / 2), (imaginary < 0 ? -1 : 1) * std::sqrt((-real + value) / 2));
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VComplexNumberTest()
    {
        VComplexNumber number0(1, 2);
        number0 *= number0;
        
        return;
    }
}
