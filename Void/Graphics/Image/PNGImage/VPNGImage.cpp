#include "VPNGImage.h"
#include <fstream>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VPNGImage
    //----------------------------------------------------------------------------------------------------
    VImage VPNGImage::ReadFromFile(const char* _fileName)
    {
        std::ifstream fin(_fileName);
        if (fin.is_open())
        {
            do
            {
                
            } while(false);
            fin.close();
        }
        
        return VImage();
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VPNGImageTest()
    {
        //VImage image = VPNGImage::ReadFromFile("./Test/Data/lenna.png");
        
    }
}
