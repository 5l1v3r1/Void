#pragma once
#ifndef _V_PRIMENUMBER_H_
#define _V_PRIMENUMBER_H_

#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VPrimeNumber
    // Prime: 2, 3, 5, 7, 11, 13, 17, 19, 23...
    //----------------------------------------------------------------------------------------------------
    class VPrimeNumber
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static bool IsPrimeNumber(const unsigned long long& _number);
        static unsigned ApproximateCount(const unsigned long long& _ceil);
        
    public:
        //----------------------------------------------------------------------------------------------------
        VPrimeNumber();
        VPrimeNumber(const VPrimeNumber& _prime);
        ~VPrimeNumber();
        
        //----------------------------------------------------------------------------------------------------
        void EratosthenesSieve(const unsigned long long& _floor, const unsigned long long& _ceil, std::vector<unsigned long long>& _container);
        void EratosthenesSieve6n(const unsigned long long& _floor, const unsigned long long& _ceil, std::vector<unsigned long long>& _container);
        
    protected:
        //----------------------------------------------------------------------------------------------------
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VPrimeNumberTest();
}

#endif
