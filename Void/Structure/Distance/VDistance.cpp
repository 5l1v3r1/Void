#include "VDistance.h"
#include "../DynamicMatrix/VDynamicMatrix.h"
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VDistance
    //----------------------------------------------------------------------------------------------------
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VDistanceTest()
    {
        auto distance = VDistance<std::vector<float>, VDistanceType::Cityblock>::Calculate({1, 2, 3}, {1, 2, 3});
        distance = VDistance<std::vector<float>, VDistanceType::Cityblock>::Calculate({3, 2, 1}, {1, 2, 3});
        distance = VDistance<std::vector<float>, VDistanceType::BrayCurtis>::Calculate({3, 2, 1}, {1, 2, 3});
        distance = VDistance<std::vector<float>, VDistanceType::Cosine>::Calculate({3, 2, 1}, {1, 2, 3});
        distance = VDistance<VDynamicMatrix<float>, VDistanceType::Cosine>::Calculate(std::vector<float>({3, 2, 1}), std::vector<float>({1, 2, 3}));
        distance = VDistance<std::vector<float>, VDistanceType::Euclidean>::Calculate({3, 2, 1}, {1, 2, 3});
        distance = VDistance<VDynamicMatrix<float>, VDistanceType::Euclidean>::Calculate(std::vector<float>({3, 2, 1}), std::vector<float>({1, 2, 3}));
        
        return;
    }
    
}
