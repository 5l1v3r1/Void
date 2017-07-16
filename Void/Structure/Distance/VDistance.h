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
    };
    
    // VDistanceInterface
    //----------------------------------------------------------------------------------------------------
    template<template<typename...> class _Template, typename _T>
    class VDistanceInterface
    {
    protected:
        //----------------------------------------------------------------------------------------------------
        static bool IsValid(const _Template<_T>& _u, const _Template<_T>& _v)
        {
            return Size(_u) == Size(_v);
        }
        
        //----------------------------------------------------------------------------------------------------
        static unsigned long Size(const _Template<_T>& _vector)
        {
            return _vector.size();
        }
        
        //----------------------------------------------------------------------------------------------------
        static _T DotProduct(const _Template<_T>& _u, const _Template<_T>& _v)
        {
            if (IsValid(_u, _v))
            {
                _T result(0);
                unsigned long size = Size(_u);
                for (unsigned long i = 0; i < size; ++i)
                {
                    result += _u[i] * _v[i];
                }
                return result;
            }
            return static_cast<_T>(0);
        }
    };
    
    // VDistanceInterface: VDynamicMatrix
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VDistanceInterface<VDynamicMatrix, _T>
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
    };
    
    // VDistance
    //----------------------------------------------------------------------------------------------------
    template<template<typename...> class _Template, typename _T, VDistanceType _D>
    class VDistance : public VDistanceInterface<_Template, _T>
    {
    };
    
    // VDistance: Cityblock
    // City Block (Manhattan)
    // Distance = ∑(|ui - vi|)
    //----------------------------------------------------------------------------------------------------
    template<template<typename...> class _Template, typename _T>
    class VDistance<_Template, _T, VDistanceType::Cityblock> : public VDistanceInterface<_Template, _T>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static _T Calculate(const _Template<_T>& _u, const _Template<_T>& _v)
        {
            if (VDistanceInterface<_Template, _T>::IsValid(_u, _v))
            {
                _T result(0);
                unsigned long size = VDistanceInterface<_Template, _T>::Size(_u);
                for (unsigned long i = 0; i < size; ++i)
                {
                    result += std::abs(_u[i] - _v[i]);
                }
                return result;
            }
            return static_cast<_T>(0);
        }
    };
    
    // VDistance: BrayCurtis
    // Bray-Curtis dissimilarity
    // Distance = ∑(|ui - vi|) / ∑(|ui + vi|)
    //----------------------------------------------------------------------------------------------------
    template<template<typename...> class _Template, typename _T>
    class VDistance<_Template, _T, VDistanceType::BrayCurtis> : public VDistanceInterface<_Template, _T>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static double Calculate(const _Template<_T>& _u, const _Template<_T>& _v)
        {
            if (VDistanceInterface<_Template, _T>::IsValid(_u, _v))
            {
                _T numerator = 0;
                _T denominator = 0;
                unsigned long size = VDistanceInterface<_Template, _T>::Size(_u);
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
    template<template<typename...> class _Template, typename _T>
    class VDistance<_Template, _T, VDistanceType::Cosine> : public VDistanceInterface<_Template, _T>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static double Calculate(const _Template<_T>& _u, const _Template<_T>& _v)
        {
            if (VDistanceInterface<_Template, _T>::IsValid(_u, _v))
            {
                double numerator = VDistanceInterface<_Template, _T>::DotProduct(_u, _v);
                double denominator = std::sqrt(VDistanceInterface<_Template, _T>::DotProduct(_u, _u)) * std::sqrt(VDistanceInterface<_Template, _T>::DotProduct(_v, _v));
                return 1.0 - numerator / denominator;
            }
            return 0;
        }
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VDistanceTest();
}

#endif
