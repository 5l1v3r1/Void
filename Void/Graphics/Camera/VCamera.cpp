#include "VCamera.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VCamera
    //----------------------------------------------------------------------------------------------------
    VCamera::VCamera()
        :
        VSharePointer(nullptr)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VCamera::VCamera(const VCamera& _camera)
        :
        VSharePointer(_camera)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VCamera::~VCamera()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VCamera::SetOrthogonaLens(float _width, float _height, float _nearZ, float _farZ, bool _isLeftHand)
    {
        if (!mValue)
        {
            this->SetValue(new VCameraData());
        }
        
        mValue->cameraType = V_CAMERA_TYPE_2D;
        mValue->projectionMatrix = _isLeftHand ? VMatrixOrthogonalLH(_width, _height, _nearZ, _farZ) : VMatrixOrthogonalRH(_width, _height, _nearZ, _farZ);
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    VCameraType VCamera::CameraType()
    {
        return mValue ? mValue->cameraType : V_CAMERA_TYPE_NONE;
    }
    
    //----------------------------------------------------------------------------------------------------
    VMatrix<> VCamera::Projection()
    {
        return mValue ? mValue->projectionMatrix : VMatrix<>::Identity();
    }
}
