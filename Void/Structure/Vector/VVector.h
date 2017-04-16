#pragma once
#ifndef _V_VECTOR_H_
#define _V_VECTOR_H_
#include <stddef.h>
#include <math.h>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VVectorN
    //----------------------------------------------------------------------------------------------------
    template<typename _T=float, size_t _S=4>
    class VVectorN
    {
    public:
        //----------------------------------------------------------------------------------------------------
        union
        {
            struct
            {
                _T x, y, z, w;
            };
            _T vector[_S];
        };
    };
    
    template<typename _T>
    class VVectorN<_T, 0>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        union
        {
            _T vector[0];
        };
    };
    
    template<typename _T>
    class VVectorN<_T, 1>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        union
        {
            struct
            {
                _T x;
            };
            _T vector[1];
        };
    };
    
    template<typename _T>
    class VVectorN<_T, 2>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        union
        {
            struct
            {
                _T x, y;
            };
            _T vector[2];
        };
    };
    
    template<typename _T>
    class VVectorN<_T, 3>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        union
        {
            struct
            {
                _T x, y, z;
            };
            _T vector[3];
        };
    };
    
    // VVector
    //----------------------------------------------------------------------------------------------------
    template <typename _T=float, size_t _S=4>
    struct VVector : public VVectorN<_T, _S>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        inline VVector()
        {
        }
        
        inline VVector(const _T& _x, const _T& _y=0, const _T& _z=0, const _T& _w=0)
        {
            SetValue(_x, _y, _z, _w);
        }
        
        inline VVector(const _T* _vector, const size_t _size)
        {
            for (size_t i = 0; i < _S && i < _size; ++i)
            {
                this->vector[i] = _vector[i];
            }
        }
        
        inline VVector(const VVector& _vector)
        {
            SetValue(_vector);
        }
        
        inline ~VVector()
        {
            
        }
        
        //----------------------------------------------------------------------------------------------------
        inline _T operator[](const size_t i) const
        {
            if (i < _S)
                return this->vector[i];
            return 0;
        }
        
        inline _T& operator[](const size_t i)
        {
            if (i < _S)
                return this->vector[i];
            return this->vector[_S - 1];
        }
        
        inline VVector& operator=(const VVector& _vector)
        {
            for (size_t i = 0; i < _S; ++i)
            {
                this->vector[i] = _vector[i];
            }
            return *this;
        }
        
        inline VVector operator+(const VVector& _vector) const
        {
            VVector result;
            for (size_t i = 0; i < _S; ++i)
            {
                result[i] = this->vector[i] + _vector[i];
            }
            return result;
        }
        
        inline VVector& operator+=(const VVector& _vector)
        {
            VVector result;
            for (size_t i = 0; i < _S; ++i)
            {
                this->vector[i] += _vector[i];
            }
            return *this;
        }
        
        inline VVector operator+(const _T& _t) const
        {
            VVector result;
            for (size_t i = 0; i < _S; ++i)
            {
                result[i] = this->vector[i] + _t;
            }
            return result;
        }
        
        inline VVector operator-(const VVector& _vector) const
        {
            VVector result;
            for (size_t i = 0; i < _S; ++i)
            {
                result[i] = this->vector[i] - _vector[i];
            }
            return result;
        }
        
        inline VVector operator-(const _T& _t) const
        {
            VVector result;
            for (size_t i = 0; i < _S; ++i)
            {
                result[i] = this->vector[i] - _t;
            }
            return result;
        }
        
        inline VVector operator*(const VVector& _vector) const
        {
            VVector result;
            for (size_t i = 0; i < _S; ++i)
            {
                result[i] = this->vector[i] * _vector[i];
            }
            return result;
        }
        
        inline VVector operator*(const _T& _t) const
        {
            VVector result;
            for (size_t i = 0; i < _S; ++i)
            {
                result[i] = this->vector[i] * _t;
            }
            return result;
        }
        
        inline VVector operator/(const VVector& _vector) const
        {
            VVector result;
            for (size_t i = 0; i < _S; ++i)
            {
                result[i] = this->vector[i] / _vector[i]; // 0
            }
            return result;
        }
        
        inline VVector operator/(const _T& _t) const
        {
            if (_t)
            {
                VVector result;
                for (size_t i = 0; i < _S; ++i)
                {
                    result[i] = this->vector[i] / _t;
                }
                return result;
            }
            return VVector();
        }
        
        //----------------------------------------------------------------------------------------------------
        inline VVector& SetValue(const _T _x, const _T _y=0, const _T _z=0, const _T _w=0)
        {
            _T tmp[4] = {_x, _y, _z, _w};
            for (size_t i = 0; i < _S && i <= 4; ++i)
            {
                this->vector[i] = tmp[i];
            }
            return *this;
        }
        
        inline VVector& SetValue(const VVector& _vector)
        {
            for (size_t i = 0; i < _S; ++i)
            {
                this->vector[i] = _vector[i];
            }
            return *this;
        }

        inline _T Length() const
        {
            _T tmp = 0;
            for (size_t i = 0; i < _S; ++i)
            {
                tmp += this->vector[i] * this->vector[i];
            }
            return sqrt(tmp);
        }
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VVectorTest();
}

#endif
