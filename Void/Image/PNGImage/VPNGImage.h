#pragma once
#ifndef _V_PNGIMAGE_H_
#define _V_PNGIMAGE_H_
#include "../VImage.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VPNGImage
    //----------------------------------------------------------------------------------------------------
    class VPNGImage
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static VImage ReadFromFile(const char* _fileName);
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VPNGImageTest();
}

#endif
