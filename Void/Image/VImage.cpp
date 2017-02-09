#include "VImage.h"
#include "BMPImage/VBMPImage.h"
#include "JPEGImage/VJPEGImage.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    //----------------------------------------------------------------------------------------------------
    VImage::VImage()
        :
        VSmartPtr(nullptr)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VImage::VImage(const VImage& _image)
        :
        VSmartPtr(_image)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VImage::~VImage()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    unsigned int VImage::Width() const
    {
        if (m_value)
        {
            return m_value->width;
        }
        return 0;
    }
    
    unsigned int VImage::Height() const
    {
        if (m_value)
        {
            return m_value->height;
        }
        return 0;
    }
    
    VColorFormat VImage::ColorFormat() const
    {
        if (m_value)
        {
            return m_value->colorFormat;
        }
        return V_COLOR_FORMAT_NONE;
    }
    
    unsigned char* VImage::Data(size_t index)
    {
        if (m_value)
        {
            if (index < m_value->data.size())
            {
                return m_value->data[index].data();
            }
        }
        return nullptr;
    }
    
    const unsigned char* VImage::Data(size_t index) const
    {
        if (m_value)
        {
            if (index < m_value->data.size())
            {
                return m_value->data[index].data();
            }
        }
        return nullptr;
    }
    
    bool VImage::SetData(unsigned int _width, unsigned int _height, VColorFormat _format)
    {
        SetValue(new VImageData(_width, _height, _format));
        return true;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VImageTest()
    {
        VBMPImageTest();
    }
}
