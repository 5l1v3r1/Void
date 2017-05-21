#include "VBinomialDistribution.h"
#include <cmath>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VBinomialDistribution
    //----------------------------------------------------------------------------------------------------
    VBinomialDistribution::VBinomialDistribution()
        :
        probability(0.5f)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VBinomialDistribution::VBinomialDistribution(float _probability)
        :
        probability(_probability)
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    VBinomialDistribution::VBinomialDistribution(const VBinomialDistribution& _distribution)
        :
        probability(_distribution.probability)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VBinomialDistribution::~VBinomialDistribution()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    float VBinomialDistribution::Tries(unsigned int _times, unsigned int _success)
    {
        unsigned int combination = Combination(_times, _success);
        return combination * std::powf(probability, (float)_success) * std::powf(1 - probability, (float)(_times - _success));
    }
    
    // n!
    //----------------------------------------------------------------------------------------------------
    unsigned int VBinomialDistribution::Factorial(unsigned int _n)
    {
        if (_n == 0)
        {
            return 1;
        }
        
        unsigned int result = 1;
        for (unsigned int i = 2; i <= _n; ++i) {
            result *= i;
        }
        return result;
    }
    
    // A(n, m) = n! / (n - m)!
    //----------------------------------------------------------------------------------------------------
    unsigned int VBinomialDistribution::Arrangement(unsigned int _n, unsigned int _m)
    {
        if (_n == 0)
        {
            return 1;
        }
        
        unsigned int result = 1;
        for (unsigned int i = _n - _m + 1; i <= _n; ++i) {
            result *= i;
        }
        return result;
    }
    
    // C(n, m) = n! / (m! * (n - m)!)
    //----------------------------------------------------------------------------------------------------
    unsigned int VBinomialDistribution::Combination(unsigned int _n, unsigned int _m)
    {
        return Arrangement(_n, _m) / Factorial(_m);
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VBinomialDistributionTest()
    {
        VBinomialDistribution distribution;
        distribution.probability = 0.5;
        
        auto probability = distribution.Tries(100, 4);
        probability = distribution.Tries(2, 1);
        probability = distribution.Tries(4, 1);
        probability = distribution.Tries(8, 4);
        probability = distribution.Tries(5, 0) + distribution.Tries(5, 1) + distribution.Tries(5, 2) + distribution.Tries(5, 3) + distribution.Tries(5, 4) + distribution.Tries(5, 5);
        
        return;
    }
}
