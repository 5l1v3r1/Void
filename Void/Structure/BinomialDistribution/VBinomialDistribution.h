#pragma once
#ifndef _V_BINOMIALDISTRIBUTION_H_
#define _V_BINOMIALDISTRIBUTION_H_

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VBinomialDistribution
    //----------------------------------------------------------------------------------------------------
    struct VBinomialDistribution
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VBinomialDistribution();
        VBinomialDistribution(float _probability);
        VBinomialDistribution(const VBinomialDistribution& _distribution);
        ~VBinomialDistribution();
        
        //----------------------------------------------------------------------------------------------------
        float Tries(unsigned int _times, unsigned int _success);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        unsigned int Factorial(unsigned int _n);
        unsigned int Arrangement(unsigned int _n, unsigned int _m);
        unsigned int Combination(unsigned int _n, unsigned int _m);
        
    public:
        //----------------------------------------------------------------------------------------------------
        float probability;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VBinomialDistributionTest();
}

#endif
