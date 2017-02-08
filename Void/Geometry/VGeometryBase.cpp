#include "VGeometryBase.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VGeometryBase
    //----------------------------------------------------------------------------------------------------
    VGeometryBase::VGeometryBase()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VGeometryBase::VGeometryBase(const VGeometryBase& _geometry)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VGeometryBase::~VGeometryBase()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VGeometryBase::Process()
    {
        bool result = false;
        if (Update())
            result = Render();
        
        return result;
    }
    
    //----------------------------------------------------------------------------------------------------
    VCamera VGeometryBase::Camera()
    {
        return m_camera;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VGeometryBase::SetCamera(VCamera& camera)
    {
        m_camera = camera;
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    VColor<V_COLOR_FORMAT_RGBA_FLOAT>* VGeometryBase::Color()
    {
        return m_color ? &(*m_color) : nullptr;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VGeometryBase::SetColor(const VColor<V_COLOR_FORMAT_RGBA_FLOAT>& _color)
    {
        m_color.SetValue(new VColor<V_COLOR_FORMAT_RGBA_FLOAT>(_color));
        return true;
    }
}
