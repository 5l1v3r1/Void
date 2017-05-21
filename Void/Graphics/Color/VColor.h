#pragma once
#ifndef _V_COLOR_H_
#define _V_COLOR_H_

#include "../../Structure/Vector/VVector.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // YUV And RGB
    //----------------------------------------------------------------------------------------------------
    // Y = 0.299 * R + 0.587 * G + 0.114 * B
    // U = -0.147 * R - 0.289 * G + 0.436 * B = 0.492 * (B - Y)
    // V = 0.615 * R - 0.515 * G - 0.100 * B = 0.877 * (R - Y)
    //
    // R = Y + 1.140 * V
    // G = Y - 0.394 * U - 0.581 * V
    // B = Y + 2.032 * U
    
    // YCbCr And RGB
    //----------------------------------------------------------------------------------------------------
    // Y = 0.257 * R + 0.504 * G + 0.098 * B + 16
    // Cb = -0.148 * R - 0.291 * G + 0.439 * B + 128
    // Cr = 0.439 * R - 0.368 * G - 0.071 * B + 128
    //
    // R = 1.164 * (Y - 16) + 1.596 * (Cr - 128)
    // G = 1.164 * (Y - 16) - 0.813 * (Cr - 128) - 0.392 * (Cb - 128)
    // B = 1.164 * (Y - 16) + 2.017 * (Cb - 128)
    
    // YV12
    //----------------------------------------------------------------------------------------------------
    // YV12 (4 : 2 : 0)
    // Y(width * heigth) + V(width * heigth / 4) + U(width * heigth / 4)
    // size: width * heigth * 1.5 Byte
    
    // I420
    //----------------------------------------------------------------------------------------------------
    // I420 (4 : 2 : 0)
    // Y(width * heigth) + U(width * heigth / 4) + V(width * heigth / 4)
    // size: width * heigth * 1.5 Byte
    
    // VColorFormat
    //----------------------------------------------------------------------------------------------------
    enum VColorFormat
    {
        V_COLOR_FORMAT_NONE = 0,
        V_COLOR_FORMAT_RGBA_FLOAT = 1,
        V_COLOR_FORMAT_RGBA_256 = 2,
        V_COLOR_FORMAT_BGRX_256 = 3,
        V_COLOR_FORMAT_RGB_256 = 4,
        V_COLOR_FORMAT_GRAY_256 = 5,
        V_COLOR_FORMAT_GRAYALPHA_256 = 6,
    };
    
    // VColorData
    //----------------------------------------------------------------------------------------------------
    template <VColorFormat _F>
    struct VColorData : VVector<float, 4>
    {
    };
    
    template<>
    struct VColorData<V_COLOR_FORMAT_RGBA_256> : VVector<unsigned char, 4>
    {
    };
    
    template<>
    struct VColorData<V_COLOR_FORMAT_BGRX_256> : VVector<unsigned char, 4>
    {
    };
    
    template<>
    struct VColorData<V_COLOR_FORMAT_RGB_256> : VVector<unsigned char, 3>
    {
    };
    
    template<>
    struct VColorData<V_COLOR_FORMAT_GRAY_256> : VVector<unsigned char, 1>
    {
    };
    
    // VColor
    //----------------------------------------------------------------------------------------------------
    template <VColorFormat _F=V_COLOR_FORMAT_RGBA_FLOAT>
    struct VColor : VColorData<_F>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        inline VColor()
            :
            VColorData<_F>()
        {
        }
        
        template <typename _T>
        inline VColor(const _T _x, const _T _y=static_cast<_T>(0), const _T _z=static_cast<_T>(0), const _T _w=static_cast<_T>(0))
        {
            this->SetValue(_x, _y, _z, _w);
        }
        
        inline VColor(const VColor& _color)
            :
            VColorData<_F>(_color)
        {
        }
        
        inline ~VColor()
        {
            
        }
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VColorTest();
}

#endif
