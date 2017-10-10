#pragma once
#ifndef _V_IMAGE_H_
#define _V_IMAGE_H_

#include "../../Memory/SmartPointer/VSmartPointer.h"
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
        
        inline VImageData(unsigned int _width, unsigned int _height, VColorFormat _format=VColorFormat::RGBA256)
            :
            width(_width),
            height(_height),
            data()
        {
            colorFormat = _format;
            switch (_format)
            {
                case VColorFormat::None:
                    break;
                case VColorFormat::Float:
                    data.push_back(std::vector<unsigned char>(_width * _height * 16));
                    break;
                case VColorFormat::RGBA256:
                case VColorFormat::BGRX256:
                    data.push_back(std::vector<unsigned char>(_width * _height * 4));
                    break;
                case VColorFormat::RGB256:
                    data.push_back(std::vector<unsigned char>(_width * _height * 3));
                    break;
                case VColorFormat::Gray256:
                    data.push_back(std::vector<unsigned char>(_width * _height * 1));
                    break;
                case VColorFormat::GrayAlpha256:
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
    class VImage : protected VSharePointer<VImageData>
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
        bool SetData(unsigned int _width, unsigned int _height, VColorFormat _format=VColorFormat::RGBA256);
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VImageTest();
}

#endif
