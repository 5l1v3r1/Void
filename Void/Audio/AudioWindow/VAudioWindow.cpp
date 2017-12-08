#include "VAudioWindow.h"
#include "../../Structure/Angle/VAngle.h"
#include <cmath>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAudioWindow
    //----------------------------------------------------------------------------------------------------
    VAudioWindow::VAudioWindow()
        :
        mType(VAudioWindowType::Unknown),
        mWeights()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VAudioWindow::VAudioWindow(const VAudioWindow& _window)
        :
        mType(_window.mType),
        mWeights(_window.mWeights)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VAudioWindow::~VAudioWindow()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VAudioWindow::Generate(VAudioWindowType _type, unsigned int _windowSize)
    {
        if (_type != VAudioWindowType::Unknown)
        {
            mType = _type;
        }
        
        if (mType != VAudioWindowType::Unknown)
        {
            switch (mType)
            {
                case VAudioWindowType::Rectangular:
                    return GenerateRectangular(_windowSize);
                case VAudioWindowType::Hamming:
                    return GenerateHamming(_windowSize);
                case VAudioWindowType::Hann:
                    return GenerateHann(_windowSize);
                case VAudioWindowType::Blackman:
                    return GenerateBlackman(_windowSize);
                default:
                    break;
            }
        }
        return false;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VAudioWindow::VAudioWindow::GenerateRectangular(unsigned int _windowSize)
    {
        mType = VAudioWindowType::Rectangular;
        mWeights = std::vector<float>(_windowSize, 0);
        for (unsigned long i = 0; i < mWeights.size(); ++i)
        {
            mWeights[i] = 1;
        }
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VAudioWindow::GenerateHamming(unsigned int _windowSize)
    {
        mType = VAudioWindowType::Hamming;
        mWeights = std::vector<float>(_windowSize, 0);
        float factor = V_ANGLE_2PI / (_windowSize - 1);
        for (unsigned long i = 0; i < mWeights.size(); ++i)
        {
            mWeights[i] = 0.53836 - 0.46164 * std::cosf(i * factor);
        }
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VAudioWindow::GenerateHann(unsigned int _windowSize)
    {
        mType = VAudioWindowType::Hann;
        mWeights = std::vector<float>(_windowSize, 0);
        float factor = V_ANGLE_2PI / (_windowSize - 1);
        for (unsigned long i = 0; i < mWeights.size(); ++i)
        {
            mWeights[i] = 0.5 * (1 - std::cosf(i * factor));
        }
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VAudioWindow::GenerateBlackman(unsigned int _windowSize, float _coefficient)
    {
        mType = VAudioWindowType::Blackman;
        mWeights = std::vector<float>(_windowSize, 0);
        float factor = V_ANGLE_2PI / (_windowSize - 1);
        for (unsigned long i = 0; i < mWeights.size(); ++i)
        {
            mWeights[i] = _coefficient - 0.5 * std::cosf(i * factor) + (0.5 - _coefficient) * std::cosf(2 * i * factor);
        }
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    unsigned long VAudioWindow::NumberOfFrames(unsigned long _samples, unsigned long _windowShift, bool _isSnipEdges)
    {
        unsigned long windowSize = mWeights.size();
        if (windowSize && _windowShift)
        {
            if (_isSnipEdges)
            {
                if (_samples < windowSize)
                {
                    return 0;
                }
                else
                {
                    return 1 + (_samples - windowSize) / _windowShift;
                }
            }
            else
            {
                return (_samples + (_windowShift / 2)) / _windowShift;
            }
        }
        return 0;
    }
    
    //----------------------------------------------------------------------------------------------------
    long VAudioWindow::FrameIndexToSampleIndex(unsigned long _windowShift, unsigned long _frameIndex, bool _isSnipEdges)
    {
        unsigned long windowSize = mWeights.size();
        if (windowSize && _windowShift)
        {
            if (_isSnipEdges)
            {
                return _windowShift * _frameIndex;
            }
            else
            {
                unsigned long middleOfStep = _windowShift * _frameIndex + _windowShift / 2;
                return middleOfStep - (long)windowSize / 2;
            }
        }
        return 0;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VAudioWindowTest()
    {
        
        return;
    }
    
}
