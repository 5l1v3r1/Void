#include "VAudioResample.h"
#include "../../Utility/Math/VMath.h"
#include "../../Structure/Angle/VAngle.h"
#include "../AudioFile/WAVAudio/VWAVAudio.h"
#include <cmath>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAudioResample
    //----------------------------------------------------------------------------------------------------
    //           | base samples | input samples | ouput samples | full samples |
    // frequency |          GCD |               |               |          LCM |
    //           |              |               |               |              |
    //----------------------------------------------------------------------------------------------------
    VAudioBase VAudioResample::Resample(VAudioBase const* _source, const VAudioFormat& _outputFormat)
    {
        VAudioFormat inputFormat = _source->Format();
        VAudioBase outputAudio(_outputFormat);
        // float durations = _source->DurationSeconds();
        
        // Calculate weights (Hanning window)
        int zeros = 5;
        double lowpassFrequency = std::min(inputFormat.samplesPerSecond, _outputFormat.samplesPerSecond) * 0.5 * 0.99;
        double windowHalfWidth = zeros / (lowpassFrequency * 2.0);
        int baseFrequency = VMath::GreatestCommonDivisor(inputFormat.samplesPerSecond, _outputFormat.samplesPerSecond);
        int inputBaseFrequency = inputFormat.samplesPerSecond / baseFrequency;
        int outputBaseFrequency = _outputFormat.samplesPerSecond / baseFrequency;
        std::vector<int> indices(outputBaseFrequency);
        std::vector<std::vector<double>> weights(outputBaseFrequency);
        for (int i = 0; i < outputBaseFrequency; ++i)
        {
            double outputTime = i / (double)_outputFormat.samplesPerSecond;
            double minOutputTime = outputTime - windowHalfWidth;
            double maxOutputTime = outputTime + windowHalfWidth;
            int minInputIndex = std::ceil(minOutputTime * inputFormat.samplesPerSecond);
            int maxInputIndex = std::floor(maxOutputTime * inputFormat.samplesPerSecond);
            int inputIntervalCount = maxInputIndex - minInputIndex + 1;
            indices[i] = minInputIndex;
            weights[i].resize(inputIntervalCount);
            for (int j = 0; j < inputIntervalCount; ++j)
            {
                double inputTime = (minInputIndex + j) / (double)inputFormat.samplesPerSecond;
                double deltaTime = inputTime - outputTime;
                weights[i][j] = VAudioResample::HanningWindowFilter(deltaTime, zeros, lowpassFrequency) / (double)inputFormat.samplesPerSecond;
            }
        }
        
        // Calculate output sample count (InputSampleCount / InputRate * OutputRate)
        int fullFrequency = VMath::LeastCommonMultiple(inputFormat.samplesPerSecond, _outputFormat.samplesPerSecond);
        int inputFullPeriod = fullFrequency / inputFormat.samplesPerSecond;
        int outputFullPeriod = fullFrequency / _outputFormat.samplesPerSecond;
        unsigned long fullSampleCount = _source->BlockCount() * inputFullPeriod;
        unsigned long outputSampleCount = fullSampleCount / outputFullPeriod;
        if (outputSampleCount * outputFullPeriod != fullSampleCount)
        {
            ++outputSampleCount;
        }
        
        // Process (Todo: int16_t)
        VAudioFormattedDataCore<int16_t> formattedInputData;
        formattedInputData.Initialize((char*)_source->Samples()->data(), 0, inputFormat.BlockAlign(), _source->BlockCount());
        outputAudio.Samples()->resize(outputSampleCount * outputAudio.Format().BlockAlign(), 0);
        VAudioFormattedDataCore<int16_t> formattedOuputData;
        formattedOuputData.Initialize(outputAudio.Samples()->data(), 0, outputAudio.Format().BlockAlign(), outputAudio.BlockCount());
        for (unsigned long outputIndex = 0; outputIndex < outputSampleCount; ++outputIndex)
        {
            unsigned long baseIndex = outputIndex / outputBaseFrequency;
            unsigned long remainder = outputIndex - baseIndex * outputBaseFrequency;
            long inputIndex = baseIndex * inputBaseFrequency + indices[remainder];
            const std::vector<double>& weightArray = weights[remainder];
            if (0 <= inputIndex && inputIndex + weightArray.size() <= _source->BlockCount()) // Center
            {
                for (unsigned long weightIndex = 0; weightIndex < weightArray.size(); ++weightIndex)
                {
                    formattedOuputData[outputIndex] += weightArray[weightIndex] * formattedInputData[inputIndex + weightIndex];
                }
            }
            else // Edges
            {
                for (unsigned long weightIndex = 0; weightIndex < weightArray.size(); ++weightIndex)
                {
                    const int16_t *inputSample = formattedInputData.Sample(inputIndex + weightIndex);
                    if (inputSample)
                    {
                        formattedOuputData[outputIndex] += weightArray[weightIndex] * (*inputSample);
                    }
                }
            }
        }
        
        return outputAudio;
    }
    
    // window(n) = 1 / 2 * (1 + cos(2 * Pi * n / (N - 1)))
    //           = sin(Pi * n / (N - 1))^2
    //----------------------------------------------------------------------------------------------------
    double VAudioResample::HanningWindowFilter(double _t, int _zeros, double _lowpassFrequency)
    {
        // Filter
        double filter = 0;
        if (_t)
        {
            filter = std::sin(V_ANGLE_2PI * _lowpassFrequency * _t) / (V_ANGLE_PI * _t);
        }
        else
        {
            filter = 2 * _lowpassFrequency;
        }
        // Window
        double window = 0;
        double windowHalfWidth = _zeros / (_lowpassFrequency * 2.0);
        if (-windowHalfWidth < _t && _t < windowHalfWidth)
        {
            window = 0.5 * (1 + std::cos(V_ANGLE_2PI * _t * _lowpassFrequency / _zeros));
        }
        // Result
        return filter * window;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VAudioResampleTest()
    {
        VWAVAudio audio;
        audio.ReadFromFile("Test/Data/right.wav");
        VAudioFormat outputFormat(VAudioSampleFormat::Int16, 1, 16000, 16); // Todo: channel && width
        VWAVAudio newAudio(VAudioResample::Resample(&audio, outputFormat));
        newAudio.WriteToFile("Test/Data/right_resampled.wav");
        return;
    }
    
}
