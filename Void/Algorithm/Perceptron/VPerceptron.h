#pragma once
#ifndef _V_PERCEPTRON_H_
#define _V_PERCEPTRON_H_

#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VPerceptronSample
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    struct VPerceptronSample
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VPerceptronSample(std::vector<_T> _features, bool _result)
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
    
    // VPerceptron
    // Hyperplane: w * x + b = 0
    // Separating: f(x) = sign(w * x + b) = y
    // Error Distance: |w * xi + b| / ||w|| = -yi * (w * xi + b) / ||w|| where i ∈ Error Indices
    // Loss Function: L(w, b) = -∑(yi * (w * xi + b)) where i ∈ Error Indices
    // Goal: find min(w, b) for L(w, b)
    // Method: Stochastic Gradient Descent
    //         ∂L/∂w = -∑(yi * xi)
    //         ∂L/∂b = -∑(yi)
    //         for a stochastic sample (adjust direction w and offset b)
    //         w <- w + (Learning Rate) * yi * xi
    //         b <- b + (Learning Rate) * yi
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VPerceptron
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VPerceptron(unsigned int _dimension)
            :
            mLearningRate(0.1),
            mWeights(_dimension),
            mThreshold(0)
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        virtual ~VPerceptron()
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void Reset(unsigned int _dimension)
        {
            mWeights.clear();
            mWeights.resize(_dimension);
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void Train(const std::vector<VPerceptronSample<_T>>& _samples, unsigned int _maxTimes)
        {
            if (_samples.size() == 0)
            {
                return;
            }
            
            for (unsigned int i = 0; i < _maxTimes; ++i)
            {
                unsigned int errorCount = 0;
                for (VPerceptronSample<_T> sample : _samples)
                {
                    bool isError = Learn(sample);
                    if (isError)
                    {
                        ++errorCount;
                    }
                }
                
                if (errorCount == 0)
                {
                    return;
                }
            }
        }
        
        //----------------------------------------------------------------------------------------------------
        bool Perceive(const std::vector<_T>& _features, bool& _result) const
        {
            if (_features.size() != mWeights.size())
            {
                return false;
            }
            
            double value = 0;
            for (unsigned long i = 0; i < mWeights.size(); ++i)
            {
                value += mWeights[i] * _features[i];
            }
            _result = mThreshold < value;
            return true;
        }
        
        //----------------------------------------------------------------------------------------------------
        bool Perceive(const std::vector<_T>& _features) const
        {
            bool result = false;
            if (Perceive(_features, result))
            {
                return result;
            }
            throw "VPerceptron: perceive error";
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        bool Learn(const VPerceptronSample<_T>& _sample)
        {
            bool fakeResult = false;
            if (Perceive(_sample.features, fakeResult))
            {
                if (fakeResult != _sample.result)
                {
                    for (int i = 0; i < mWeights.size(); i++)
                    {
                        mWeights[i] += mLearningRate * (_sample.result ? 1.0 : -1.0) * _sample.features[i];
                    }
                    mThreshold += mLearningRate * (_sample.result ? -1.0 : 1.0);
                    return true;
                }
            }
            return false;
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        double mLearningRate;
        std::vector<double> mWeights; // w
        double mThreshold; // -b
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VPerceptronTest();
}

#endif
