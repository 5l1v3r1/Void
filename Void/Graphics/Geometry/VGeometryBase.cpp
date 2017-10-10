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
    VColor<VColorFormat::Float>* VGeometryBase::Color()
    {
        return m_color ? &(*m_color) : nullptr;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VGeometryBase::SetColor(const VColor<VColorFormat::Float>& _color)
    {
        m_color.SetValue(new VColor<VColorFormat::Float>(_color));
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    VImage VGeometryBase::Image()
    {
        return m_image;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VGeometryBase::SetImage(VImage& _image)
    {
        m_image = _image;
        return true;
    }
}
