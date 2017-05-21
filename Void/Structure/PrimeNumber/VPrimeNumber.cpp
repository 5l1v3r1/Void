#include "VPrimeNumber.h"
#include "../../Utility/Logger/VLogger.h"
#include "../../Utility/Time/VTime.h"
#include <cmath>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VPrimeNumber
    //----------------------------------------------------------------------------------------------------
    bool VPrimeNumber::IsPrimeNumber(const unsigned long long& _number)
    {
        return true;
    }
    
    // π(x)
    // π(x) <= x / (log(x) - 1.1) + 5, x >= 4
    //----------------------------------------------------------------------------------------------------
    unsigned VPrimeNumber::ApproximateCount(const unsigned long long& _ceil)
    {
        return 0;
    }
    
    //----------------------------------------------------------------------------------------------------
    VPrimeNumber::VPrimeNumber()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VPrimeNumber::VPrimeNumber(const VPrimeNumber& _prime)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VPrimeNumber::~VPrimeNumber()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    void VPrimeNumber::EratosthenesSieve(const unsigned long long& _floor, const unsigned long long& _ceil, std::vector<unsigned long long>& _container)
    {
        // _container.reserve(_container.size());
        std::vector<bool> table(_ceil + 1, false); // Define: true(composite), false(prime)
        unsigned long long sieveFactorCeil = (unsigned long long)std::sqrtl(_ceil);
        for (unsigned long long sieveFactor = 2; sieveFactor <= sieveFactorCeil; ++sieveFactor)
        {
            if (!table[sieveFactor]) // Prime
            {
                if (_floor <= sieveFactor)
                {
                    _container.push_back(sieveFactor);
                }
                for (unsigned long long  j = sieveFactor * sieveFactor; j <= _ceil; j += sieveFactor)
                {
                    table[j] = true;
                }
            }
        }
        // Rest
        for (unsigned long long index = sieveFactorCeil + 1; index <= _ceil; ++index)
        {
            if (!table[index]) // Prime
            {
                _container.push_back(index);
            }
        }
        
        return;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VPrimeNumber::EratosthenesSieve6n(const unsigned long long& _floor, const unsigned long long& _ceil, std::vector<unsigned long long>& _container)
    {
        
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VPrimeNumberTest()
    {
        VPrimeNumber number;
        std::vector<unsigned long long> container;
        VTime time = VTime::Now();
        number.EratosthenesSieve(50, 10000000, container);
        VLogger::Info("Time: %ld", VTime::Now().Timestamp() - time.Timestamp());
        
        return;
    }
    
}
