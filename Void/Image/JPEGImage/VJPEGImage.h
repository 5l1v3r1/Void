#pragma once
#ifndef _V_JPEGIMAGE_H_
#define _V_JPEGIMAGE_H_

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VJPEGImage
    //----------------------------------------------------------------------------------------------------
    class VJPEGImage
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VJPEGImage();
        VJPEGImage(const VJPEGImage& _image);
        virtual ~VJPEGImage();
    };
}

#endif
