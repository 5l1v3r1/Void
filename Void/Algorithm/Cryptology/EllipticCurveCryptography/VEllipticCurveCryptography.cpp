#include "VEllipticCurveCryptography.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VEllipticCurveCryptography
    //----------------------------------------------------------------------------------------------------
    VEllipticCurveCryptography::VEllipticCurveCryptography()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VEllipticCurveCryptography::VEllipticCurveCryptography(const VEllipticCurveCryptography& _cryptography)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VEllipticCurveCryptography::~VEllipticCurveCryptography()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    std::pair<double, double> VEllipticCurveCryptography::Plus(const std::pair<double, double>& _p, const std::pair<double, double>& _q)
    {
        if (_p == _q)
        {
            
        }
        else
        {
            // k = ∞
            if (_p.first == _q.first)
            {
                
            }
            else
            {
                // double k = (_p.second - _q.second) / (_p.first - _q.first);
            }
        }
        
        return std::pair<double, double>();
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VEllipticCurveCryptographyTest()
    {
        
    }
    
}
