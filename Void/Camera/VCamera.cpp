#include "VCamera.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VCamera
    //----------------------------------------------------------------------------------------------------
    VCamera::VCamera()
        :
        VSmartPtr(nullptr)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VCamera::VCamera(const VCamera& _camera)
        :
        VSmartPtr(_camera)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VCamera::~VCamera()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VCamera::SetOrthogonaLens(float _width, float _height, float _nearZ, float _farZ, bool _isLeftHand)
    {
        if (!m_value)
        {
            this->SetValue(new VCameraData());
        }
        
        m_value->cameraType = V_CAMERA_TYPE_2D;
        m_value->projectionMatrix = _isLeftHand ? VMatrixOrthogonalLH(_width, _height, _nearZ, _farZ) : VMatrixOrthogonalRH(_width, _height, _nearZ, _farZ);
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    VCameraType VCamera::CameraType()
    {
        return m_value ? m_value->cameraType : V_CAMERA_TYPE_NONE;
    }
    
    //----------------------------------------------------------------------------------------------------
    VMatrix<> VCamera::Projection()
    {
        return m_value ? m_value->projectionMatrix : VMatrix<>::Identity();
    }
}
