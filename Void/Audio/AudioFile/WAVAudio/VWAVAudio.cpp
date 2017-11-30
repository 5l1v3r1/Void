#include "VWAVAudio.h"
#include <fstream>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VWAVAudio
    //----------------------------------------------------------------------------------------------------
    VWAVAudio::VWAVAudio()
        :
        VAudioBase(),
        mWAVFormat()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VWAVAudio::VWAVAudio(VAudioBase& _audio)
        :
        VAudioBase(_audio),
        mWAVFormat()
    {
        RefreshWAVFormat();
    }
    
    //----------------------------------------------------------------------------------------------------
    VWAVAudio::VWAVAudio(VAudioBase&& _audio)
        :
        VAudioBase(_audio),
        mWAVFormat()
    {
        RefreshWAVFormat();
    }
    
    //----------------------------------------------------------------------------------------------------
    VWAVAudio::VWAVAudio(const VWAVAudio& _audio)
        :
        VAudioBase(_audio),
        mWAVFormat(_audio.mWAVFormat)
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
                fin.read((char*)&mWAVFormat, formatChunk.size);
                if (mWAVFormat.formatTag == 1)
                {
                    if (formatChunk.size < 16)
                    {
                        break;
                    }
                }
                else if (mWAVFormat.formatTag == 0xFFFE)
                {
                    // Extensible
                    if (formatChunk.size < 40 || mWAVFormat.extraSize < 22)
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
                RefreshFormat();
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
                        mData->resize(chunk.size);
                        fin.read((char*)mData->data(), chunk.size); // Todo: stream mode
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
        if (mData->size() == 0)
        {
            return false;
        }
        
        std::ofstream fout(_fileName);
        if (fout.is_open())
        {
            fout << "RIFF";
            fout.write((char*)BinaryString(int(4 + 8 + 16 + 8 + mData->size())).data(), 4);
            fout << "WAVE";
            fout << "fmt\x20";
            fout.write((char*)BinaryString(int(sizeof(VWAVAudioFormatData) - 2)).data(), 4);
            fout.write((char*)&mWAVFormat, sizeof(VWAVAudioFormatData) - 2);
            fout << "data";
            fout.write((char*)BinaryString(int(mData->size())).data(), 4);
            fout.write((char*)mData->data(), mData->size());
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
    
    //----------------------------------------------------------------------------------------------------
    void VWAVAudio::RefreshFormat()
    {
        VAudioSampleFormat sampleFormat = VAudioSampleFormat::Unknown;
        if (mWAVFormat.formatTag == 1)
        {
            switch (mWAVFormat.bitsPerSample / 8)
            {
                case 1:
                    sampleFormat = VAudioSampleFormat::Int8;
                    break;
                case 2:
                    sampleFormat = VAudioSampleFormat::Int16;
                    break;
                case 3:
                    sampleFormat = VAudioSampleFormat::Int24;
                    break;
                case 4:
                    sampleFormat = VAudioSampleFormat::Int32;
                    break;
                default:
                    break;
            }
        }
        else if (mWAVFormat.formatTag == 3)
        {
            sampleFormat = VAudioSampleFormat::Float32;
        }
        mFormat = VAudioFormat(sampleFormat, mWAVFormat.channels, mWAVFormat.samplesPerSec, mWAVFormat.bitsPerSample);
    }
    
    //----------------------------------------------------------------------------------------------------
    void VWAVAudio::RefreshWAVFormat()
    {
        mWAVFormat.formatTag = 0;
        switch (mFormat.format)
        {
            case VAudioSampleFormat::Int8:
            case VAudioSampleFormat::Int16:
            case VAudioSampleFormat::Int24:
            case VAudioSampleFormat::Int32:
                mWAVFormat.formatTag = 1;
                break;
            case VAudioSampleFormat::Float32:
                mWAVFormat.formatTag = 3;
                break;
            default:
                break;
        }
        mWAVFormat.channels = mFormat.channels;
        mWAVFormat.samplesPerSec = mFormat.samplesPerSecond;
        mWAVFormat.bytesPerSec = mFormat.BytesPerSecond();
        mWAVFormat.blockAlign = mFormat.BlockAlign();
        mWAVFormat.bitsPerSample = mFormat.bitsPerSample;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VWAVAudioTest()
    {
        VWAVAudio audio;
        audio.ReadFromFile("Test/Data/right.wav");
        audio.WriteToFile("Test/Data/right_saved.wav");
        // auto durations = audio.DurationSeconds();
        
        return;
    }
    
}
