#pragma once
#ifndef _V_PASCALTRIANGLE_H_
#define _V_PASCALTRIANGLE_H_

#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VPascalTriangle
    // See also: VBinomialDistribution
    //----------------------------------------------------------------------------------------------------
    class VPascalTriangle
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static std::vector<std::vector<unsigned long long>> Generate(unsigned _n);
        
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VPascalTriangleTest();
}

#endif
