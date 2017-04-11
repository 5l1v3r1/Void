#pragma once
#ifndef _V_GAUSSIANDISTRIBUTION_H_
#define _V_GAUSSIANDISTRIBUTION_H_

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VGaussianDistribution
    // one-dimensional
    // PDF: f(x) = (1 / √(2π)) * exp(-(x - mean)^2 / (2variance))
    // ∫all(f(x)) = 1
    // P(a < x ≤ b) = ∫b-a(f(x)dx)
    // CDF: F(x) = P(a ≤ x) = ∫x-∞(f(a)da)
    //----------------------------------------------------------------------------------------------------
    struct VGaussianDistribution
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VGaussianDistribution();
        VGaussianDistribution(float _mean, float _standardDeviation);
        VGaussianDistribution(const VGaussianDistribution& _distribution);
        ~VGaussianDistribution();
        
        //----------------------------------------------------------------------------------------------------
        float ProbabilityDensityFunction(float _x);
        float CumulativeDensityFunction(float _x);
        float DifferentialEntropy();
        
    public:
        //----------------------------------------------------------------------------------------------------
        float mean;
        float standardDeviation; // square root of variance
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VGaussianDistributionTest();
}

#endif
