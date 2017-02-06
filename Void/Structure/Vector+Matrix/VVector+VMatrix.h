#pragma once
#ifndef _V_VECTOR_V_MATRIX_H_
#define _V_VECTOR_V_MATRIX_H_
#include "../Vector/VVector.h"
#include "../Matrix/VMatrix.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VVector+VMatrix
    //----------------------------------------------------------------------------------------------------
    template<typename _T, size_t _N, size_t _M>
    VVector<_T, _M> operator*(const VVector<_T, _N>& _vector, const VMatrix<_T, _N, _M>& _metrix)
    {
        VVector<_T, _M> result;
        for (int i = 0; i < _M; ++i)
        {
            _T tmp = 0;
            for (int j = 0; j < _N; ++j)
            {
                tmp += _vector[j] * _metrix(j, i);
            }
            result[i] = tmp;
        }
        
        return result;
    }
    
    //----------------------------------------------------------------------------------------------------
    template<typename _T, size_t _S>
    VVector<_T, _S>& operator*=(VVector<_T, _S>& _vector, const VMatrix<_T, _S, _S>& _metrix)
    {
        VVector<_T, _S> result;
        for (int i = 0; i < _S; ++i)
        {
            _T tmp = 0;
            for (int j = 0; j < _S; ++j)
            {
                tmp += _vector[j] * _metrix(j, i);
            }
            result[i] = tmp;
        }
        _vector = result;
        
        return _vector;
    }
    
    // Translation Matrix
    /*
     [1      ]
     [  1    ]
     [    1  ]
     [X X X 1]
    */
    //----------------------------------------------------------------------------------------------------
    template<typename _T, size_t _S>
    VMatrix<_T, _S + 1, _S + 1> VMatrixTranslation(const VVector<_T, _S>& _vector)
    {
        VMatrix<_T, _S + 1, _S + 1> result = VMatrix<_T, _S + 1, _S + 1>::Identity();
        for (int i = 0; i < _S; ++i)
        {
            result(_S, i) = _vector[i];
        }
        
        return result;
    }

    // Test
    //----------------------------------------------------------------------------------------------------
    void VVectorVMatrixTest();
}

#endif
