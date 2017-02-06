#pragma once
#ifndef _V_MATRIX_H_
#define _V_MATRIX_H_
#include <stddef.h>
#include <math.h>
#include <algorithm>
#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VMatrixNM
    /*
        M (column)
     +-----+
     |     |
     |     | N (row)
     |     |
     +-----+
     */
    //----------------------------------------------------------------------------------------------------
    template<typename _T, size_t _N, size_t _M>
    class VMatrixNM
    {
    public:
        //----------------------------------------------------------------------------------------------------
        union
        {
            _T matrix[_N][_M];
        };
    };
    
    template<typename _T>
    class VMatrixNM<_T, 0, 0>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        union
        {
            _T matrix[0][0];
        };
    };
    
    template<typename _T>
    class VMatrixNM<_T, 1, 1>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        union
        {
            struct
            {
                _T m11;
            };
            _T matrix[1][1];
        };
    };
    
    template<typename _T>
    class VMatrixNM<_T, 2, 2>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        union
        {
            struct
            {
                _T m11, m12;
                _T m21, m22;
            };
            _T matrix[2][2];
        };
    };
    
    template<typename _T>
    class VMatrixNM<_T, 3, 3>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        union
        {
            struct
            {
                _T m11, m12, m13;
                _T m21, m22, m23;
                _T m31, m32, m33;
            };
            _T matrix[3][3];
        };
    };
    
    template<typename _T>
    class VMatrixNM<_T, 4, 4>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        union
        {
            struct
            {
                _T m11, m12, m13, m14;
                _T m21, m22, m23, m24;
                _T m31, m32, m33, m34;
                _T m41, m42, m43, m44;
            };
            _T matrix[4][4];
        };
    };

    // VMatrix
    //----------------------------------------------------------------------------------------------------
    template<typename _T, size_t _N, size_t _M>
    struct VMatrix : public VMatrixNM<_T, _N, _M>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        inline VMatrix()
        {
        }
        
        inline VMatrix(const _T* _matrix, const size_t _size)
        {
            std::memcpy((char*)this->matrix, (char*)_matrix, sizeof(_T) * std::min(_N * _M, _size));
        }
        
        inline VMatrix(const VMatrix& _matrix)
        {
            std::memcpy((char*)this->matrix, (char*)_matrix.matrix, sizeof(_T) * _N * _M);
        }
        
        inline ~VMatrix()
        {
            
        }
        
        //----------------------------------------------------------------------------------------------------
        inline _T operator() (size_t _row, size_t _column) const
        {
            return this->matrix[_row][_column];
        }
        
        inline _T& operator() (size_t _row, size_t _column)
        {
            return this->matrix[_row][_column];
        }
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VMatrixTest();
}

#endif
