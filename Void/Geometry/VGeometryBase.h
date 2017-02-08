#pragma once
#ifndef _V_GEOMETRYBASE_H_
#define _V_GEOMETRYBASE_H_
#include "../Memory/SmartPtr/VSmartPtr.h"
#include "../Color/VColor.h"
#include "../Camera/VCamera.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VGeometryBase
    //----------------------------------------------------------------------------------------------------
    class VGeometryBase
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VGeometryBase();
        VGeometryBase(const VGeometryBase& _geometry);
        virtual ~VGeometryBase();
        
        //----------------------------------------------------------------------------------------------------
        virtual bool Update() = 0;
        virtual bool Render() = 0;
        virtual bool Process();
        
        //----------------------------------------------------------------------------------------------------
        VCamera Camera();
        bool SetCamera(VCamera& camera);
        VColor<V_COLOR_FORMAT_RGBA_FLOAT>* Color();
        bool SetColor(const VColor<V_COLOR_FORMAT_RGBA_FLOAT>& _color);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        VCamera m_camera;
        VSmartPtr<VColor<V_COLOR_FORMAT_RGBA_FLOAT>> m_color;
    };
}

#endif
