#pragma once
#ifndef _V_DYNAMICMATRIX_H_
#define _V_DYNAMICMATRIX_H_

#include "../../Memory/SmartPtr/VSmartPtr.h"
#include <vector>
#include <map>

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
            mRows(0),
            mColumns(0),
            mRowRoutes(),
            mColumnRoutes(),
            mMatrix(nullptr)
        {
        }
        
        inline VDynamicMatrix(const unsigned long& _rows, const unsigned long& _columns)
            :
            mRows(_rows),
            mColumns(_columns),
            mRowRoutes(),
            mColumnRoutes(),
            mMatrix(new std::vector<std::vector<_T>>(_rows, std::vector<_T>(_columns)))
        {
        }
        
        inline VDynamicMatrix(const unsigned long& _rows, const unsigned long& _columns, _T _defaultValue)
            :
            mRows(_rows),
            mColumns(_columns),
            mRowRoutes(),
            mColumnRoutes(),
            mMatrix(new std::vector<std::vector<_T>>(_rows, std::vector<_T>(_columns, _defaultValue)))
        {
        }
        
        inline VDynamicMatrix(const unsigned long& _rows, const unsigned long& _columns, _T* _values, const unsigned long& _count)
            :
            mRows(_rows),
            mColumns(_columns),
            mRowRoutes(),
            mColumnRoutes(),
            mMatrix(new std::vector<std::vector<_T>>(_rows, std::vector<_T>(_columns)))
        {
            SetValues(_values, _count);
        }
        
        inline VDynamicMatrix(const VDynamicMatrix& _matrix)
            :
            mRows(_matrix.mRows),
            mColumns(_matrix.mColumns),
            mRowRoutes(_matrix.mRowRoutes),
            mColumnRoutes(_matrix.mColumnRoutes),
            mMatrix(_matrix.mMatrix)
        {
        }
        
        ~VDynamicMatrix()
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        unsigned long Rows() const
        {
            return mRows;
        }
        
        unsigned long Columns() const
        {
            return mColumns;
        }
        
        //----------------------------------------------------------------------------------------------------
        void SetValues(_T* _values, const unsigned long& _count)
        {
            for (unsigned long row = 0; row < mRows; ++row)
            {
                for (unsigned long column = 0; column < mColumns; ++column)
                {
                    unsigned long index = row * mColumns + column;
                    if (_count <= index)
                    {
                        return;
                    }
                    (*this)(row, column) = _values[index];
                }
            }
        }
        
        //----------------------------------------------------------------------------------------------------
        _T& operator()(const unsigned long& _row, const unsigned long& _column)
        {
            if (_row < mRows && _column < mColumns)
            {
                unsigned long realRow = _row;
                auto route = mRowRoutes.find(_row);
                if (route != mRowRoutes.end())
                {
                    realRow = route->second;
                }
                unsigned long realColumn = _column;
                route = mColumnRoutes.find(_column);
                if (route != mColumnRoutes.end())
                {
                    realColumn = route->second;
                }
                return (*mMatrix)[realRow][realColumn];
            }
            throw "VDynamicMatrix: out of range";
        }
        
        _T operator()(const unsigned long& _row, const unsigned long& _column) const
        {
            if (_row < mRows && _column < mColumns)
            {
                unsigned long realRow = _row;
                auto route = mRowRoutes.find(_row);
                if (route != mRowRoutes.end())
                {
                    realRow = route->second;
                }
                unsigned long realColumn = _column;
                route = mColumnRoutes.find(_column);
                if (route != mColumnRoutes.end())
                {
                    realColumn = route->second;
                }
                return (*mMatrix)[realRow][realColumn];
            }
            throw "VDynamicMatrix: out of range";
        }
        
        //----------------------------------------------------------------------------------------------------
        VDynamicMatrix& operator=(const long long& _matrix);
        VDynamicMatrix& operator=(const VDynamicMatrix& _matrix);
        VDynamicMatrix operator+(const VDynamicMatrix& _matrix) const;
        VDynamicMatrix& operator+=(const VDynamicMatrix& _matrix);
        VDynamicMatrix operator+(long long _integer) const;
        VDynamicMatrix& operator+=(long long _integer);
        friend VDynamicMatrix operator+(long long _integer, const VDynamicMatrix& _matrix);
        VDynamicMatrix operator-() const;
        VDynamicMatrix operator-(const VDynamicMatrix& _matrix) const;
        VDynamicMatrix& operator-=(const VDynamicMatrix& _matrix);
        VDynamicMatrix operator-(long long _integer) const;
        VDynamicMatrix& operator-=(long long _integer);
        friend VDynamicMatrix operator-(long long _integer, const VDynamicMatrix& _matrix);
        VDynamicMatrix operator*(const VDynamicMatrix& _matrix) const;
        VDynamicMatrix& operator*=(const VDynamicMatrix& _matrix);
        VDynamicMatrix operator*(long long _integer) const;
        VDynamicMatrix& operator*=(long long _integer);
        friend VDynamicMatrix operator*(long long _integer, const VDynamicMatrix& _matrix);
        VDynamicMatrix operator/(const VDynamicMatrix& _matrix) const;
        VDynamicMatrix& operator/=(const VDynamicMatrix& _matrix);
        VDynamicMatrix operator/(long long _integer) const;
        VDynamicMatrix& operator/=(long long _integer);
        friend VDynamicMatrix operator/(long long _integer, const VDynamicMatrix& _matrix);
        
        //----------------------------------------------------------------------------------------------------
        VDynamicMatrix SubMatrix(const unsigned long& _omittedRow, const unsigned long& _omittedColumn) const
        {
            VDynamicMatrix subMatrix(*this);
            // Shift routes
            if (_omittedRow < subMatrix.mRows)
            {
                --subMatrix.mRows;
                auto& rowRoutes = subMatrix.mRowRoutes;
                for (unsigned long row = _omittedRow; row < subMatrix.mRows; ++row)
                {
                    auto route = rowRoutes.find(row + 1);
                    route != rowRoutes.end() ? rowRoutes[row] = route->second : rowRoutes[row] = row + 1;
                }
            }
            if (_omittedColumn < subMatrix.mColumns)
            {
                --subMatrix.mColumns;
                auto& columnRoutes = subMatrix.mColumnRoutes;
                for (unsigned long column = _omittedColumn; column < subMatrix.mColumns; ++column)
                {
                    auto route = columnRoutes.find(column + 1);
                    route != columnRoutes.end() ? columnRoutes[column] = route->second : columnRoutes[column] = column + 1;
                }
            }
            return subMatrix;
        }
        
        // The only way to get a copy
        // Reconstruct a same matrix with empty routes
        //----------------------------------------------------------------------------------------------------
        VDynamicMatrix Copy() const
        {
            VDynamicMatrix matrix(mRows, mColumns);
            for (unsigned long row = 0; row < mRows; ++row)
            {
                for (unsigned long column = 0; column < mColumns; ++column)
                {
                    matrix(row, column) = (*this)(row, column);
                }
            }
            return matrix;
        }
        
        //----------------------------------------------------------------------------------------------------
        VDynamicMatrix Transpose() const
        {
            VDynamicMatrix matrix(mColumns, mRows);
            for (unsigned long row = 0; row < mRows; ++row)
            {
                for (unsigned long column = 0; column < mColumns; ++column)
                {
                    matrix(column, row) = (*this)(row, column);
                }
            }
            return matrix;
        }
        
        // Minor recursive
        //----------------------------------------------------------------------------------------------------
        _T Determinant()
        {
            _T result = static_cast<_T>(0);
            if (mRows == mColumns && mRows != 0)
            {
                if (mRows == 1)
                {
                    return (*this)(0, 0);
                }
                else if (mRows == 2)
                {
                    return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
                }
                else
                {
                    for (unsigned long column = 0; column < mColumns; ++column)
                    {
                        VDynamicMatrix subMatrix = SubMatrix(0, column);
                        if (column % 2)
                        {
                            result -= (*this)(0, column) * subMatrix.Determinant();
                        }
                        else
                        {
                            result += (*this)(0, column) * subMatrix.Determinant();
                        }
                    }
                }
            }
            else
            {
                // Error
            }
            return result;
        }
        
        //----------------------------------------------------------------------------------------------------
        _T DotProduct(const VDynamicMatrix _matrix) const
        {
            _T result = static_cast<_T>(0);
            if (mRows == _matrix.mRows && mColumns == _matrix.mColumns)
            {
                for (unsigned long row = 0; row < mRows; ++row)
                {
                    for (unsigned long column = 0; column < mColumns; ++column)
                    {
                        result += (*this)(row, column) * _matrix(row, column);
                    }
                }
            }
            else
            {
                // Error
            }
            return result;
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        unsigned long mRows;
        unsigned long mColumns;
        std::map<unsigned long, unsigned long> mRowRoutes; // empty == common index
        std::map<unsigned long, unsigned long> mColumnRoutes; // empty == common index
        VSmartPtr<std::vector<std::vector<_T>>> mMatrix;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VDynamicMatrixTest();
}

#endif
