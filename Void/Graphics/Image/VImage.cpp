#include "VImage.h"
#include "BMPImage/VBMPImage.h"
#include "JPEGImage/VJPEGImage.h"
#include "PNGImage/VPNGImage.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VImage
    //----------------------------------------------------------------------------------------------------
    VImage VImage::ReadFromBMPFile(const char* _fileName)
    {
        return VBMPImage::ReadFromFile(_fileName);
    }
    
    //----------------------------------------------------------------------------------------------------
    VImage::VImage()
        :
        VSmartPointer(nullptr)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VImage::VImage(const VImage& _image)
        :
        VSmartPointer(_image)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VImage::~VImage()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    unsigned int VImage::Width() const
    {
        if (mValue)
        {
            return mValue->width;
        }
        return 0;
    }
    
    unsigned int VImage::Height() const
    {
        if (mValue)
        {
            return mValue->height;
        }
        return 0;
    }
    
    VColorFormat VImage::ColorFormat() const
    {
        if (mValue)
        {
            return mValue->colorFormat;
        }
        return V_COLOR_FORMAT_NONE;
    }
    
    unsigned char* VImage::Data(size_t index)
    {
        if (mValue)
        {
            if (index < mValue->data.size())
            {
                return mValue->data[index].data();
            }
        }
        return nullptr;
    }
    
    const unsigned char* VImage::Data(size_t index) const
    {
        if (mValue)
        {
            if (index < mValue->data.size())
            {
                return mValue->data[index].data();
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
        VJPEGImageTest();
        VPNGImageTest();
    }
}
