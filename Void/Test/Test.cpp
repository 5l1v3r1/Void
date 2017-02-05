#if true
#include "../Void.h"

//----------------------------------------------------------------------------------------------------
int main(int _argc, char** _argv)
{
    //VWindowTest();
	VStableMatchingTest();
    VImageTest();
    
    float array[5] = {1, 2, 3, 4, 5};
    VVector<float, 3> test(array, 1);
    test.x = 5;
    VVector<float, 3> test2(test);
    test[1] = 5;
    
    VColor color(0.5, 0.1, 0.2, 5);
    color.x = 5;
    color = color + color;
    float length = color.Length();
    ++length;
    
	return 0;
}
#endif
