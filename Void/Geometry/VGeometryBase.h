#pragma once
#ifndef _V_GEOMETRYBASE_H_
#define _V_GEOMETRYBASE_H_
#include "../Memory/SmartPtr/VSmartPtr.h"
#include "../Color/VColor.h"
#include "../Camera/VCamera.h"
#include "../Structure/Vector/VVector.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VVertexPosition
    //----------------------------------------------------------------------------------------------------
    struct VVertexPosition
    {
    public:
        //----------------------------------------------------------------------------------------------------
        inline VVertexPosition()
        {
        }
        
        inline VVertexPosition(const VVector<float, 3>& _position)
            :
            postion(_position)
        {
        }
        
        inline VVertexPosition(float _x, float _y=0, float _z=0)
            :
            postion(_x, _y, _z)
        {
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        VVector<float, 3> postion;
    };
    
    // VVertexTextureCoord
    //----------------------------------------------------------------------------------------------------
    struct VVertexTextureCoord
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VVector<float, 2> textureCoord;
    };
    
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
