#include "VBMPImage.h"
#include <fstream>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VBMPImage
    // Todo
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
                int bytesPerColor = infoHeader.bitCount >> 3;
                VImage image;
                unsigned char *buffer = nullptr;
                if (bytesPerColor == 1)
                {
                    image.SetData(width, height, V_COLOR_FORMAT_GRAY_256);
                }
                else if (bytesPerColor == 3)
                {
                    image.SetData(width, height, V_COLOR_FORMAT_RGB_256);
                }
                buffer = image.Data();
                
                
                fin.seekg(fileHeader.offBits, std::ios::beg);
                if(infoHeader.height > 0)
                {
                    fin.read((char*)buffer, width * height * bytesPerColor);
                }
                else
                {
                    for(int i = 0; i < height; ++i)
                    {
                        fin.read((char*)buffer + (height - 1 - i) * width * bytesPerColor, width * bytesPerColor);
                    }
                }
                
                fin.close();
                return image;
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
