#include "VPerceptron.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VPerceptron
    //----------------------------------------------------------------------------------------------------
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VPerceptronTest()
    {
        VPerceptron<float> perceptron(3);
        
        std::vector<VPerceptronSample<float>> samples;
        samples.push_back({{1.0, 1.0, 5.0}, true});
        samples.push_back({{0.0, 1.0, 0.0}, false});
        samples.push_back({{1.0, 0.0, 0.0}, false});
        samples.push_back({{0.0, 0.0, 1.0}, false});
        perceptron.Train(samples, 20);
        
        perceptron.Reset(2);
        // samples.push_back({{1.0, 1.0}, true});
        samples.push_back({{1.0, 0.0}, false});
        samples.push_back({{0.0, 1.0}, false});
        samples.push_back({{0.4, 0.4}, true});
        perceptron.Train(samples, 100);
        
        return;
    }
    
}
