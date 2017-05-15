#pragma once
#ifndef _V_IMAGE_H_
#define _V_IMAGE_H_

#include "../../Memory/SmartPtr/VSmartPtr.h"
#include "../Color/VColor.h"
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VImageData
    //----------------------------------------------------------------------------------------------------
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
        
        inline VImageData(unsigned int _width, unsigned int _height, VColorFormat _format=V_COLOR_FORMAT_RGBA_256)
            :
            width(_width),
            height(_height),
            data()
        {
            colorFormat = _format;
            switch (_format)
            {
                case V_COLOR_FORMAT_NONE:
                    break;
                case V_COLOR_FORMAT_RGBA_FLOAT:
                    data.push_back(std::vector<unsigned char>(_width * _height * 16));
                    break;
                case V_COLOR_FORMAT_RGBA_256:
                case V_COLOR_FORMAT_BGRX_256:
                    data.push_back(std::vector<unsigned char>(_width * _height * 4));
                    break;
                case V_COLOR_FORMAT_RGB_256:
                    data.push_back(std::vector<unsigned char>(_width * _height * 3));
                    break;
                case V_COLOR_FORMAT_GRAY_256:
                    data.push_back(std::vector<unsigned char>(_width * _height * 1));
                    break;
                case V_COLOR_FORMAT_GRAYALPHA_256:
                    data.push_back(std::vector<unsigned char>(_width * _height * 2));
                    break;
            }
        }
        
        virtual ~VImageData()
        {
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        unsigned int width;
        unsigned int height;
        VColorFormat colorFormat;
        std::vector<std::vector<unsigned char>> data;
    };
    
    // VImage
    //----------------------------------------------------------------------------------------------------
    class VImage : protected VSmartPtr<VImageData>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static VImage ReadFromBMPFile(const char* _fileName);
        
    public:
        //----------------------------------------------------------------------------------------------------
        VImage();
        VImage(const VImage& _image);
        virtual ~VImage();
        
        //----------------------------------------------------------------------------------------------------
        unsigned int Width() const;
        unsigned int Height() const;
        VColorFormat ColorFormat() const;
        unsigned char* Data(size_t index=0);
        const unsigned char* Data(size_t index=0) const;
        bool SetData(unsigned int _width, unsigned int _height, VColorFormat _format=V_COLOR_FORMAT_RGBA_256);
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VImageTest();
}

#endif
