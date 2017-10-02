#pragma once
#ifndef _V_FACTORIZATIONMACHINELEARNINGSGD_H_
#define _V_FACTORIZATIONMACHINELEARNINGSGD_H_

#include "./VFactorizationMachineLearning.h"
#include "../FactorizationMachineType/VFactorizationMachineType.h"
#include <vector>
#include <cmath>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VFactorizationMachineLearningSGD
    //----------------------------------------------------------------------------------------------------
    template<typename _T, VFactorizationMachineType _Type>
    class VFactorizationMachineLearningSGD : public VFactorizationMachineLearning<_T>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VFactorizationMachineLearningSGD(unsigned int _dimension, unsigned int _k)
            :
            VFactorizationMachineLearning<_T>(_dimension, _k),
            mBiasTerm(0),
            mWeightTerm(0),
            mAuxiliaryVectorTerm(0)
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        virtual ~VFactorizationMachineLearningSGD()
        {
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        virtual bool Learn(const VSparseVector<_T>& _features, const double& _result)
        {
            double fakeResult = 0;
            std::vector<double> sums;
            if (this->Perceive(_features, fakeResult, sums))
            {
                double lossGradient = 0;
                if (_Type == VFactorizationMachineType::Regression) // The least square error: (y(x) - y)
                {
                    lossGradient = fakeResult - _result;
                }
                else if (_Type == VFactorizationMachineType::Classification) // Logit loss: (σ(y(x) * y) - 1) * y
                {
                    lossGradient = (1.0 / (1.0 + std::exp(-fakeResult * _result)) - 1) * _result;
                }
                return Descent(_features, lossGradient, sums);
            }
            return false;
        }
        
        //----------------------------------------------------------------------------------------------------
        bool Descent(const VSparseVector<_T>& _features, const double& lossGradient, const std::vector<double>& _sums)
        {
            // Bias
            this->mBias -= this->mLearningRate * (lossGradient + mBiasTerm * this->mBias);
            // Weight
            for (unsigned long i = 0; i < this->mWeights.size(); ++i)
            {
                this->mWeights[i] -= this->mLearningRate * (lossGradient * _features(i) + mWeightTerm * this->mWeights[i]);
            }
            // Vector
            for (unsigned long k = 0; k < this->mAuxiliaryVectors.Columns(); ++k)
            {
                for (unsigned long i = 0; i < this->mAuxiliaryVectors.Rows(); ++i)
                {
                    double gradient = _sums[k] * _features(i) - this->mAuxiliaryVectors(i, k) * _sums[k] * _sums[k];
                    this->mAuxiliaryVectors(i, k) -= this->mLearningRate * (lossGradient * gradient + mAuxiliaryVectorTerm * this->mAuxiliaryVectors(i, k));
                }
            }
            return false;
        }
        
    protected:
        // Regularization Terms
        //----------------------------------------------------------------------------------------------------
        double mBiasTerm;
        double mWeightTerm;
        double mAuxiliaryVectorTerm;
    };
}

#endif
