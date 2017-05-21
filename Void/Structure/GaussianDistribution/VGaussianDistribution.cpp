#include "VGaussianDistribution.h"
#include "../Angle/VAngle.h"
#include <cmath>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VGaussianDistribution
    //----------------------------------------------------------------------------------------------------
    VGaussianDistribution::VGaussianDistribution()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VGaussianDistribution::VGaussianDistribution(float _mean, float _standardDeviation)
        :
        mean(_mean),
        standardDeviation(_standardDeviation)
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    VGaussianDistribution::VGaussianDistribution(const VGaussianDistribution& _distribution)
        :
        mean(_distribution.mean),
        standardDeviation(_distribution.standardDeviation)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VGaussianDistribution::~VGaussianDistribution()
    {
    }
    
    // PDF: f(x) = (1 / √(2π)) * exp(-(x - mean)^2 / (2variance))
    //----------------------------------------------------------------------------------------------------
    float VGaussianDistribution::ProbabilityDensityFunction(float _x)
    {
        float a = 1 / std::sqrtf(V_ANGLE_2PI);
        float b = 2 * powf(standardDeviation, 2);
        float c = _x - mean;
        
        return a * std::expf(-powf(c, 2) / b);
    }
    
    // CDF: F(x) = P(a ≤ x) = ∫x-∞(f(a)da) = (1 / 2) * (1 + erf((x - mean) / sqrt(2variance)))
    //----------------------------------------------------------------------------------------------------
    float VGaussianDistribution::CumulativeDensityFunction(float _x)
    {
        float a = 1 / 2.f;
        float b = sqrtf(2 * powf(standardDeviation, 2));
        float c = _x - mean;
        
        return a * (1 + std::erff(c / b));
    }
    
    //----------------------------------------------------------------------------------------------------
    float VGaussianDistribution::DifferentialEntropy()
    {
        return 0.5f * std::log(2 * V_ANGLE_PI * 2.71828182845904523536f * powf(standardDeviation, 2));
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VGaussianDistributionTest()
    {
        VGaussianDistribution distribution;
        distribution.mean = 0;
        distribution.standardDeviation = 1;
        
        float result = distribution.ProbabilityDensityFunction(0);
        result = distribution.ProbabilityDensityFunction(3);
        result = distribution.ProbabilityDensityFunction(10);
        
        result = distribution.CumulativeDensityFunction(0);
        result = distribution.CumulativeDensityFunction(3);
        
        return;
    }
}
