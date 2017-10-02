#pragma once
#ifndef _V_FACTORIZATIONMACHINELEARNING_H_
#define _V_FACTORIZATIONMACHINELEARNING_H_

#include "../../../Structure/SparseMatrix/VSparseMatrix.h"
#include "../FactorizationMachineModel/VFactorizationMachineModel.h"
#include <vector>
#include <cmath>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VFactorizationMachineSample
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    struct VFactorizationMachineSample
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VFactorizationMachineSample(VSparseVector<_T> _features, double _result)
            :
            features(_features),
            result(_result)
        {
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        VSparseVector<_T> features;
        double result;
    };
    
    // VFactorizationMachineLearningType
    //----------------------------------------------------------------------------------------------------
    enum class VFactorizationMachineLearningType
    {
        StochasticGradientDescent = 0,
        AdaptiveSGD,
        AlternatingLeastSquares,
        MarkovChainMonteCarlo
    };
    
    // VFactorizationMachineLearning
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VFactorizationMachineLearning : public VFactorizationMachineModel<_T>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VFactorizationMachineLearning(unsigned int _dimension, unsigned int _k)
            :
            VFactorizationMachineModel<_T>(_dimension, _k),
            mLearningRate(0.01)
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        virtual ~VFactorizationMachineLearning()
        {
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        inline void Train(const std::vector<VFactorizationMachineSample<_T>>& _samples, unsigned int _maxTimes)
        {
            if (_samples.size() == 0)
            {
                return;
            }
            
            for (unsigned int i = 0; i < _maxTimes; ++i)
            {
                for (const VFactorizationMachineSample<_T>& sample : _samples)
                {
                    Learn(sample.features, sample.result);
                }
            }
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        virtual bool Learn(const VSparseVector<_T>& _features, const double& _result) = 0;
        
    protected:
        //----------------------------------------------------------------------------------------------------
        double mLearningRate;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VFactorizationMachineLearningTest();
}

#endif
