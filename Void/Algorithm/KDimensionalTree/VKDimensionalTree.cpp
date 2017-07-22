#include "VKDimensionalTree.h"
#include "../../Utility/Random/VRandom.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VKDimensionalTree
    //----------------------------------------------------------------------------------------------------

    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VKDimensionalTreeTest()
    {
        VRandom random;
        VKDimensionalTree<std::vector<float>> tree;
        
        // 3-dimensional
        std::vector<std::vector<float>> points;
        for (int i = 0; i < 10000; ++i)
        {
            points.push_back({random.Rand(-5.f, 5.f), random.Rand(-5.f, 5.f), random.Rand(-5.f, 5.f)});
        }
        tree.BuildTree(points, 3);
        std::vector<float> target = {0.f, 0.f, 0.f};
        auto nearest = tree.Search(target, 2);
        // Brute force
        VMaxHeap<double, std::vector<float>> heap;
        for (auto& point : points)
        {
            double distance = VDistance<std::vector<float>, VDistanceType::Euclidean>::Calculate(point, target);
            if (heap.Size() < 2)
            {
                heap.Insert(distance, point);
            }
            else if (distance < heap.FrontKey())
            {
                heap.Insert(distance, point);
                heap.PopFront();
            }
        }
        
        tree.Clear();
        
        return;
    }
    
}
