#include "VColor.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // Test
    //----------------------------------------------------------------------------------------------------
    void VColorTest()
    {
        VColor<V_COLOR_FORMAT_RGB_256> color;
        int size = sizeof(color);
        color.x = 5;
        color.y = 1;
        VColor<V_COLOR_FORMAT_RGB_256> color2(color);
        unsigned char *test = (unsigned char *)&color2;
        test[0] = 100;
        VColor<V_COLOR_FORMAT_RGBA_FLOAT> color3;
        color3.SetValue(1.f, 0.5f, 0.6f, 1.0f);
        size = sizeof(color3);
        size += 0;
        
        return;
    }
}
