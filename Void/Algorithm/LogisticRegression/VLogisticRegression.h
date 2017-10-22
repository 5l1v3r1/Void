#pragma once
#ifndef _V_LOGISTICREGRESSION_H_
#define _V_LOGISTICREGRESSION_H_

#include <vector>
#include <cmath>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VLogisticRegressionSample
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    struct VLogisticRegressionSample
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VLogisticRegressionSample(std::vector<_T> _features, bool _result)
            :
            features(_features),
            result(_result)
        {
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        std::vector<_T> features;
        bool result;
    };
    
    // VLogisticRegression
    //----------------------------------------------------------------------------------------------------
    // Linear: z = w * x + b
    // Mapping: output = σ(z) = sigmoid(z) = 1 / (1 + e^-z) = 1 / (1 + e^-(w * x + b)), 0 < output < 1
    // Lost Function: L(y, ouput) = -ln((output^y * (1 - ouput)^(1 - y)))
    //                            = -(y * ln(ouput) + (1 - y) * ln(1 - ouput))
    //                            = -(y * (ln(ouput) - ln(1 - ouput)) + ln(1 - output))
    //                            = -(y * ln(ouput / (1 - output)) + ln(1 - ouput))
    //                            = -(y * -ln(e^-z) + ln(e^-z) - ln(1 + e^-z))
    //                            = -(y * z - z - ln(1 + e^-z))
    //                            = -((y - 1) * z - ln(1 + e^-z))
    //                            = -((y - 1) * (w * x + b) - ln(1 + e^-(w * x + b)))
    // Cost Function: J(w, b) = ∑(L(y(i), ouput))
    //                ∂J/∂w = -∑((y - 1) * x - 1 / (1 + e^-(w * x + b)) * (e^-(w * x + b)) * -x)
    //                      = -∑((y - 1 / (1 + e^-(w * x + b))) * x)
    //                ∂J/∂b = -∑(y - 1 / (1 + e^-(w * x + b)))
    // Goal: (w, b) = arg(min(J(w, b)))
    // Method: Stochastic Gradient Descent
    //         for a stochastic sample (adjust direction w and offset b)
    //         w <- w + (Learning Rate) * (y - 1 / (1 + e^-(w * x + b))) * x
    //         b <- b + (Learning Rate) * (y - 1 / (1 + e^-(w * x + b)))
    // Classify: y = round(output)
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VLogisticRegression
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VLogisticRegression(unsigned int _dimension)
            :
            mLearningRate(0.01),
            mWeights(_dimension),
            mBias(0)
        {
        }

        //----------------------------------------------------------------------------------------------------
        virtual ~VLogisticRegression()
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void Reset(unsigned int _dimension)
        {
            mWeights.clear();
            mWeights.resize(_dimension);
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void Train(const std::vector<VLogisticRegressionSample<_T>>& _samples, unsigned int _maxTimes)
        {
            if (_samples.size() == 0)
            {
                return;
            }
            
            for (unsigned int i = 0; i < _maxTimes; ++i)
            {
                for (const VLogisticRegressionSample<_T>& sample : _samples)
                {
                    Learn(sample);
                }
            }
        }
        
        //----------------------------------------------------------------------------------------------------
        bool Perceive(const std::vector<_T>& _features, double& _result) const
        {
            if (_features.size() != mWeights.size())
            {
                return false;
            }
            
            double value = mBias;
            for (unsigned long i = 0; i < mWeights.size(); ++i)
            {
                value += mWeights[i] * _features[i];
            }
            _result = Sigmoid(value);
            return true;
        }
        
        //----------------------------------------------------------------------------------------------------
        bool Perceive(const std::vector<_T>& _features) const
        {
            double result = 0;
            if (Perceive(_features, result))
            {
                return 0.5 < result;
            }
            throw "VPerceptron: perceive error";
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        double Sigmoid(const double& _input) const
        {
            return 1.0 / (1 + std::exp(-_input));
        }
        
        //----------------------------------------------------------------------------------------------------
        bool Learn(const VLogisticRegressionSample<_T>& _sample)
        {
            double fakeResult = 0;
            if (Perceive(_sample.features, fakeResult))
            {
                for (int i = 0; i < mWeights.size(); i++)
                {
                    mWeights[i] += mLearningRate * (_sample.result - fakeResult) * _sample.features[i];
                }
                mBias += mLearningRate * (_sample.result - fakeResult);
                return true;
            }
            return false;
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        double mLearningRate;
        std::vector<double> mWeights; // w
        double mBias; // b
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VLogisticRegressionTest();
}

#endif
