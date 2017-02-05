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
        virtual ~VImageData();
        
    public:
        //----------------------------------------------------------------------------------------------------
        int width;
        int height;
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
        
    protected:
        //----------------------------------------------------------------------------------------------------
        VSmartPtr<VAny> data;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VImageTest();
}

#endif
