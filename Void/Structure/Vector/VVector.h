#pragma once
#ifndef _V_VECTOR_H_
#define _V_VECTOR_H_
#include <stddef.h>
#include <math.h>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VVector
    //----------------------------------------------------------------------------------------------------
    template <typename _T, size_t _S>
    class VVector
    {
    public:
        //----------------------------------------------------------------------------------------------------
        inline VVector()
        {
        }
        
        inline VVector(const _T _x, const _T _y, const _T _z, const _T _w) : x(_x), y(_y), z(_z), w(_w)
        {
        }
        
        inline VVector(const _T* _vector, const size_t _size)
        {
            for (size_t i = 0; i < _S && i < _size; ++i)
            {
                vector[i] = _vector[i];
            }
        }
        
        inline VVector(const VVector& _vector)
        {
            for (size_t i = 0; i < _S; ++i)
            {
                vector[i] = _vector[i];
            }
        }
        
        inline virtual ~VVector()
        {
            
        }
        
        //----------------------------------------------------------------------------------------------------
        inline _T operator[] (const size_t i) const
        {
            if (i < _S)
                return vector[i];
            return 0;
        }
        
        inline _T& operator[] (const size_t i)
        {
            if (i < _S)
                return vector[i];
            return _S <= 0 ? w : vector[_S - 1];
        }
        
        inline VVector& operator= (const VVector& _vector)
        {
            for (size_t i = 0; i < _S; ++i)
            {
                vector[i] = _vector[i];
            }
            return *this;
        }
        
        inline VVector operator+ (const VVector& _vector) const
        {
            VVector result;
            for (size_t i = 0; i < _S; ++i)
            {
                result[i] = vector[i] + _vector[i];
            }
            return result;
        }
        
        inline VVector operator- (const VVector& _vector) const
        {
            VVector result;
            for (size_t i = 0; i < _S; ++i)
            {
                result[i] = vector[i] - _vector[i];
            }
            return result;
        }
        
        inline VVector operator- (const _T& _t) const
        {
            VVector result;
            for (size_t i = 0; i < _S; ++i)
            {
                result[i] = vector[i] - _t;
            }
            return result;
        }
        
        inline VVector operator* (const VVector& _vector) const
        {
            VVector result;
            for (size_t i = 0; i < _S; ++i)
            {
                result[i] = vector[i] * _vector[i];
            }
            return result;
        }
        
        inline VVector operator* (const _T& _t) const
        {
            VVector result;
            for (size_t i = 0; i < _S; ++i)
            {
                result[i] = vector[i] * _t;
            }
            return result;
        }
        
        inline VVector operator/ (const VVector& _vector) const
        {
            VVector result;
            for (size_t i = 0; i < _S; ++i)
            {
                result[i] = vector[i] / _vector[i]; // 0
            }
            return result;
        }
        
        inline VVector operator/ (const _T& _t) const
        {
            if (_t)
            {
                VVector result;
                for (size_t i = 0; i < _S; ++i)
                {
                    result[i] = vector[i] / _t;
                }
                return result;
            }
            return VVector();
        }
        
        //----------------------------------------------------------------------------------------------------
        inline _T Length() const
        {
            _T tmp = 0;
            for (size_t i = 0; i < _S; ++i)
            {
                tmp += vector[i] * vector[i];
            }
            return sqrt(tmp);
        }
        
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
}

#endif
