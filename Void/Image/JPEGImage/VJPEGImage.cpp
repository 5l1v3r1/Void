#include "VJPEGImage.h"
#include <fstream>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VJPEGImage
    //----------------------------------------------------------------------------------------------------
    VImage VJPEGImage::ReadFromFile(const char* _fileName)
    {
        std::ifstream fin(_fileName);
        if (fin.is_open())
        {
            do
            {
                VJPEGHeader header;
                fin.read((char*)&header, sizeof(header));
                
                VImage image;
                return image;
            } while(false);
            fin.close();
        }
        
        return VImage();
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VJPEGImageTest()
    {
        VImage image = VJPEGImage::ReadFromFile("./Test/Data/lenna.jpg");
        
    }
}
