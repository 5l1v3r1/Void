#pragma once
#ifndef _V_SPARSEMATRIX_H_
#define _V_SPARSEMATRIX_H_

#include <vector>
#include <map>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VSparseVector
    //----------------------------------------------------------------------------------------------------
    template<typename _T=float>
    class VSparseVector : public std::map<unsigned long, _T>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VSparseVector()
            :
            std::map<unsigned long, _T>()
        {
        }
        
        VSparseVector(std::initializer_list<typename std::map<unsigned long, _T>::value_type> _list)
            :
            std::map<unsigned long, _T>(_list)
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        _T& operator()(const unsigned long& _column)
        {
            return std::map<unsigned long, _T>::operator[](_column);
        }
        
        _T operator()(const unsigned long& _column) const
        {
            auto iterator = this->find(_column);
            if (iterator != this->end())
            {
                return iterator->second;
            }
            return 0;
        }
        
    };
    
    // VSparseMatrix
    //----------------------------------------------------------------------------------------------------
    template<typename _T=float>
    class VSparseMatrix
    {
    public:
        //----------------------------------------------------------------------------------------------------
        typedef _T value_type;
        typedef _T ValueType;
        
    public:
        //----------------------------------------------------------------------------------------------------
        inline VSparseMatrix()
            :
            mRows(0),
            mColumns(0),
            mMatrix()
        {
        }
        
        inline VSparseMatrix(const unsigned long& _rows, const unsigned long& _columns)
            :
            mRows(_rows),
            mColumns(_columns),
            mMatrix()
        {
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        unsigned long Rows() const
        {
            return mRows;
        }
        
        unsigned long Columns() const
        {
            return mColumns;
        }
        
        unsigned long Size() const
        {
            return mRows * mColumns;
        }
        
        unsigned long RealSize() const
        {
            unsigned long size = 0;
            for (auto& row : mMatrix)
            {
                size += row.second.size();
            }
            return size;
        }
        
        //----------------------------------------------------------------------------------------------------
        _T& operator()(const unsigned long& _row, const unsigned long& _column)
        {
            if (_row < mRows && _column < mColumns)
            {
                return mMatrix[_row][_column];
            }
            throw "VSparseMatrix: out of range";
        }
        
        _T operator()(const unsigned long& _row, const unsigned long& _column) const
        {
            if (_row < mRows && _column < mColumns)
            {
                return mMatrix[_row][_column];
            }
            throw "VSparseMatrix: out of range";
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        unsigned long mRows;
        unsigned long mColumns;
        std::map<unsigned long, VSparseVector<_T>> mMatrix;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VSparseMatrixTest();
}

#endif
