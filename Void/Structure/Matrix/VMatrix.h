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
    template<typename _T=float, size_t _N=4, size_t _M=4>
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
    // Compile-time
    //----------------------------------------------------------------------------------------------------
    template<typename _T=float, size_t _N=4, size_t _M=4>
    struct VMatrix : public VMatrixNM<_T, _N, _M>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static inline VMatrix Zero()
        {
            VMatrix result;
            std::memset((char*)result.matrix, 0, sizeof(_T) * _N * _M);
            return result;
        }
        
        //----------------------------------------------------------------------------------------------------
        static inline VMatrix Identity()
        {
            VMatrix result;
            std::memset((char*)result.matrix, 0, sizeof(_T) * _N * _M);
            if (_N == _M)
            {
                for (int i = 0; i < _N; ++i)
                {
                    result.matrix[i][i] = 1;
                }
            }
            return result;
        }
        
        //----------------------------------------------------------------------------------------------------
        
        
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
        
        //----------------------------------------------------------------------------------------------------
        
    };
    
    // Orthogonal Matrix (Left-Hand, DirectX)
    /*
     [2x/w                 ]
     [     -2y/h           ]
     [            z/(f-n)  ]
     [  -1     1 -n/(f-n) 1]
     
     +----x         y z(0.f~1.f)
     |\       ==>   |/
     | z(n~f)     --+--x
     y              |
    */
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    VMatrix<_T, 4, 4> VMatrixOrthogonalLH(_T _width, _T _height, _T _nearZ=0.f, _T _farZ=1.f)
    {
        VMatrix<_T, 4, 4> result = VMatrix<_T, 4, 4>::Zero();
        float range = 1.f / (_farZ - _nearZ);
        result(0, 0) = 2.f / _width;
        result(1, 1) = -2.f / _height;
        result(2, 2) = range;
        result(3, 0) = -1.f; result(3, 1) = 1.f; result(3, 2) = -_nearZ * range; result(3, 3) = 1.f;
        
        return result;
    }
    
    // Orthogonal Matrix (Right-Hand, OpenGL)
    /*
     [2x/w                    ]
     [     -2y/h              ]
     [              2z/(f-n)  ]
     [  -1     1 -2n/(f-n)-1 1]
     
     +----x         y
     |\       ==>   |
     | z(n~f)     --+--x
     y             /|
                  z(1.f~-1.f)
    */
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    VMatrix<_T, 4, 4> VMatrixOrthogonalRH(_T _width, _T _height, _T _nearZ=0.f, _T _farZ=1.f)
    {
        VMatrix<_T, 4, 4> result = VMatrix<_T, 4, 4>::Zero();
        float range = 2.f / (_farZ - _nearZ);
        result(0, 0) = 2.f / _width;
        result(1, 1) = -2.f / _height;
        result(2, 2) = range;
        result(3, 0) = -1.f; result(3, 1) = 1.f; result(3, 2) = -_nearZ * range - 1; result(3, 3) = 1.f;
        
        return result;
    }
    
    // Perspective Matrix (Left-Hand, DirectX)
    // y field of view: (0°~180°)
    // aspect ratio: width / height
    // multiply result: (homogeneous)
    /*
     [xcot(0.5f)/a                      ]
     [             ycot(0.5v)           ]
     [                         f/(f-n) 1]
     [                        nf/(f-n)  ]
     
       y z(n~f, frustum)       y z(0.f~1.f)
       |/                ==>   |/
     --+--x                  --+--x
       |                       |
     */
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    VMatrix<_T, 4, 4> VMatrixPerspectiveLH(_T _yFOV, _T _aspectRatio, _T _nearZ=0.f, _T _farZ=1.f)
    {
        VMatrix<_T, 4, 4> result = VMatrix<_T, 4, 4>::Zero();
        float range = 1.f / (_farZ - _nearZ);
        result(0, 0) = 1 / (tan(_yFOV * 0.5f) *_aspectRatio);
        result(1, 1) = 1 / tan(_yFOV * 0.5f);
        result(2, 2) = _farZ * range; result.m(2, 3) = 1.0f;
        result(3, 2) = (_nearZ * _farZ) * range;
        
        return result;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VMatrixTest();
}

#endif
