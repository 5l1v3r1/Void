#pragma once
#ifndef _V_DECISIONTREESPLIT_H_
#define _V_DECISIONTREESPLIT_H_

#include "../../../../Structure/Any/VAny.h"
#include "../../../../Memory/SmartPtr/VSmartPtr.h"
#include <vector>
#include <utility>
#include <map>
#include <functional>
#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VDecisionTreeSplit
    // Complete: categorical, ordinal features
    // Binary: categorical, ordinal, continuous features
    //----------------------------------------------------------------------------------------------------
    enum class VDecisionTreeSplit
    {
        Default = 0,
        Complete,
        BinaryCategorical,
        BinaryOrdinal,
        BinaryContinuous,
    };
    
    // VDecisionTreeSplitParameter
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    struct VDecisionTreeSplitParameter
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VDecisionTreeSplitParameter(const std::vector<std::pair<std::vector<VAny>, _T>*>& _samples, unsigned _featureIndex)
            :
            samples(_samples),
            featureIndex(_featureIndex)
        {
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        const std::vector<std::pair<std::vector<VAny>, _T>*>& samples;
        unsigned featureIndex;
    };
    
    // VDecisionTreeSplitResult
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    struct VDecisionTreeSplitResult
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VDecisionTreeSplitResult()
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        VDecisionTreeSplitResult(std::vector<std::vector<std::pair<std::vector<VAny>, _T>*>> _branches, std::function<unsigned(const VAny&)> _routes)
            :
            branches(_branches),
            routes(_routes)
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        void Swap(VDecisionTreeSplitResult& _other)
        {
            std::swap(branches, _other.branches);
            std::swap(routes, _other.routes);
        }
        
        //----------------------------------------------------------------------------------------------------
        void Clear()
        {
            branches.clear();
            routes = nullptr;
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        std::vector<std::vector<std::pair<std::vector<VAny>, _T>*>> branches;
        std::function<unsigned(const VAny&)> routes;
    };
    
    // VDecisionTreeSplitInterface
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VDecisionTreeSplitInterface
    {
    public:
        //----------------------------------------------------------------------------------------------------
        inline virtual ~VDecisionTreeSplitInterface() {}
        
        //----------------------------------------------------------------------------------------------------
        virtual bool Process(const VDecisionTreeSplitParameter<_T>& _parameter) = 0;
        virtual bool Next(VDecisionTreeSplitResult<_T>& _result) = 0;
    };
    
    // VDecisionTreeSplitOperator
    // _T: target type
    // _F: feature type
    // samples -> (split by one of the features) -> branches + routes
    //----------------------------------------------------------------------------------------------------
    template<typename _T, typename _F,  VDecisionTreeSplit _S>
    class VDecisionTreeSplitOperator : public VDecisionTreeSplitInterface<_T>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        bool Process(const VDecisionTreeSplitParameter<_T>& _parameter)
        {
            return false;
        }
        
        //----------------------------------------------------------------------------------------------------
        bool Next(VDecisionTreeSplitResult<_T>& _result)
        {
            return false;
        }
    };
    
    //----------------------------------------------------------------------------------------------------
    template<typename _T, typename _F>
    class VDecisionTreeSplitOperator<_T, _F, VDecisionTreeSplit::Complete> : public VDecisionTreeSplitInterface<_T>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VDecisionTreeSplitOperator()
            :
            mFlag(false)
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        bool Process(const VDecisionTreeSplitParameter<_T>& _parameter)
        {
            // Count
            mBrancheMap.clear();
            for (auto& sample : _parameter.samples)
            {
                mBrancheMap[VAnyCast<_F>(sample->first[_parameter.featureIndex])].push_back(sample);
            }
            return 2 <= mBrancheMap.size() ? true : false;
        }
        
        //----------------------------------------------------------------------------------------------------
        bool Next(VDecisionTreeSplitResult<_T>& _result)
        {
            if (2 <= mBrancheMap.size() && !mFlag)
            {
                mFlag = true;
                _result.Clear();
                std::map<_F, unsigned> routeMap;
                for (auto& branch : mBrancheMap)
                {
                    _result.branches.push_back(branch.second);
                    routeMap[VAnyCast<_F>(branch.first)] = (unsigned)(_result.branches.size() - 1);
                }
                _result.routes = [routeMap](const VAny& _feature)->unsigned
                {
                    _F feature = VAnyCast<_F>(_feature);
                    auto it = routeMap.find(feature);
                    return it != routeMap.end() ? it->second : -1;
                };
                return true;
            }
            return false;
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        bool mFlag;
        std::map<_F, std::vector<std::pair<std::vector<VAny>, _T>*>> mBrancheMap;
    };
    
    // VDecisionTreeSplitHelper
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VDecisionTreeSplitHelper
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VDecisionTreeSplitHelper()
        {
            Initialize();
        }
        
        //----------------------------------------------------------------------------------------------------
        bool Process(const VDecisionTreeSplitParameter<_T>& _parameter, VDecisionTreeSplit _split)
        {
            if (_parameter.samples.size())
            {
                std::string typeName = _parameter.samples[0]->first[_parameter.featureIndex].Type().name();
                auto it = mSplitOperators[_split].find(typeName);
                if (it != mSplitOperators[_split].end())
                {
                    mCurrentInterface = it->second;
                    if (mCurrentInterface->Process(_parameter))
                    {
                        return true;
                    }
                }
            }
            return false;
        }
        
        //----------------------------------------------------------------------------------------------------
        bool Next(VDecisionTreeSplitResult<_T>& _result)
        {
            if (mCurrentInterface && mCurrentInterface->Next(_result))
            {
                return true;
            }
            return false;
        }
        
    protected:
        // Todo: extension
        //----------------------------------------------------------------------------------------------------
        void Initialize()
        {
            // Complete (int)
            mSplitOperators[VDecisionTreeSplit::Complete][typeid(int).name()] = new VDecisionTreeSplitOperator<_T, int, VDecisionTreeSplit::Complete>();
            // Complete (string)
            mSplitOperators[VDecisionTreeSplit::Complete][typeid(std::string).name()] = new VDecisionTreeSplitOperator<_T, std::string, VDecisionTreeSplit::Complete>();
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        VSmartPtr<VDecisionTreeSplitInterface<_T>> mCurrentInterface;
        std::map<VDecisionTreeSplit, std::map<std::string, VSmartPtr<VDecisionTreeSplitInterface<_T>>>> mSplitOperators;
    };
}

#endif
