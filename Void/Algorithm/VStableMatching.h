#pragma once
#ifndef _V_STABLEMATCHING_H_
#define _V_STABLEMATCHING_H_

#include <list>
#include <vector>
#include <map>
#include <utility>

//----------------------------------------------------------------------------------------------------
namespace Void
{
	// VStableMatching
	// Propose-And-Reject (Gale-Shapley)
	// gentlemen rank¡ý
	// ladies rank¡ü
	//----------------------------------------------------------------------------------------------------
	template <typename _T>
	class VStableMatching
	{
	public:
		//----------------------------------------------------------------------------------------------------
		static std::map<_T, _T> GaleShapley(std::map<_T, std::vector<_T>>& _gentlemen, std::map<_T, std::vector<_T>>& _ladies)
		{
			std::map<_T, _T> result;
			std::list<_T> leftover; // why list? lovelorn man may immerse in the grief
			std::map<_T, Mind> gentlemen;
			std::map<_T, Mind> ladies;

			// init leftover, gentlemen, ladies
			for (std::map<_T, std::vector<_T>>::iterator it = _gentlemen.begin(); it != _gentlemen.end(); ++it)
			{
				leftover.push_back(it->first);
				gentlemen.insert(std::pair<_T, Mind>(it->first, Mind(it->second)));
			}
			for (std::map<_T, std::vector<_T>>::iterator it = _ladies.begin(); it != _ladies.end(); ++it)
			{
				ladies.insert(std::pair<_T, Mind>(it->first, Mind(it->second)));
			}

			// fight
			while (!leftover.empty())
			{
				_T man = leftover.front();
				Mind &manMind = gentlemen[man];
				++manMind.preferRank;

				_T &lady = manMind.preferences[manMind.preferRank];
				Mind &ladyMind = ladies[lady];

				int rankInHerMind = ladyMind.GetTargetRank(man);
				if (ladyMind.preferRank == -1) // free
				{
					leftover.pop_front();
					ladyMind.preferRank = rankInHerMind;
					result[man] = lady;
				}
				else if (rankInHerMind < ladyMind.preferRank) // lady rank¡ü
				{
					leftover.pop_front();
					leftover.push_back(ladyMind.preferences[ladyMind.preferRank]);
					ladyMind.preferRank = rankInHerMind;
					result[man] = lady;
				}
			}

			return result;
		}

	protected:
		//----------------------------------------------------------------------------------------------------
		struct Mind
		{
		public:
			std::vector<_T> &preferences;
			int preferRank;

			Mind()
				:
				preferences(std::vector<_T>()),
				preferRank(-1)
			{
				// Error
			}

			Mind(std::vector<_T>& _preferences)
				:
				preferences(_preferences),
				preferRank(-1)
			{
			}

			int GetTargetRank(const _T& _target)
			{
				for (unsigned int i = 0; i < preferences.size(); ++i)
				{
					if (preferences[i] == _target)
					{
						return i;
					}
				}
				return -1;
			}
		};
	};

	//----------------------------------------------------------------------------------------------------
	void VStableMatchingTest();
}

#endif