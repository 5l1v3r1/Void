#include "VAny.h"
#include "../../Utility/Logger/VLogger.h"
#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // Test
    //----------------------------------------------------------------------------------------------------
    void VAnyTest()
    {
        VAny anyValue(10);
        VAny anyValue1(std::string("123"));
        VAny anyValue2 = 'a';
        std::vector<VAny> anyVector;
        
        VAnyCast<int>(anyValue);
        anyVector.push_back(123);
        anyVector.push_back(anyValue1);
        anyVector.push_back(1.5f);
        anyVector.push_back(anyValue2);
        anyValue2.Type().name();
        
        return;
    }
}
