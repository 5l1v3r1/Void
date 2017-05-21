#include "VPascalTriangle.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VPascalTriangle
    //----------------------------------------------------------------------------------------------------
    std::vector<std::vector<unsigned long long>> VPascalTriangle::Generate(unsigned _n)
    {
        std::vector<std::vector<unsigned long long>> triangle;
        triangle.reserve(_n);
        if (_n)
        {
            triangle.push_back(std::vector<unsigned long long>(1, 1));
            while (--_n)
            {
                std::vector<unsigned long long>& lastRow = triangle.back();
                triangle.push_back(std::vector<unsigned long long>(lastRow.size() + 1, 1));
                std::vector<unsigned long long>& currentRow = triangle.back();
                for (unsigned int j = 1; j < lastRow.size(); ++j)
                {
                    currentRow[j] = lastRow[j - 1] + lastRow[j];
                }
            }
        }
        return triangle;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VPascalTriangleTest()
    {
        auto result = VPascalTriangle::Generate(2);
        result = VPascalTriangle::Generate(20);
        result = VPascalTriangle::Generate(32);
        result = VPascalTriangle::Generate(61);
        
        return;
    }
    
}
