#include "VFunction.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // Test
    //----------------------------------------------------------------------------------------------------
    void VFunctionTest()
    {
        VFunction<int> function0;
        {
            VFunction<int> tmp1([](const std::map<std::string, VAny>& _variables)->double{ return 123.4; });
            VFunction<int> tmp2([](const std::map<std::string, VAny>& _variables)->double{ return 567.8; });
            function0 = tmp1 + tmp2;
        }
        float value0 = (float)function0.Value();
        
        VFunction<float> x([](const std::map<std::string, VAny>& _variables)->auto{ return VAnyCast<float>(_variables.find("x")->second); });
        x.Bind("x", 111.1f);
        VFunction<int> y([](const std::map<std::string, VAny>& _variables)->auto{ return VAnyCast<int>(_variables.find("y")->second); });
        auto function1 = 200 + x + y + 100;
        function1.Bind("y", 222);
        value0 = function1.Value();
        function1.Bind("x", 999.f);
        value0 = function1.Value();
        
        return;
    }
}
