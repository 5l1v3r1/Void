#pragma once
#ifndef _V_MATH_H_
#define _V_MATH_H_

#include <algorithm>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VMath
    //----------------------------------------------------------------------------------------------------
    class VMath
    {
    public:
        // Greatest Common Divisor
        //----------------------------------------------------------------------------------------------------
        // Euclidean
        //----------------------------------------------------------------------------------------------------
        template<typename _T=unsigned>
        static _T GreatestCommonDivisor(_T _first, _T second)
        {
            if (_first == 0 || second == 0)
            {
                return _first == 0 ? (second < 0 ? -second : second) : (_first < 0 ? -_first : _first);
            }
            while (true)
            {
                _first %= second;
                if (_first == 0)
                {
                    return second < 0 ? -second : second;
                }
                second %= _first;
                if (second == 0)
                {
                    return _first < 0 ? -_first : _first;
                }
            }
        }
        
        // Least Common Multiple
        //----------------------------------------------------------------------------------------------------
        template<typename _T=unsigned>
        static _T LeastCommonMultiple(_T _first, _T second)
        {
            _T gcd = GreatestCommonDivisor(_first, second);
            return gcd == 0 ? 0 : gcd * (_first / gcd) * (second / gcd);
        }
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VMathTest();
}

#endif
