#include "VWAVAudio.h"
#include <fstream>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VWAVAudio
    //----------------------------------------------------------------------------------------------------
    VWAVAudio::VWAVAudio()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VWAVAudio::VWAVAudio(const VWAVAudio& _audio)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VWAVAudio::~VWAVAudio()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VWAVAudio::ReadFromFile(const char* _fileName)
    {
        std::ifstream fin(_fileName);
        if (fin.is_open())
        {
            do
            {
                // RIFF
                VWAVAudioChunk RIFFChunk;
                fin.read((char*)&RIFFChunk, sizeof(VWAVAudioChunk));
                if(!IsFourCC(RIFFChunk.fourCC, 'R', 'I', 'F', 'F')) { break; }
                // WAVE
                int formType;
                fin.read((char*)&formType, sizeof(formType));
                if(!IsFourCC(formType, 'W', 'A', 'V', 'E')) { break; }
                // Format
                VWAVAudioChunk formatChunk;
                fin.read((char*)&formatChunk, sizeof(VWAVAudioChunk));
                if(!IsFourCC(formatChunk.fourCC, 'f', 'm', 't', '\x20')) { break; }
                fin.read((char*)&mFormat, formatChunk.size);
                // List && Fact && Data
                VWAVAudioChunk chunk;
                fin.read((char*)&chunk, sizeof(VWAVAudioChunk));
                if (IsFourCC(chunk.fourCC, 'L', 'I', 'S', 'T'))
                {
                    // int listType;
                    // fin.read((char*)&listType, sizeof(listType));
                    fin.seekg(chunk.size, std::ios::cur);
                    fin.read((char*)&chunk, sizeof(VWAVAudioChunk));
                }
                if (IsFourCC(chunk.fourCC, 'f', 'a', 'c', 't'))
                {
                    
                }
                if (IsFourCC(chunk.fourCC, 'd', 'a', 't', 'a'))
                {
                    data.resize(chunk.size);
                    fin.read((char*)data.data(), sizeof(chunk.size));
                }
                else
                {
                    return false;
                }

                fin.close();
                return true;
            } while(false);
            fin.close();
        }

        return false;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VWAVAudio::IsFourCC(int _value, char _first, char _second, char _third, char _fourth)
    {
        return _value == (((int)_first) | (((int)_second) << 8) | (((int)_third) << 16) | (((int)_fourth) << 24));
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VWAVAudioTest()
    {
        VWAVAudio audio;
        
        return;
    }
    
}
