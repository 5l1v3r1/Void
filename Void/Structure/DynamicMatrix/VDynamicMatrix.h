#pragma once
#ifndef _V_DYNAMICMATRIX_H_
#define _V_DYNAMICMATRIX_H_

#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VDynamicMatrix
    // Runtime
    //----------------------------------------------------------------------------------------------------
    template<typename _T=float>
    class VDynamicMatrix
    {
    public:
        //----------------------------------------------------------------------------------------------------
        inline VDynamicMatrix()
            :
            mRow(0),
            mColumn(0),
            mMatrix()
        {
        }
        
        inline VDynamicMatrix(const unsigned long& _row, const unsigned long& _column)
            :
            mRow(_row),
            mColumn(_column),
            mMatrix(_row, std::vector<_T>(_column))
        {
        }
        
        inline VDynamicMatrix(const VDynamicMatrix& _matrix)
            :
            mRow(_matrix.mRow),
            mColumn(_matrix.mColumn),
            mMatrix(_matrix.mMatrix)
        {
            
        }
        
        ~VDynamicMatrix()
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------------------------
        
    protected:
        //----------------------------------------------------------------------------------------------------
        
    protected:
        //----------------------------------------------------------------------------------------------------
        unsigned long mRow;
        unsigned long mColumn;
        std::vector<std::vector<_T>> mMatrix;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VDynamicMatrixTest();
}

#endif
