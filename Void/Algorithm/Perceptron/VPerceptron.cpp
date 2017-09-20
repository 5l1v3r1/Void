#include "VPerceptron.h"
#include <assert.h>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VPerceptron
    //----------------------------------------------------------------------------------------------------
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VPerceptronTest()
    {
        std::vector<VPerceptronSample<float>> samples;
        
        VPerceptron<float> AND(2);
        samples.clear();
        samples.push_back({{1.0, 1.0}, true});
        samples.push_back({{0.0, 1.0}, false});
        samples.push_back({{1.0, 0.0}, false});
        samples.push_back({{0.0, 0.0}, false});
        AND.Train(samples, 100);
        
        VPerceptron<float> OR(2);
        samples.clear();
        samples.push_back({{1.0, 1.0}, true});
        samples.push_back({{0.0, 1.0}, true});
        samples.push_back({{1.0, 0.0}, true});
        samples.push_back({{0.0, 0.0}, false});
        OR.Train(samples, 100);
        
        VPerceptron<float> NOT(1);
        samples.clear();
        samples.push_back({{1.0}, false});
        samples.push_back({{0.0}, true});
        NOT.Train(samples, 100);
        
        // XOR = (A && !B) || (!A && B)
        assert(OR.Perceive({
            (float)AND.Perceive({
                1.0, (float)NOT.Perceive({1.0})
            }),
            (float)AND.Perceive({
                (float)NOT.Perceive({1.0}), 1.0
            }),
        }) == false);
        assert(OR.Perceive({
            (float)AND.Perceive({
                1.0, (float)NOT.Perceive({0.0})
            }),
            (float)AND.Perceive({
                (float)NOT.Perceive({1.0}), 0.0
            }),
        }) == true);
        assert(OR.Perceive({
            (float)AND.Perceive({
                0.0, (float)NOT.Perceive({1.0})
            }),
            (float)AND.Perceive({
                (float)NOT.Perceive({0.0}), 1.0
            }),
        }) == true);
        assert(OR.Perceive({
            (float)AND.Perceive({
                0.0, (float)NOT.Perceive({0.0})
            }),
            (float)AND.Perceive({
                (float)NOT.Perceive({0.0}), 0.0
            }),
        }) == false);
        return;
    }
    
}
