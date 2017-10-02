#pragma once
#ifndef _V_FACTORIZATIONMACHINEMODEL_H_
#define _V_FACTORIZATIONMACHINEMODEL_H_

#include "../../../Structure/SparseMatrix/VSparseMatrix.h"
#include "../../../Structure/DynamicMatrix/VDynamicMatrix.h"
#include "../../../Utility/Random/VRandom.h"
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VFactorizationMachineModel
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VFactorizationMachineModel
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VFactorizationMachineModel(unsigned int _dimension, unsigned int _k)
            :
            mBias(0),
            mWeights(_dimension, 0.01),
            mAuxiliaryVectors(_dimension, _k, VRandom().NormalMultipleRand<double>(_dimension * _k, 0, 0.01))
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        virtual ~VFactorizationMachineModel()
        {
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        inline void Reset(unsigned int _dimension, unsigned int _k)
        {
            mWeights.clear();
            mAuxiliaryVectors = VDynamicMatrix<double>(_dimension, _k);
            mWeights.resize(_dimension);
        }
        
        //----------------------------------------------------------------------------------------------------
        bool Perceive(const VSparseVector<_T>& _features, double& _result) const
        {
            std::vector<double> sums;
            return Perceive(_features, _result, sums);
        }
        
        //----------------------------------------------------------------------------------------------------
        bool Perceive(const VSparseVector<_T>& _features, double& _result, std::vector<double>& _sums) const
        {
            // b
            _result = mBias;
            // ∑(wi * xi)
            for (auto& feature : _features)
            {
                unsigned long i = feature.first;
                _result += mWeights[i] * _features(i);
            }
            // ∑(∑(vik * xi)^2 - ∑((vik * xi)^2)) / 2
            _sums.clear();
            _sums.resize(mAuxiliaryVectors.Columns(), 0);
            for (unsigned long k = 0; k < mAuxiliaryVectors.Columns(); ++k)
            {
                double squareSums = 0;
                for (auto& feature : _features)
                {
                    unsigned long i = feature.first;
                    double value = mAuxiliaryVectors(i, k) * _features(i);
                    _sums[k] += value;
                    squareSums += value * value;
                }
                _result += 0.5 * (_sums[k] * _sums[k] - squareSums);
            }
            return true;
        }

    protected:
        //----------------------------------------------------------------------------------------------------
        double mBias; // b
        std::vector<double> mWeights; // W(i)
        VDynamicMatrix<double> mAuxiliaryVectors; // V(i, k)
    };
}

#endif
