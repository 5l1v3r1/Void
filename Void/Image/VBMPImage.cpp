#include "VBMPImage.h"
#include <fstream>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    //----------------------------------------------------------------------------------------------------
    VImage VBMPImage::ReadFromFile(const char* fileName)
    {
        std::ifstream fin(fileName);
        if (fin.is_open())
        {
            do
            {
                VBMPFileHeader fileHeader;
                VBMPInfoHeader infoHeader;
                fin.read((char*)&fileHeader, sizeof(fileHeader));
                if(fileHeader.type != 0x4D42) { break; }
                fin.read((char*)&infoHeader, sizeof(infoHeader));
                if(infoHeader.bitCount != 24 || infoHeader.compression != 0) { break; }
                
                int width = infoHeader.width;
                int height = infoHeader.height < 0 ? (-infoHeader.height) : infoHeader.height;
                int bmpSize = width * height * 3;
                unsigned char *buffer = new(std::nothrow) unsigned char[bmpSize];
                if(buffer == nullptr) { break; }
                fin.seekg(fileHeader.offBits, std::ios::beg);
                
                
                fin.close();
                return VImage();
            } while(false);
        }
        
        return VImage();
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VBMPImageTest()
    {
        VImage image = VBMPImage::ReadFromFile("./Test/Data/lenna.bmp");
    }
}
