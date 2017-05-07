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
            VFunction<int> function1([](const std::map<std::string, VAny>& _variables)->double{ return 123.4; });
            VFunction<int> function2([](const std::map<std::string, VAny>& _variables)->double{ return 567.8; });
            function0 = function1 + function2;
        }
        auto value0 = function0.Value();
        
//        {
//            VFunction<int> function1([](const std::map<std::string, VAny>& _variables)->double{ return _variables.find(0)->second; });
//            VFunction<int> function2([](const std::map<std::string, VAny>& _variables)->double{ return _variables.find(1)->second; });
//            function0 = function1 + function2;
//        }
//        function0.Bind(0, 111.1);
//        function0.Bind(1, 222.2);
//        value0 = function0.Value();
//        
//        {
//            VFunction<int> function1([](const std::map<std::string, VAny>& _variables)->double{ return _variables.find(0)->second; });
//            VFunction<int> function2([](const std::map<std::string, VAny>& _variables)->double{ return _variables.find(1)->second; });
//            function0 = function1 + function2;
//        }
//        function0.Bind(0, 100);
//        function0.Bind(1, 200);
//        value0 = function0.Value();
        
        return;
    }
}
