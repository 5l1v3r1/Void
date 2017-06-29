#pragma once
#pragma once
#ifndef _V_LEVENSHTEIN_H_
#define _V_LEVENSHTEIN_H_

#include <vector>
#include <utility>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VLevenshteinStepper
    //----------------------------------------------------------------------------------------------------
    enum class VLevenshteinStepper
    {
        None = 0,
        Matching,
        Deletion,
        Insertion,
        Subtraction,
    };
    
	// VLevenshtein
	// Edit Distance
	//----------------------------------------------------------------------------------------------------
    template<typename _T>
	class VLevenshtein
	{
    protected:
        //----------------------------------------------------------------------------------------------------
        struct Route
        {
        public:
            //----------------------------------------------------------------------------------------------------
            Route()
                :
                distance(0),
                stepper(VLevenshteinStepper::None)
            {
            }
            
            //----------------------------------------------------------------------------------------------------
            Route(unsigned long _distance, VLevenshteinStepper _stepper)
                :
                distance(_distance),
                stepper(_stepper)
            {
            }
            
            //----------------------------------------------------------------------------------------------------
            Route(const Route& _route)
                :
                distance(_route.distance),
                stepper(_route.stepper)
            {
            }
            
        public:
            //----------------------------------------------------------------------------------------------------
            unsigned long distance;
            VLevenshteinStepper stepper;
        };
        
	public:
		//----------------------------------------------------------------------------------------------------
		static unsigned long Distance(const _T& _from, const _T& _to)
        {
            VLevenshtein levenshtein(_from, _to);
            return levenshtein.Distance();
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        VLevenshtein(const _T& _from, const _T& _to)
        {
            Calculate(_from, _to);
        }
        
        //----------------------------------------------------------------------------------------------------
        unsigned long Distance()
        {
            return mMatrix.back().back().distance;
        }
        
        //----------------------------------------------------------------------------------------------------
        

	protected:
        /*
                to
              +-----+
              |     |
         from |     |
              |     |
              +-----+
        */
		//----------------------------------------------------------------------------------------------------
        void Calculate(const _T& _from, const _T& _to)
        {
            unsigned long rows = _from.size();
            unsigned long columns = _to.size();
            
            mMatrix.resize(rows + 1, std::vector<Route>(columns + 1));
            mMatrix[0][0] = Route(0, VLevenshteinStepper::None);
            for (int j = 1; j <= columns; ++j)
            {
                mMatrix[0][j] = Route(j, VLevenshteinStepper::Insertion);
            }
            for (int i = 1; i <= rows; ++i)
            {
                mMatrix[i][0] = Route(i, VLevenshteinStepper::Deletion);
                for (int j = 1; j <= columns; ++j)
                {
                    if (_from[i - 1] == _to[j - 1])
                    {
                        mMatrix[i][j] = Route(mMatrix[i - 1][j - 1].distance, VLevenshteinStepper::Matching);
                    }
                    else
                    {
                        unsigned long deletion = mMatrix[i - 1][j].distance + 1;
                        unsigned long insertion = mMatrix[i][j - 1].distance + 1;
                        unsigned long subtraction = mMatrix[i - 1][j - 1].distance + 1;
                        if (deletion < insertion)
                        {
                            if (deletion < subtraction)
                            {
                                mMatrix[i][j] = Route(deletion, VLevenshteinStepper::Deletion);
                            }
                            else
                            {
                                mMatrix[i][j] = Route(subtraction, VLevenshteinStepper::Subtraction);
                            }
                        }
                        else
                        {
                            if (insertion < subtraction)
                            {
                                mMatrix[i][j] = Route(insertion, VLevenshteinStepper::Insertion);
                            } else
                            {
                                mMatrix[i][j] = Route(subtraction, VLevenshteinStepper::Subtraction);
                            }
                        }
                    }
                }
            }
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::vector<std::vector<Route>> mMatrix;
        
	};

	// Test
	//----------------------------------------------------------------------------------------------------
	void VLevenshteinTest();
}

#endif
