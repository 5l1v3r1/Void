#pragma once
#pragma once
#ifndef _V_LEVENSHTEIN_H_
#define _V_LEVENSHTEIN_H_

#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
	// VLevenshtein
	// Edit Distance
	//----------------------------------------------------------------------------------------------------
	class VLevenshtein
	{
	public:
		//----------------------------------------------------------------------------------------------------
		static unsigned Distance(const std::string& _first, const std::string& _second);

	protected:
		//----------------------------------------------------------------------------------------------------
		
	};

	// Test
	//----------------------------------------------------------------------------------------------------
	void VLevenshteinTest();
}

#endif
