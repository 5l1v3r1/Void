#include "VColor.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // Test
    //----------------------------------------------------------------------------------------------------
    void VColorTest()
    {
        VColor<VColorFormat::RGB256> color;
        int size = sizeof(color);
        color.x = 5;
        color.y = 1;
        VColor<VColorFormat::RGB256> color2(color);
        unsigned char *test = (unsigned char *)&color2;
        test[0] = 100;
        VColor<VColorFormat::Float> color3;
        color3.SetValue(1.f, 0.5f, 0.6f, 1.0f);
        size = sizeof(color3);
        size += 0;
        
        return;
    }
}
