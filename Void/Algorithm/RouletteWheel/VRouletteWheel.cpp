#include "VRouletteWheel.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // Test
    //----------------------------------------------------------------------------------------------------
    void VRouletteWheelTest()
    {
        VRouletteWheel<int> rouletteWheel;
        rouletteWheel.Insert(50, 1);
        rouletteWheel.Insert(30, 2);
        rouletteWheel.Insert(10, 3);
        int rwResult = 0;
        rouletteWheel.Select(-30, rwResult);
        rouletteWheel.RandomSelect(rwResult);
        rouletteWheel.Delete(10, 3);
        
        return;
    }
}
