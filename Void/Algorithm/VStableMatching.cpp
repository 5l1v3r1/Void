#include "VStableMatching.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
	// VStableMatching
	//----------------------------------------------------------------------------------------------------
	void VStableMatchingTest()
	{
		std::map<int, std::vector<int>> gentlemen;
		gentlemen[0] = { 1, 2, 3, 0 };
		gentlemen[1] = { 2, 1, 3, 0 };
		gentlemen[2] = { 1, 3, 2, 0 };
		gentlemen[3] = { 0, 2, 3, 1 };
		std::map<int, std::vector<int>> ladies;
		ladies[0] = { 1, 2, 3, 0 };
		ladies[1] = { 0, 1, 2, 3 };
		ladies[2] = { 0, 2, 1, 3 };
		ladies[3] = { 1, 2, 3, 0 };

		auto result = VStableMatching<int>::GaleShapley(gentlemen, ladies);
	}
}