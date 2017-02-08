#include "VAngle.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAngle
    //----------------------------------------------------------------------------------------------------
    VAngle::VAngle()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VAngle::VAngle(const VAngle& _angle)
        :
        radian(_angle.radian)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VAngle::~VAngle()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    void VAngle::SetRadian(float _radian)
    {
        radian = _radian;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VAngle::SetCircle(float _circle)
    {
        radian = _circle * V_ANGLE_2PI;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VAngle::SetDegree(float _degree)
    {
        radian = _degree / 360.f * V_ANGLE_2PI;
    }

}
