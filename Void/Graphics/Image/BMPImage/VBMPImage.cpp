#include "VBMPImage.h"
#include <fstream>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VBMPImage
    // Todo
    //----------------------------------------------------------------------------------------------------
    VImage VBMPImage::ReadFromFile(const char* _fileName)
    {
        std::ifstream fin(_fileName);
        if (fin.is_open())
        {
            do
            {
                VBMPFileHeader fileHeader;
                VBMPInfoHeader infoHeader;
                fin.read((char*)&fileHeader, sizeof(fileHeader));
                if(fileHeader.type != 0x4D42) { break; } // BM
                fin.read((char*)&infoHeader, sizeof(infoHeader));
                if(infoHeader.size == 12 || infoHeader.planes != 1 || infoHeader.bitCount == 1 || infoHeader.compression != 0) { break; }
                
                int width = infoHeader.width;
                int height = abs(infoHeader.height);
                int bytesPerColor = infoHeader.bitCount >> 3;
                //int padding = 0;
                //int rowSize = 0;
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
                else
                {
                    break;
                }
                buffer = image.Data();
                
                fin.seekg(fileHeader.offBits, std::ios::beg);
                if (0 < infoHeader.height)
                {
                    char pixel[3];
                    for (int i = 0; i < infoHeader.sizeImage; i += bytesPerColor)
                    {
                        fin.read(pixel, 3);
                        buffer[i + 2] = pixel[0];
                        buffer[i + 1] = pixel[1];
                        buffer[i + 0] = pixel[2];
                    }
                }
                else
                {
                    for(int i = 0; i < height; ++i)
                    {
                        fin.read((char*)buffer + (height - 1 - i) * width * bytesPerColor, width * bytesPerColor); // Todo
                    }
                }
                
                fin.close();
                return image;
            } while(false);
            fin.close();
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
