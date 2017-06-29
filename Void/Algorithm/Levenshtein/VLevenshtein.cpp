#include "VLevenshtein.h"
#include <vector>
#include <algorithm>

//----------------------------------------------------------------------------------------------------
namespace Void
{
	// VLevenshtein
	//----------------------------------------------------------------------------------------------------
	unsigned long VLevenshtein::Distance(const std::string& _first, const std::string& _second)
	{
		unsigned long rows = _first.size();
		unsigned long columns = _second.size();
		if (rows == 0)
		{
			return columns;
		} 
		else if (columns == 0)
		{
			return rows;
		}
		else if (_first == _second)
		{
			return 0;
		}

		std::vector<std::vector<unsigned>> table(rows + 1, std::vector<unsigned>(columns + 1));
		for (int j = 1; j < columns + 1; ++j)
		{
			table[0][j] = j;
		}
		for (int i = 1; i < rows + 1; ++i)
		{
			table[i][0] = i;
			for (int j = 1; j < columns + 1; ++j)
			{
				unsigned temp = std::min(table[i - 1][j], table[i][j - 1]) + 1;
				if (_first[i - 1] == _second[j - 1])
				{
					table[i][j] = std::min(temp, table[i - 1][j - 1]);
				}
				else
				{
					table[i][j] = std::min(temp, table[i - 1][j - 1] + 1);
				}
			}
		}
		return table[rows][columns];
	}

	// Test
	//----------------------------------------------------------------------------------------------------
	void VLevenshteinTest()
	{
		auto result = VLevenshtein::Distance("", "");
		result = VLevenshtein::Distance("ho", "hello");

		return;
	}

}
