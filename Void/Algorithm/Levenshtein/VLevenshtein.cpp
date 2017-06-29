#include "VLevenshtein.h"
#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
	// Test
	//----------------------------------------------------------------------------------------------------
	void VLevenshteinTest()
	{
        auto result = VLevenshtein<std::string>::Distance("", "");
		result = VLevenshtein<std::string>::Distance("ho", "hello");

		return;
	}

}
