#pragma once
#ifndef _V_DYNAMICMATRIX_H_
#define _V_DYNAMICMATRIX_H_

#include "../../Memory/SmartPtr/VSmartPtr.h"
#include <vector>
#include <map>
#include <string>
#include <sstream>

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
        _T Min() const
        {
            if (mRows == 0 || mColumns == 0)
            {
                return static_cast<_T>(0);
            }
            else
            {
                _T result = (*this)(0, 0);
                for (unsigned long row = 0; row < mRows; ++row)
                {
                    for (unsigned long column = 0; column < mColumns; ++column)
                    {
                        _T value = (*this)(row, column);
                        if (value < result)
                        {
                            result = value;
                        }
                    }
                }
                return result;
            }
        }
        
        _T Max() const
        {
            if (mRows == 0 || mColumns == 0)
            {
                return static_cast<_T>(0);
            }
            else
            {
                _T result = (*this)(0, 0);
                for (unsigned long row = 0; row < mRows; ++row)
                {
                    for (unsigned long column = 0; column < mColumns; ++column)
                    {
                        _T value = (*this)(row, column);
                        if (result < value)
                        {
                            result = value;
                        }
                    }
                }
                return result;
            }
        }
        
        std::pair<_T, _T> MinMax() const
        {
            if (mRows == 0 || mColumns == 0)
            {
                return std::pair<_T, _T>(static_cast<_T>(0), static_cast<_T>(0));
            }
            else
            {
                std::pair<_T, _T> result = std::pair<_T, _T>((*this)(0, 0), (*this)(0, 0));
                for (unsigned long row = 0; row < mRows; ++row)
                {
                    for (unsigned long column = 0; column < mColumns; ++column)
                    {
                        _T value = (*this)(row, column);
                        if (value < result.first)
                        {
                            result.first = value;
                        }
                        if (result.second < value)
                        {
                            result.second = value;
                        }
                    }
                }
                return result;
            }
        }
        
        //----------------------------------------------------------------------------------------------------
        std::string String() const
        {
            // Prepare
            std::vector<unsigned long> maxLengths(mColumns);
            for (unsigned long row = 0; row < mRows; ++row)
            {
                for (unsigned long column = 0; column < mColumns; ++column)
                {
                    std::stringstream sstream;
                    sstream << (*this)(row, column);
                    if (maxLengths[column] < sstream.str().length())
                    {
                        maxLengths[column] = sstream.str().length();
                    }
                }
            }
            for (unsigned long column = 0; column < mColumns; ++column)
            {
                maxLengths[column] += 1;
            }
            
            // Fill
            std::stringstream sstream;
            for (unsigned long row = 0; row < mRows; ++row)
            {
                sstream << '[';
                for (unsigned long column = 0; column < mColumns; ++column)
                {
                    sstream.width(maxLengths[column]);
                    sstream << std::right << (*this)(row, column);
                    if (column != mColumns - 1)
                    {
                        sstream << ',';
                    }
                }
                // sstream.seekp((long)sstream.tellp() - 1L);
                sstream << ']';
                if (row != mRows - 1)
                {
                    sstream << std::endl;
                }
            }
            return sstream.str();
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
        VDynamicMatrix& operator=(const _T& _scale)
        {
            for (unsigned long row = 0; row < mRows; ++row)
            {
                for (unsigned long column = 0; column < mColumns; ++column)
                {
                    (*this)(row, column) = _scale;
                }
            }
            return *this;
        }
        
        VDynamicMatrix& operator=(const VDynamicMatrix& _matrix)
        {
            mRows = _matrix.mRows;
            mColumns = _matrix.mColumns;
            mRowRoutes = _matrix.mRowRoutes;
            mColumnRoutes = _matrix.mColumnRoutes;
            mMatrix = _matrix.mMatrix;
            return *this;
        }
        
        //----------------------------------------------------------------------------------------------------
        VDynamicMatrix operator+(const VDynamicMatrix& _matrix) const;
        VDynamicMatrix& operator+=(const VDynamicMatrix& _matrix);
        VDynamicMatrix operator+(const _T& _scale) const;
        VDynamicMatrix& operator+=(const _T& _scale);
        friend VDynamicMatrix operator+(const _T& _scale, const VDynamicMatrix& _matrix);
        VDynamicMatrix operator-() const;
        VDynamicMatrix operator-(const VDynamicMatrix& _matrix) const;
        VDynamicMatrix& operator-=(const VDynamicMatrix& _matrix);
        VDynamicMatrix operator-(const _T& _scale) const;
        VDynamicMatrix& operator-=(const _T& _scale);
        friend VDynamicMatrix operator-(const _T& _scale, const VDynamicMatrix& _matrix);
        
        //----------------------------------------------------------------------------------------------------
        VDynamicMatrix operator*(const VDynamicMatrix& _matrix) const
        {
            if (mColumns != _matrix.mRows)
            {
                throw "VDynamicMatrix: invalid multiplication";;
            }
            
            VDynamicMatrix result(mRows, _matrix.mColumns, 0);
            for (unsigned long row = 0; row < mRows; ++row)
            {
                for (unsigned long column = 0; column < _matrix.mColumns; ++column)
                {
                    _T& value = result(row, column);
                    for (unsigned long index = 0; index < mColumns; ++index)
                    {
                        value += (*this)(row, index) * _matrix(index, column);
                    }
                }
            }
            return result;
        }
        
        VDynamicMatrix& operator*=(const VDynamicMatrix& _matrix)
        {
            *this = *this * _matrix;
            return *this;
        }
        
        VDynamicMatrix operator*(const _T& _scale) const
        {
            VDynamicMatrix result = this->Copy();
            for (unsigned long row = 0; row < mRows; ++row)
            {
                for (unsigned long column = 0; column < mColumns; ++column)
                {
                    result(row, column) *= _scale;
                }
            }
            return result;
        }
        
        VDynamicMatrix& operator*=(const _T& _scale)
        {
            *this = *this * _scale;
            return *this;
        }
        
        //----------------------------------------------------------------------------------------------------
        friend VDynamicMatrix operator*(const _T& _scale, const VDynamicMatrix& _matrix);
        VDynamicMatrix operator/(const VDynamicMatrix& _matrix) const;
        VDynamicMatrix& operator/=(const VDynamicMatrix& _matrix);
        VDynamicMatrix operator/(const _T& _scale) const;
        VDynamicMatrix& operator/=(const _T& _scale);
        friend VDynamicMatrix operator/(const _T& _scale, const VDynamicMatrix& _matrix);
        
        // Elementary transformation
        // Row switching: Ri <-> Rj
        // Row multiplication: kRi -> Ri, k ≠ 0
        // Row addition: Ri + kRj -> Ri, i ≠ j
        //----------------------------------------------------------------------------------------------------
        void RowSwitch(const unsigned long& _iRow, const unsigned long& _jRow)
        {
            if (_iRow < mRows && _jRow < mRows)
            {
                unsigned long realIRow = _iRow;
                auto route = mRowRoutes.find(_iRow);
                if (route != mRowRoutes.end())
                {
                    realIRow = route->second;
                }
                unsigned long realJRow = _jRow;
                route = mRowRoutes.find(_jRow);
                if (route != mRowRoutes.end())
                {
                    realJRow = route->second;
                }
                
                mRowRoutes[_iRow] = realJRow;
                mRowRoutes[_jRow] = realIRow;
            }
        }
        
        void RowMultiply(const unsigned long& _row, const _T& _factor)
        {
            if (_row < mRows)
            {
                for (unsigned long column = 0; column < mColumns; ++column)
                {
                    (*this)(_row, column) *= _factor;
                }
            }
        }
        
        void RowDivide(const unsigned long& _row, const _T& _factor)
        {
            if (_row < mRows)
            {
                for (unsigned long column = 0; column < mColumns; ++column)
                {
                    (*this)(_row, column) /= _factor;
                }
            }
        }
        
        void RowAdd(const unsigned long& _iRow, const unsigned long& _jRow, const _T& _factor)
        {
            if (_iRow < mRows && _jRow < mRows)
            {
                for (unsigned long column = 0; column < mColumns; ++column)
                {
                    (*this)(_iRow, column) += (*this)(_jRow, column) * _factor;
                }
            }
        }
        
        //----------------------------------------------------------------------------------------------------
        VDynamicMatrix SubMatrix(const unsigned long& _omittedRow, const unsigned long& _omittedColumn)
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
        
        // Reconstruct a same matrix with empty routes
        //----------------------------------------------------------------------------------------------------
        VDynamicMatrix Copy() const
        {
            VDynamicMatrix matrix(mRows, mColumns);
            // (*matrix.mMatrix) = *mMatrix;
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
        _T DotProduct(const VDynamicMatrix& _matrix) const
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
        
        // result = [this | other]
        //----------------------------------------------------------------------------------------------------
        VDynamicMatrix Concatenate(const VDynamicMatrix& _matrix) const
        {
            VDynamicMatrix result(mRows < _matrix.mRows ? _matrix.mRows : mRows, mColumns + _matrix.mColumns);
            for (unsigned long row = 0; row < mRows; ++row)
            {
                for (unsigned long column = 0; column < mColumns; ++column)
                {
                    result(row, column) = (*this)(row, column);
                }
            }
            for (unsigned long row = 0; row < _matrix.Rows(); ++row)
            {
                for (unsigned long column = 0; column < _matrix.mColumns; ++column)
                {
                    result(row, mColumns + column) = _matrix(row, column);
                }
            }
            
            return result;
        }
        
        // this = Lower * Upper
        // Doolittle algorithm
        // a00 a01 a02   1
        // a10 a11 a12 =  1
        // a20 a21 a22     1
        //----------------------------------------------------------------------------------------------------
        void LUDecomposition(VDynamicMatrix& _lower, VDynamicMatrix& _upper)
        {
            if (mRows != mColumns)
            {
                return;
            }
            
            _lower = VDynamicMatrix(mRows, mColumns);
            _upper = this->Copy();
            for (unsigned long row = 0; row < mRows; ++row)
            {
                _T value = _upper(row, row);
                if (value != 0)
                {
                    _upper.RowDivide(row, value); // Memo: int type
                    _lower(row, row) = value;
                }
                
                for (unsigned long subRow = row + 1; subRow < mRows; ++subRow)
                {
                    _T value = _upper(subRow, row);
                    _upper.RowAdd(subRow, row, -value);
                    _lower(subRow, row) = value;
                }
            }
            
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
