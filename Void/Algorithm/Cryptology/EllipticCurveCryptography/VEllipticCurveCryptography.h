#pragma once
#ifndef _V_ELLIPTICCURVECRYPTOGRAPHY_H_
#define _V_ELLIPTICCURVECRYPTOGRAPHY_H_

#include <utility>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VEllipticCurveCryptography
    // Weierstrass
    // Common: (y^2) + (a1 * x * y) + (a3 * y) = (x3) + (a2 * x^2) + (a4 * x) + (a6)
    //         k = -Fx(x, y) / Fy(x, y) = (3 * x^2 + 2 * a2 * x + a4 - a1 * y) / (2 * y + a1 * x +a3)
    // Projection: X = x / z, Y = y / z
    //             (y^2 * z) + (a1 * x * y * z) + (a3 * y * z^2) = (x^3) + (a2 * x^2 * z) + (a3 * x * z^2) + (a6 * z^3)
    // P-Q-R' are collinear
    // R‘ = (x, f(x)[0]), R = (x, f(x)[1]), R = negative R'
    // P plus Q = R
    // O∞-R'-R-R' are collinear
    // O∞ plus R' = R'
    //----------------------------------------------------------------------------------------------------
    class VEllipticCurveCryptography
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VEllipticCurveCryptography();
        VEllipticCurveCryptography(const VEllipticCurveCryptography& _cryptography);
        ~VEllipticCurveCryptography();
        
        //----------------------------------------------------------------------------------------------------
        double Slope(const std::pair<double, double>& _position);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::pair<double, double> Plus(const std::pair<double, double>& _p, const std::pair<double, double>& _q);
        
    public:
        //----------------------------------------------------------------------------------------------------
        double a1;
        double a2;
        double a3;
        double a4;
        double a6;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VEllipticCurveCryptographyTest();
}

#endif
