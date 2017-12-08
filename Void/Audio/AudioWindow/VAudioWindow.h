#pragma once
#ifndef _V_AUDIOWINDOW_H_
#define _V_AUDIOWINDOW_H_

#include "../AudioBase/AudioFormat/VAudioFormat.h"
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAudioWindowType
    //----------------------------------------------------------------------------------------------------
    // Rectangular | w(n) = const
    //----------------------------------------------------------------------------------------------------
    //     Hamming | w(n) = 0.53836 - 0.46164 * cos(2 * Pi * n / (N - 1))
    //----------------------------------------------------------------------------------------------------
    //        Hann | w(n) = 0.5 * (1 - cos(2 * Pi * n / (N - 1)))
    //----------------------------------------------------------------------------------------------------
    //    Blackman | w(n) = coefficient - 0.5 * cos(2 * Pi * n / (N - 1)) + (0.5 - coefficient) * cos(4 * Pi * n / (N - 1))
    //----------------------------------------------------------------------------------------------------
    enum class VAudioWindowType
    {
        Unknown = 0,
        Rectangular,
        Hamming,
        Hann,
        Blackman
    };
    
    // VAudioWindow
    //----------------------------------------------------------------------------------------------------
    class VAudioWindow
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VAudioWindow();
        VAudioWindow(const VAudioWindow& _window);
        virtual ~VAudioWindow();
        
    public:
        //----------------------------------------------------------------------------------------------------
        bool Generate(VAudioWindowType _type=VAudioWindowType::Unknown, unsigned int _windowSize=0);
        bool GenerateRectangular(unsigned int _windowSize);
        bool GenerateHamming(unsigned int _windowSize);
        bool GenerateHann(unsigned int _windowSize);
        bool GenerateBlackman(unsigned int _windowSize, float _coefficient=0.42);
        
        //----------------------------------------------------------------------------------------------------
        unsigned long NumberOfFrames(unsigned long _samples, unsigned long _windowShift, bool _isSnipEdges=true);
        long FrameIndexToSampleIndex(unsigned long _windowShift, unsigned long _frameIndex, bool _isSnipEdges=true);
        
        //----------------------------------------------------------------------------------------------------
        // Todo: channels
        //----------------------------------------------------------------------------------------------------
        //                | Extract
        //----------------------------------------------------------------------------------------------------
        //           Data |  0123456789
        //                |  ~~~~~~~~~~
        //----------------------------------------------------------------------------------------------------
        //          Shift |  ~~~
        //       (Step 3) |     ~~~
        //                |        ...
        //----------------------------------------------------------------------------------------------------
        //     Snip Edges |  ~~~~~ >> shift
        //     (Window 5) |  01234
        //----------------------------------------------------------------------------------------------------
        // Not Snip Edges | ~~~~~ >> shift
        //     (Window 5) | x0123
        //----------------------------------------------------------------------------------------------------
        template<VAudioSampleFormat _SampleFormat>
        std::vector<float> ExtractWindow(VAudioFormattedData<_SampleFormat>& _formattedData, unsigned long _windowShift, unsigned long _frameIndex, bool _isSnipEdges=true)
        {
            unsigned long blockCount = _formattedData.BlockCount();
            unsigned long numberOfFrames = NumberOfFrames(blockCount, _windowShift, _isSnipEdges);
            if (_frameIndex < numberOfFrames)
            {
                unsigned long windowSize = mWeights.size();
                std::vector<float> window(windowSize, 0);
                long sampleStart = FrameIndexToSampleIndex(_windowShift, _frameIndex, _isSnipEdges);
                long sampleEnd = sampleStart + windowSize;
                if (0 <= sampleStart && sampleEnd <= blockCount) // Center
                {
                    for (unsigned long i = 0; i < windowSize; ++i)
                    {
                        window[i] = _formattedData[sampleStart + i];
                    }
                }
                else // Edges
                {
                    for (unsigned long i = 0; i < windowSize; ++i)
                    {
                        long sampleIndex = sampleStart + i;
                        if (0 <= sampleIndex && sampleIndex < blockCount)
                        {
                            window[i] = _formattedData[sampleIndex];
                        }
                        else
                        {
                            window[i] = 0;
                        }
                    }
                }
                ProcessWindow<_SampleFormat>(window);
                return window;
            }
            return std::vector<float>();
        }
        
        // Todo: Pre-emphasis
        //----------------------------------------------------------------------------------------------------
        template<VAudioSampleFormat _SampleFormat>
        void ProcessWindow(std::vector<float> &_window, float _dither=0.f, bool _isRemoveDCOffset=true)
        {
            unsigned long windowSize = mWeights.size();
            if (_window.size() == windowSize)
            {
                float offset = 0;
                if (_isRemoveDCOffset)
                {
                    for (unsigned long i = 0; i < windowSize; ++i)
                    {
                        offset += _window[i];
                    }
                    offset /= windowSize;
                }
                for (unsigned long i = 0; i < windowSize; ++i)
                {
                    _window[i] -= offset;
                    _window[i] *= mWeights[i];
                }
            }
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        
    protected:
        //----------------------------------------------------------------------------------------------------
        VAudioWindowType mType;
        std::vector<float> mWeights;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VAudioWindowTest();
}

#endif
