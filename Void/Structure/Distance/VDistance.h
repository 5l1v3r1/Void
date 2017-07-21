#pragma once
#ifndef _V_DISTANCE_H_
#define _V_DISTANCE_H_

#include <cmath>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VDynamicMatrix;
    
    // VDistanceType
    //----------------------------------------------------------------------------------------------------
    enum class VDistanceType
    {
        Cityblock = 0,
        BrayCurtis,
        Cosine,
        Hamming,
        Jaccard,
        Euclidean,
    };
    
    // VDistanceInterface
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VDistanceInterface
    {
    protected:
        //----------------------------------------------------------------------------------------------------
        static bool IsValid(const _T& _u, const _T& _v)
        {
            return Size(_u) == Size(_v);
        }
        
        //----------------------------------------------------------------------------------------------------
        static unsigned long Size(const _T& _vector)
        {
            return _vector.size();
        }
        
        //----------------------------------------------------------------------------------------------------
        static typename _T::value_type DotProduct(const _T& _u, const _T& _v)
        {
            if (IsValid(_u, _v))
            {
                typename _T::value_type result(0);
                unsigned long size = Size(_u);
                for (unsigned long i = 0; i < size; ++i)
                {
                    result += _u[i] * _v[i];
                }
                return result;
            }
            return static_cast<typename _T::value_type>(0);
        }
        
        //----------------------------------------------------------------------------------------------------
        static _T Subtract(const _T& _u, const _T& _v)
        {
            if (IsValid(_u, _v))
            {
                _T result = _u;
                unsigned long size = Size(result);
                for (unsigned long i = 0; i < size; ++i)
                {
                    result[i] -= _v[i];
                }
                return result;
            }
            return _T();
        }
    };
    
    // VDistanceInterface: VDynamicMatrix
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VDistanceInterface<VDynamicMatrix<_T>>
    {
    protected:
        //----------------------------------------------------------------------------------------------------
        static bool IsValid(const VDynamicMatrix<_T>& _u, const VDynamicMatrix<_T>& _v)
        {
            return Size(_u) == Size(_v);
        }
        
        //----------------------------------------------------------------------------------------------------
        static unsigned long Size(const VDynamicMatrix<_T>& _vector)
        {
            return _vector.Size();
        }

        //----------------------------------------------------------------------------------------------------
        static _T DotProduct(const VDynamicMatrix<_T>& _u, const VDynamicMatrix<_T>& _v)
        {
            return _u.DotProduct(_v);
        }
        
        //----------------------------------------------------------------------------------------------------
        static VDynamicMatrix<_T> Subtract(const VDynamicMatrix<_T>& _u, const VDynamicMatrix<_T>& _v)
        {
            return _u - _v;
        }
    };
    
    // VDistance
    //----------------------------------------------------------------------------------------------------
    template<typename _T, VDistanceType _D>
    class VDistance : public VDistanceInterface<_T>
    {
    };
    
    // VDistance: Cityblock
    // City Block (Manhattan)
    // Distance = ∑(|ui - vi|)
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VDistance<_T, VDistanceType::Cityblock> : public VDistanceInterface<_T>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static typename _T::value_type Calculate(const _T& _u, const _T& _v)
        {
            if (VDistanceInterface<_T>::IsValid(_u, _v))
            {
                typename _T::value_type result(0);
                unsigned long size = VDistanceInterface<_T>::Size(_u);
                for (unsigned long i = 0; i < size; ++i)
                {
                    result += std::abs(_u[i] - _v[i]);
                }
                return result;
            }
            return static_cast<typename _T::value_type>(0);
        }
    };
    
    // VDistance: BrayCurtis
    // Bray-Curtis dissimilarity
    // Distance = ∑(|ui - vi|) / ∑(|ui + vi|)
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VDistance<_T, VDistanceType::BrayCurtis> : public VDistanceInterface<_T>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static double Calculate(const _T& _u, const _T& _v)
        {
            if (VDistanceInterface<_T>::IsValid(_u, _v))
            {
                typename _T::value_type numerator = 0;
                typename _T::value_type denominator = 0;
                unsigned long size = VDistanceInterface<_T>::Size(_u);
                for (unsigned long i = 0; i < size; ++i)
                {
                    numerator += std::abs(_u[i] - _v[i]);
                    denominator += std::abs(_u[i] + _v[i]);
                }
                if (denominator)
                {
                    return 1.0 * numerator / denominator;
                }
            }
            return 0;
        }
    };
    
    // VDistance: Cosine
    // Distance = 1 - u · v / (||u|| * ||v||)
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VDistance<_T, VDistanceType::Cosine> : public VDistanceInterface<_T>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static double Calculate(const _T& _u, const _T& _v)
        {
            if (VDistanceInterface<_T>::IsValid(_u, _v))
            {
                double numerator = VDistanceInterface<_T>::DotProduct(_u, _v);
                double denominator = std::sqrt(VDistanceInterface<_T>::DotProduct(_u, _u)) * std::sqrt(VDistanceInterface<_T>::DotProduct(_v, _v));
                return 1.0 - numerator / denominator;
            }
            return 0;
        }
    };
    
    // VDistance: Euclidean
    // Distance = ||u - v||
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VDistance<_T, VDistanceType::Euclidean> : public VDistanceInterface<_T>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static double Calculate(const _T& _u, const _T& _v)
        {
            if (VDistanceInterface<_T>::IsValid(_u, _v))
            {
                _T result = VDistanceInterface<_T>::Subtract(_u, _v);
                return std::sqrt(VDistanceInterface<_T>::DotProduct(result, result));
            }
            return 0;
        }
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VDistanceTest();
}

#endif
