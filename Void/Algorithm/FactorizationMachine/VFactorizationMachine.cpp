#include "VFactorizationMachine.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VFactorizationMachine
    //----------------------------------------------------------------------------------------------------
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VFactorizationMachineTest()
    {
        VFactorizationMachine<double, VFactorizationMachineType::Regression> machine(3, 10);
        std::vector<VFactorizationMachineSample<double>> samples;
        samples.clear();
        samples.push_back({{{0, 1.0}, {1, 2.0}, {2, 3.0}}, 1});
        samples.push_back({{{0, 1.0}, {1, 4.0}, {2, 2.0}}, 2});
        samples.push_back({{{0, 1.0}, {1, 6.0}, {2, 1.0}}, 3});
        machine.Train(samples, 100);
        
        double result = 0;
        machine.Perceive({{0, 1.0}, {1, 7.0}, {2, 0.0}}, result);
        return;
    }
    
}
