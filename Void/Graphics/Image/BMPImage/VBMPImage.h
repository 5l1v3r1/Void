#pragma once
#ifndef _V_BMPIMAGE_H_
#define _V_BMPIMAGE_H_
#include "../VImage.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VBMP Header (14 + 40)
    //----------------------------------------------------------------------------------------------------
    #pragma pack(push, 2)
    struct VBMPFileHeader
    {
        unsigned short type;
        unsigned int size;
        unsigned short reserved1;
        unsigned short reserved2;
        unsigned int offBits;
    };
    
    struct VBMPInfoHeader
    {
        unsigned int size;
        int width; // (size == 12) => unsigned short
        int height;
        unsigned short planes;
        unsigned short bitCount;
        unsigned int compression;
        unsigned int sizeImage;
        int xPelsPerMeter;
        int yPelsPerMeter;
        unsigned int clrUsed;
        unsigned int clrImportant;
    };
    #pragma pack(pop)
    
    // VBMPImage (Bitmap)
    //----------------------------------------------------------------------------------------------------
    class VBMPImage
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static VImage ReadFromFile(const char* _fileName);
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VBMPImageTest();
}

#endif
