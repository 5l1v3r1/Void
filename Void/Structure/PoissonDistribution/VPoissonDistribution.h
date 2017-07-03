#pragma once
#ifndef _V_POISSONDISTRIBUTION_H_
#define _V_POISSONDISTRIBUTION_H_

#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VPoissonDistribution
    // Discrete
    //----------------------------------------------------------------------------------------------------
    struct VPoissonDistribution
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VPoissonDistribution();
        VPoissonDistribution(const VPoissonDistribution& _distribution);
        ~VPoissonDistribution();
        
        //----------------------------------------------------------------------------------------------------
        float ProbabilityDensityFunction(unsigned int _times) const;
        bool MaximumLikelihoodEstimation(std::vector<float> _samples);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        unsigned int Factorial(unsigned int _n) const;
        
    public:
        //----------------------------------------------------------------------------------------------------
        float lambda; // Frequency
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VPoissonDistributionTest();
}

#endif
