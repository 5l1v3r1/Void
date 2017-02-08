#pragma once
#ifndef _V_CAMERA_H_
#define _V_CAMERA_H_
#include "../Memory/SmartPtr/VSmartPtr.h"
#include "../Structure/Matrix/VMatrix.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VCameraType
    //----------------------------------------------------------------------------------------------------
    enum VCameraType
    {
        V_CAMERA_TYPE_NONE = 0,
        V_CAMERA_TYPE_2D = 1,
        V_CAMERA_TYPE_3D_FIRST = 2,
        V_CAMERA_TYPE_3D_THIRD = 3,
    };
    
    // VCameraData
    //----------------------------------------------------------------------------------------------------
    struct VCameraData
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VCameraType cameraType;
        VMatrix<> projectionMatrix;
    };
    
    // VCamera
    //----------------------------------------------------------------------------------------------------
    struct VCamera : protected VSmartPtr<VCameraData>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VCamera();
        VCamera(const VCamera& _camera);
        ~VCamera();
        
        //----------------------------------------------------------------------------------------------------
        bool SetOrthogonaLens(float _width, float _height, float _nearZ=0.f, float _farZ=1.f, bool _isLeftHand=true);
        VCameraType CameraType();
        VMatrix<> Projection();
    };
}

#endif
