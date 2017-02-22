#pragma once
#ifndef _V_JPEGIMAGE_H_
#define _V_JPEGIMAGE_H_
#include "../VImage.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VJPEG Header
    //----------------------------------------------------------------------------------------------------
    #pragma pack(push, 2)
    struct VJPEGHeader
    {
        unsigned short startOfImage;
        unsigned short application;
        unsigned short size;
        unsigned char identifier[5];
        unsigned char version[2];
        unsigned char unit;
    };
    #pragma pack(pop)
    
    // VJPEGImage
    //----------------------------------------------------------------------------------------------------
    class VJPEGImage
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static VImage ReadFromFile(const char* _fileName);
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VJPEGImageTest();
}

#endif
