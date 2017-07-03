#include "./VPoissonDistribution.h"
#include <cmath>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VPoissonDistribution
    //----------------------------------------------------------------------------------------------------
    VPoissonDistribution::VPoissonDistribution()
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    VPoissonDistribution::VPoissonDistribution(const VPoissonDistribution& _distribution)
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    VPoissonDistribution::~VPoissonDistribution()
    {
        
    }
    
    // P(times) = e^(-λ) * λ^times / times!
    //----------------------------------------------------------------------------------------------------
    float VPoissonDistribution::ProbabilityDensityFunction(unsigned int _times) const
    {
        return std::powf(2.71828182845904523536f, -lambda) * std::powf(lambda, _times) / Factorial(_times);
    }
    
    // L(λ) = log(∏(f(sample|λ)))
    //      = ∑(log(e^(-λ) * λ^sample / sample!))
    //      = -n * λ + ∑(sample) * log(λ) - ∑(log(sample!))
    // L'(λ) = 0 => -n + ∑(sample) / λ = 0
    // MLE(λ) = ∑(sample) / n
    //----------------------------------------------------------------------------------------------------
    bool VPoissonDistribution::MaximumLikelihoodEstimation(std::vector<float> _samples)
    {
        if (_samples.size())
        {
            double total = 0;
            for (float sample : _samples)
            {
                total += sample;
            }
            lambda = total / _samples.size();
            return true;
        }
        return false;
    }
    
    // n!
    //----------------------------------------------------------------------------------------------------
    unsigned int VPoissonDistribution::Factorial(unsigned int _n) const
    {
        if (_n == 0)
        {
            return 1;
        }
        
        unsigned int result = 1;
        for (unsigned int i = 2; i <= _n; ++i)
        {
            result *= i;
        }
        return result;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VPoissonDistributionTest()
    {
        VPoissonDistribution distribution;
        distribution.lambda = 2;
        
        auto probability = distribution.ProbabilityDensityFunction(2);
        probability = distribution.ProbabilityDensityFunction(0);
        probability = distribution.ProbabilityDensityFunction(5);
        
        return;
    }
}
