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
	//----------------------------------------------------------------------------------------------------
	template <typename _T>
	class VStableMatching
	{
    protected:
        //----------------------------------------------------------------------------------------------------
        struct Mind
        {
        public:
            //----------------------------------------------------------------------------------------------------
            Mind()
                :
                preferences(),
                preferRank(-1)
            {
            }
            
            //----------------------------------------------------------------------------------------------------
            Mind(std::vector<_T>& _preferences)
                :
                preferences(_preferences),
                preferRank(-1)
            {
            }
            
            //----------------------------------------------------------------------------------------------------
            int TargetRank(const _T& _target)
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
            
        public:
            //----------------------------------------------------------------------------------------------------
            std::vector<_T> preferences;
            int preferRank;
        };
        
	public:
		//----------------------------------------------------------------------------------------------------
		static std::map<_T, _T> GaleShapley(std::map<_T, std::vector<_T>>& _gentlemen, std::map<_T, std::vector<_T>>& _ladies)
		{
			std::map<_T, _T> result;
			std::list<_T> leftover; // Why do we use list? Lovelorn man may immerse in the grief...
			std::map<_T, Mind> gentlemen;
			std::map<_T, Mind> ladies;

			// Init leftover, gentlemen, ladies
			for (typename std::map<_T, std::vector<_T>>::iterator it = _gentlemen.begin(); it != _gentlemen.end(); ++it)
			{
				leftover.push_back(it->first);
				gentlemen.insert(std::pair<_T, Mind>(it->first, Mind(it->second)));
			}
			for (typename std::map<_T, std::vector<_T>>::iterator it = _ladies.begin(); it != _ladies.end(); ++it)
			{
				ladies.insert(std::pair<_T, Mind>(it->first, Mind(it->second)));
			}

			// Fight
			while (!leftover.empty())
			{
				_T man = leftover.front();
				Mind &manMind = gentlemen[man];
				++manMind.preferRank;

				_T &lady = manMind.preferences[manMind.preferRank];
				Mind &ladyMind = ladies[lady];

				int rankInHerMind = ladyMind.TargetRank(man);
				if (ladyMind.preferRank == -1) // Free
				{
					leftover.pop_front();
					ladyMind.preferRank = rankInHerMind;
					result[man] = lady;
				}
				else if (rankInHerMind < ladyMind.preferRank) // Green hat...
				{
					leftover.pop_front();
					leftover.push_back(ladyMind.preferences[ladyMind.preferRank]);
					ladyMind.preferRank = rankInHerMind;
					result[man] = lady;
				}
			}

			return result;
		}
	};

    // Test
	//----------------------------------------------------------------------------------------------------
	void VStableMatchingTest();
}

#endif
