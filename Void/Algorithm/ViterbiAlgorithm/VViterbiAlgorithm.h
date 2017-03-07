#pragma once
#ifndef _V_VITERBIALGORITHM_H_
#define _V_VITERBIALGORITHM_H_

#include <vector>
#include <map>
#include <math.h>
#include <limits>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VViterbiAlgorithm
    // State: S
    // Observation: O
    // Todo: log table
    //----------------------------------------------------------------------------------------------------
    template <typename _S, typename _O>
    class VViterbiAlgorithm
    {
    public:
        //----------------------------------------------------------------------------------------------------
        inline VViterbiAlgorithm()
        {
            
        }
        
        //----------------------------------------------------------------------------------------------------
        inline VViterbiAlgorithm(const std::vector<_S>& _states, const std::vector<_O>& _observations, const std::map<_S, float>& _startProbability, const std::map<_S, std::map<_S, float>>& _transitionProbability, const std::map<_S, std::map<_O, float>>& _emissionProbability)
            :
            m_states(_states),
            m_observations(_observations),
            m_startProbability(_startProbability),
            m_transitionProbability(_transitionProbability),
            m_emissionProbability(_emissionProbability)
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        inline VViterbiAlgorithm(const VViterbiAlgorithm& _viterbi)
        {
            
        }
        
        //----------------------------------------------------------------------------------------------------
        inline virtual ~VViterbiAlgorithm()
        {
            
        }
        
        //----------------------------------------------------------------------------------------------------
        inline std::vector<_S> Calculate(const std::vector<_O>& _observations)
        {
            if (_observations.size() < 1)
            {
                return std::vector<_S>();
            }
            
            std::vector<std::map<_S, float>> probabilities;
            std::vector<std::map<_S, _S>> routes;
            // First observation
            probabilities.push_back(std::map<_S, float>());
            routes.push_back(std::map<_S, _S>());
            for (auto& state : m_states)
            {
                probabilities[0][state] = log(m_startProbability[state]) + log(m_emissionProbability[state][_observations[0]]); // P(observation | state)
                routes[0][state] = state; // useless
            }
            // Rest observations
            for (unsigned long i = 1; i < _observations.size(); ++i)
            {
                _O observation = _observations[i];
                probabilities.push_back(std::map<_S, float>());
                routes.push_back(std::map<_S, _S>());
                for (auto& state : m_states)
                {
                    probabilities[i][state] = -std::numeric_limits<float>::max();
                    for(auto& lastState : m_states)
                    {
                        float p = probabilities[i - 1][lastState] + log(m_transitionProbability[lastState][state]) + log(m_emissionProbability[state][_observations[i]]); // P(observation | lastState, state)
                        if(probabilities[i][state] < p)
                        {
                            probabilities[i][state] = p;
                            routes[i][state] = lastState;
                        }
                    }
                }
            }
            // Find the best route
            std::vector<_S> result(probabilities.size());
            float p = -std::numeric_limits<float>::max();
            for (auto& state : m_states)
            {
                if(p < probabilities.back()[state])
                {
                    p = probabilities.back()[state];
                    result.back() = state;
                }
            }
            for (long index = result.size() - 2; 0 <= index; --index)
            {
                result[index] = routes[index + 1][result[index + 1]];
            }
            
            // Debug
            // for (unsigned long i = 0; i < _observations.size(); ++i)
            // {
            //     for (auto& state : m_states)
            //     {
            //         probabilities[i][state] = exp(probabilities[i][state]);
            //     }
            // }
            
            
            return result;
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::vector<_S> m_states;
        std::vector<_O> m_observations;
        std::map<_S, float> m_startProbability;
        std::map<_S, std::map<_S, float>> m_transitionProbability;
        std::map<_S, std::map<_O, float>> m_emissionProbability;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VViterbiAlgorithmTest();
}

#endif
