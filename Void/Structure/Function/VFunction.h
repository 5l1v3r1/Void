#pragma once
#ifndef _V_FUNCTION_H_
#define _V_FUNCTION_H_

#include "../../Utility/Logger/VLogger.h"
#include "../../Utility/Type/VType.h"
#include "../Any/VAny.h"
#include <functional>
#include <vector>
#include <map>
#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VFunction
    // domain -> range
    // x -> f(x) = y
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VFunction
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VFunction()
            :
            variables(),
            lambda()
        {
        }
        
        VFunction(std::function<_T(const std::map<std::string, VAny>&)> _lambda)
            :
            variables(),
            lambda(_lambda)
        {
        }
        
        VFunction(const VFunction& _function)
            :
            variables(_function.variables),
            lambda(_function.lambda)
        {
        }
        
        ~VFunction()
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        _T Value(std::map<std::string, VAny> _variables) const
        {
            for (auto& pair : variables)
            {
                _variables.insert(pair);
            }
            return lambda(_variables);
        }
        
        _T Value() const
        {
            return lambda(variables);
        }
        
        //----------------------------------------------------------------------------------------------------
        void Bind(const std::string& _name, const VAny& _variable)
        {
            variables[_name] = _variable;
        }
        
        void Bind(const std::map<std::string, VAny>& _variables)
        {
            for (auto& pair : _variables)
            {
                variables.insert(pair);
            }
        }
        
        bool Unbind(const std::string& _name)
        {
            auto variable = variables.find(_name);
            if (variable != variables.end())
            {
                variables.erase(variable);
                return true;
            }
            return false;
        }
        
        //----------------------------------------------------------------------------------------------------
        VFunction& operator=(const VFunction& _function)
        {
            variables = _function.variables;
            lambda = _function.lambda;
            return *this;
        }
        
        VFunction& operator=(std::function<_T(const std::map<std::string, VAny>&)> _function)
        {
            lambda = _function;
            return *this;
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        std::map<std::string, VAny> variables;
        std::function<_T(const std::map<std::string, VAny>&)> lambda;
    };
    
    // VFunction operator
    //----------------------------------------------------------------------------------------------------
    template<typename _LT, typename _RT>
    auto operator+(const VFunction<_LT>& _leftFunction, const VFunction<_RT>& _rightFunction)
    {
        auto lambda = [leftLambda=_leftFunction.lambda, rightLambda=_rightFunction.lambda](const std::map<std::string, VAny>& _variables)->auto
        {
            return leftLambda(_variables) + rightLambda(_variables);
        };
        VFunction<typename VTypeIndex<0, typename VTypeLambda<decltype(lambda)>::Types>::Type> function(lambda);
        function.Bind(_leftFunction.variables);
        function.Bind(_rightFunction.variables);
        return function;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VFunctionTest();
}

#endif
