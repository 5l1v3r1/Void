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
                char formType[4];
                fin.read((char*)&formType, sizeof(formType));
                if(!IsFourCC(formType, 'W', 'A', 'V', 'E')) { break; }
                // Format
                VWAVAudioChunk formatChunk;
                fin.read((char*)&formatChunk, sizeof(VWAVAudioChunk));
                if(!IsFourCC(formatChunk.fourCC, 'f', 'm', 't', '\x20')) { break; }
                std::streampos rollback = fin.tellg();
                fin.read((char*)&mFormat, formatChunk.size);
                if (mFormat.formatTag == 1)
                {
                    if (formatChunk.size < 16)
                    {
                        break;
                    }
                }
                else if (mFormat.formatTag == 0xFFFE)
                {
                    // Extensible
                    if (formatChunk.size < 40 || mFormat.extraSize < 22)
                    {
                        break;
                    }
                    fin.seekg(2, std::ios::cur);
                    fin.seekg(4, std::ios::cur);
                    int guid1, guid2, guid3, guid4;
                    fin.read((char*)&guid1, 4);
                    fin.read((char*)&guid2, 4);
                    fin.read((char*)&guid3, 4);
                    fin.read((char*)&guid4, 4);
                    if (guid1 != 0x00000001 || guid2 != 0x00100000 || guid3 != 0xAA000080 || guid4 != 0x719B3800)
                    {
                        break;
                    }
                }
                fin.seekg(rollback + std::streamoff(formatChunk.size));
                // List && Fact && Data
                while (!fin.eof())
                {
                    VWAVAudioChunk chunk;
                    fin.read((char*)&chunk, sizeof(VWAVAudioChunk));
                    if (IsFourCC(chunk.fourCC, 'L', 'I', 'S', 'T'))
                    {
                        fin.seekg(chunk.size, std::ios::cur);
                    }
                    else if (IsFourCC(chunk.fourCC, 'f', 'a', 'c', 't'))
                    {
                        fin.seekg(chunk.size, std::ios::cur);
                    }
                    else if (IsFourCC(chunk.fourCC, 'd', 'a', 't', 'a'))
                    {
                        mData.resize(chunk.size);
                        fin.read((char*)mData.data(), chunk.size); // Todo: stream mode
                        // Done
                        fin.close();
                        return true;
                    }
                    else
                    {
                        fin.seekg(chunk.size, std::ios::cur);
                    }
                }
            } while(false);
            fin.close();
        }
        return false;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VWAVAudio::WriteToFile(const char* _fileName)
    {
        if (mData.size() == 0)
        {
            return false;
        }
        
        std::ofstream fout(_fileName);
        if (fout.is_open())
        {
            fout << "RIFF";
            fout.write((char*)BinaryString(int(4 + 8 + 16 + 8 + mData.size())).data(), 4);
            fout << "WAVE";
            fout << "fmt\x20";
            fout.write((char*)BinaryString(int(sizeof(VWAVAudioFormatData) - 2)).data(), 4);
            fout.write((char*)&mFormat, sizeof(VWAVAudioFormatData) - 2);
            fout << "data";
            fout.write((char*)BinaryString(int(mData.size())).data(), 4);
            fout.write((char*)mData.data(), mData.size());
            fout.close();
            return true;
        }
        return false;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VWAVAudio::IsFourCC(char _value[4], char _first, char _second, char _third, char _fourth)
    {
        return _value[0] == _first && _value[1] == _second && _value[2] == _third && _value[3] == _fourth;
    }
    
    //----------------------------------------------------------------------------------------------------
    std::string VWAVAudio::BinaryString(int _value)
    {
        return std::string((char*)&_value, sizeof(_value));
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VWAVAudioTest()
    {
        VWAVAudio audio;
        audio.ReadFromFile("Test/Data/right.wav");
        audio.WriteToFile("Test/Data/right_saved.wav");
        
        return;
    }
    
}
