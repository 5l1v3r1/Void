#include "VLogisticRegression.h"
#include <assert.h>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VLogisticRegression
    //----------------------------------------------------------------------------------------------------
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VLogisticRegressionTest()
    {
        std::vector<VLogisticRegressionSample<float>> samples;
        
        VLogisticRegression<float> AND(2);
        samples.clear();
        samples.push_back({{1.0, 1.0}, true});
        samples.push_back({{0.0, 1.0}, false});
        samples.push_back({{1.0, 0.0}, false});
        samples.push_back({{0.0, 0.0}, false});
        AND.Train(samples, 1000);
        
        VLogisticRegression<float> OR(2);
        samples.clear();
        samples.push_back({{1.0, 1.0}, true});
        samples.push_back({{0.0, 1.0}, true});
        samples.push_back({{1.0, 0.0}, true});
        samples.push_back({{0.0, 0.0}, false});
        OR.Train(samples, 1000);
        
        VLogisticRegression<float> NOT(1);
        samples.clear();
        samples.push_back({{1.0}, false});
        samples.push_back({{0.0}, true});
        NOT.Train(samples, 1000);
        
        // XOR = (A && !B) || (!A && B)
        assert(OR.Perceive({
            (float)AND.Perceive({
                1.0, (float)NOT.Perceive({1.0})
            }),
            (float)AND.Perceive({
                (float)NOT.Perceive({1.0}), 1.0
            }),
        }) < 0.5);
        assert(OR.Perceive({
            (float)AND.Perceive({
                1.0, (float)NOT.Perceive({0.0})
            }),
            (float)AND.Perceive({
                (float)NOT.Perceive({1.0}), 0.0
            }),
        }) > 0.5);
        assert(OR.Perceive({
            (float)AND.Perceive({
                0.0, (float)NOT.Perceive({1.0})
            }),
            (float)AND.Perceive({
                (float)NOT.Perceive({0.0}), 1.0
            }),
        }) > 0.5);
        assert(OR.Perceive({
            (float)AND.Perceive({
                0.0, (float)NOT.Perceive({0.0})
            }),
            (float)AND.Perceive({
                (float)NOT.Perceive({0.0}), 0.0
            }),
        }) < 0.5);
        return;
    }
    
}
