#pragma once
#ifndef _V_RANDOM_H_
#define _V_RANDOM_H_

#include <random>
#include <vector>
#include <map>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VRandom
    //----------------------------------------------------------------------------------------------------
    //        |     Single |           Multiple |      Multiple & Unique |
    //----------------------------------------------------------------------------------------------------
    // Linear |       Rand |       MultipleRand |     MultipleUniqueRand |
    //        |   RealRand |   MultipleRealRand | MultipleUniqueRealRand |
    //----------------------------------------------------------------------------------------------------
    // Normal | NormalRand | NormalMultipleRand |                        |
    //----------------------------------------------------------------------------------------------------
    class VRandom
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VRandom();
        VRandom(const VRandom& _random);
        ~VRandom();
        
        //----------------------------------------------------------------------------------------------------
        template<typename _T>
        _T Rand(_T _min, _T _max)
        {
            std::uniform_int_distribution<_T> distribution(_min, _max);
            return distribution(mEngine);
        }
        
        //----------------------------------------------------------------------------------------------------
        template<typename _T>
        _T RealRand(_T _min, _T _max)
        {
            std::uniform_real_distribution<_T> distribution(_min, _max);
            return distribution(mEngine);
        }
        
        //----------------------------------------------------------------------------------------------------
        template<typename _T=int>
        std::vector<_T> MultipleRand(unsigned long _count, _T _min, _T _max)
        {
            std::vector<_T> result;
            result.reserve(_count);
            std::uniform_int_distribution<_T> distribution(_min, _max);
            for (unsigned long i = 0; i < _count; ++i)
            {
                result.push_back(distribution(mEngine));
            }
            return result;
        }
        
        //----------------------------------------------------------------------------------------------------
        template<typename _T=float>
        std::vector<_T> MultipleRealRand(unsigned long _count, _T _min, _T _max)
        {
            std::vector<_T> result;
            result.reserve(_count);
            std::uniform_real_distribution<_T> distribution(_min, _max);
            for (unsigned long i = 0; i < _count; ++i)
            {
                result.push_back(distribution(mEngine));
            }
            return result;
        }
        
        // Optimize: 1 / 2 reverse
        //----------------------------------------------------------------------------------------------------
        template<typename _T>
        std::vector<_T> MultipleUniqueRand(unsigned int _count, _T _min, _T _max)
        {
            if (_max - _min + 1 < _count)
            {
                _count = _max - _min + 1;
            }
            
            std::vector<_T> result;
            result.reserve(_count);
            std::map<_T, _T> replaceTable;
            for (unsigned int i = 0; i < _count; ++i)
            {
                std::uniform_int_distribution<_T> distribution(_min, _max - i);
                int rand = distribution(mEngine);
                // find real rand
                typename std::map<_T, _T>::iterator it = replaceTable.find(rand);
                it == replaceTable.end() ? result.push_back(rand) : result.push_back(it->second);
                // replace rand
                it = replaceTable.find(_max - i);
                it == replaceTable.end() ? replaceTable[rand] = _max - i : replaceTable[rand] = it->second;
            }
            return result;
        }
        
        //----------------------------------------------------------------------------------------------------
        template<typename _T>
        std::vector<_T> MultipleUniqueRealRand(unsigned int _count, _T _min, _T _max)
        {
            if (_max - _min + 1 < _count)
            {
                _count = _max - _min + 1;
            }
            
            std::vector<_T> result;
            result.reserve(_count);
            std::map<_T, _T> replaceTable;
            for (unsigned int i = 0; i < _count; ++i)
            {
                std::uniform_real_distribution<_T> distribution(_min, _max - i);
                int rand = distribution(mEngine);
                // find real rand
                typename std::map<_T, _T>::iterator it = replaceTable.find(rand);
                it == replaceTable.end() ? result.push_back(rand) : result.push_back(it->second);
                // replace rand
                it = replaceTable.find(_max - i);
                it == replaceTable.end() ? replaceTable[rand] = _max - i : replaceTable[rand] = it->second;
            }
            return result;
        }
        
        //----------------------------------------------------------------------------------------------------
        template<typename _T>
        _T NormalRand(_T _mean, _T _stddev)
        {
            std::normal_distribution<_T> distribution(_mean, _stddev);
            return distribution(mEngine);
        }
        
        //----------------------------------------------------------------------------------------------------
        template<typename _T>
        std::vector<_T> NormalMultipleRand(unsigned long _count, _T _mean, _T _stddev)
        {
            std::vector<_T> result;
            result.reserve(_count);
            std::normal_distribution<_T> distribution(_mean, _stddev);
            for (unsigned long i = 0; i < _count; ++i)
            {
                result.push_back(distribution(mEngine));
            }
            return result;
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::random_device mDevice;
        std::default_random_engine mEngine;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VRandomTest();
}

#endif
