#pragma once
#ifndef _V_IMAGE_H_
#define _V_IMAGE_H_
#include "../Color/VColor.h"
#include "../Memory/SmartPtr/VSmartPtr.h"
#include "../Structure/Any/VAny.h"
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VImageData
    //----------------------------------------------------------------------------------------------------
    template<VColorFormat _F>
    class VImageData
    {
    public:
        //----------------------------------------------------------------------------------------------------
        inline VImageData()
            :
            width(0),
            height(0),
            data()
        {
        }
        
        inline VImageData(unsigned int _width, unsigned int _height)
            :
            width(_width),
            height(_height),
            data()
        {
            data.push_back(std::vector<VColor<_F>>(_width * _height, VColor<_F>()));
        }
        
        virtual ~VImageData()
        {
            
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        unsigned int width;
        unsigned int height;
        std::vector<std::vector<VColor<_F>>> data;
    };
    
    // VImage
    //----------------------------------------------------------------------------------------------------
    class VImage
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VImage();
        VImage(const VImage& _image);
        virtual ~VImage();
        
        //----------------------------------------------------------------------------------------------------
        template <VColorFormat _F>
        inline bool SetData(unsigned int _width, unsigned int _height)
        {
            m_colorFormat = _F;
            m_imageData.SetValue(new VAny(VImageData<_F>(_width, _height)));
            return true;
        }
        
        template <VColorFormat _F=V_COLOR_FORMAT_NONE>
        inline VImageData<_F>* Data()
        {
            if (m_imageData)
            {
                if (_F != V_COLOR_FORMAT_NONE)
                {
                    return VAnyCast<VImageData<_F>>(&(*m_imageData));
                }
                else
                {
                    // Todo
                }
            }
            return nullptr;
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        VColorFormat m_colorFormat;
        VSmartPtr<VAny> m_imageData;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VImageTest();
}

#endif
