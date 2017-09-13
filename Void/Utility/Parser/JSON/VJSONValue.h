#pragma once
#ifndef _V_JSONVALUE_H_
#define _V_JSONVALUE_H_

#include "../../../Structure/Any/VAny.h"
#include <string>
#include <map>
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VJSONValueType
    // Null: nullptr (real blank)
    // Boolean: bool
    // Object: std::map<std::string, VJSONValue>
    // Array: std::vector<VJSONValue>
    // Number: long double
    // String: std::string
    //----------------------------------------------------------------------------------------------------
    enum class VJSONValueType
    {
        Null = 0,
        Boolean,
        Object,
        Array,
        Number,
        String,
    };
    
    // VJSONValue
    //----------------------------------------------------------------------------------------------------
    class VJSONValue : protected VAny
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VJSONValue()
            :
            VAny(),
            mType(VJSONValueType::Null)
        {
        }
        
        VJSONValue(const VJSONValue& _value)
            :
            VAny(static_cast<const VAny&>(_value)),
            mType(_value.mType)
        {
        }
        
        virtual ~VJSONValue()
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        VJSONValue& operator=(const VJSONValue& _any)
        {
            VAny::operator=(_any);
            mType = _any.mType;
            return *this;
        }
        
        VJSONValue& operator=(VJSONValue&& _any)
        {
            VAny::operator=(_any);
            mType = _any.mType;
            return *this;
        }
        
        VJSONValue& operator=(bool&& _bool)
        {
            VAny::operator=(_bool);
            mType = VJSONValueType::Boolean;
            return *this;
        }
        
        VJSONValue& operator=(std::map<std::string, VJSONValue>&& _object)
        {
            VAny::operator=(_object);
            mType = VJSONValueType::Object;
            return *this;
        }
        
        VJSONValue& operator=(std::vector<VJSONValue>&& _array)
        {
            VAny::operator=(_array);
            mType = VJSONValueType::Array;
            return *this;
        }
        
        VJSONValue& operator=(long double&& _number)
        {
            VAny::operator=(_number);
            mType = VJSONValueType::Number;
            return *this;
        }
        
        VJSONValue& operator=(std::string&& _string)
        {
            VAny::operator=(_string);
            mType = VJSONValueType::String;
            return *this;
        }
        
        //----------------------------------------------------------------------------------------------------
        VJSONValueType Type() const
        {
            return mType;
        }
        
        // Null
        //----------------------------------------------------------------------------------------------------
        bool Null() const
        {
            return VAny::Empty();
        }
        
        void Clear()
        {
            VAny::Clear();
            mType = VJSONValueType::Null;
        }
        
        // Boolean
        //----------------------------------------------------------------------------------------------------
        bool& Boolean()
        {
            if (mType == VJSONValueType::Boolean)
            {
                return VAnyCast<bool&>(*this);
            }
            throw "VJSONValue: type error";
        }
        
        const bool& Boolean() const
        {
            if (mType == VJSONValueType::Boolean)
            {
                return VAnyCast<const bool&>(*this);
            }
            throw "VJSONValue: type error";
        }
        
        // Object
        //----------------------------------------------------------------------------------------------------
        std::map<std::string, VJSONValue>& Object()
        {
            if (mType == VJSONValueType::Object)
            {
                return VAnyCast<std::map<std::string, VJSONValue>&>(*this);
            }
            throw "VJSONValue: type error";
        }
        
        const std::map<std::string, VJSONValue>& Object() const
        {
            if (mType == VJSONValueType::Object)
            {
                return VAnyCast<const std::map<std::string, VJSONValue>&>(*this);
            }
            throw "VJSONValue: type error";
        }
        
        VJSONValue& operator[](const std::string& _identifier)
        {
            if (mType == VJSONValueType::Object)
            {
                return VAnyCast<std::map<std::string, VJSONValue>&>(*this)[_identifier];
            }
            throw "VJSONValue: type error";
        }
        
        const VJSONValue& operator[](const std::string& _identifier) const
        {
            if (mType == VJSONValueType::Object)
            {
                return VAnyCast<const std::map<std::string, VJSONValue>&>(*this).at(_identifier);
            }
            throw "VJSONValue: type error";
        }
        
        bool Has(const std::string& _identifier) const
        {
            if (mType == VJSONValueType::Object)
            {
                const std::map<std::string, VJSONValue>& object = VAnyCast<const std::map<std::string, VJSONValue>&>(*this);
                return object.find(_identifier) != object.end();
            }
            throw "VJSONValue: type error";
        }
        
        // Array
        //----------------------------------------------------------------------------------------------------
        std::vector<VJSONValue>& Array()
        {
            if (mType == VJSONValueType::Array)
            {
                return VAnyCast<std::vector<VJSONValue>&>(*this);
            }
            throw "VJSONValue: type error";
        }
        
        const std::vector<VJSONValue>& Array() const
        {
            if (mType == VJSONValueType::Array)
            {
                return VAnyCast<const std::vector<VJSONValue>&>(*this);
            }
            throw "VJSONValue: type error";
        }
        
        VJSONValue& operator[](const unsigned long& _index)
        {
            if (mType == VJSONValueType::Array)
            {
                return VAnyCast<std::vector<VJSONValue>&>(*this)[_index];
            }
            throw "VJSONValue: type error";
        }
        
        VJSONValue operator[](const unsigned long& _index) const
        {
            if (mType == VJSONValueType::Array)
            {
                return VAnyCast<const std::vector<VJSONValue>&>(*this)[_index];
            }
            throw "VJSONValue: type error";
        }
        
        void PushBack(VJSONValue& _value)
        {
            if (mType == VJSONValueType::Array)
            {
                return VAnyCast<std::vector<VJSONValue>&>(*this).push_back(_value);
            }
            throw "VJSONValue: type error";
        }
        
        // Number
        //----------------------------------------------------------------------------------------------------
        long double& Number()
        {
            if (mType == VJSONValueType::Number)
            {
                return VAnyCast<long double&>(*this);
            }
            throw "VJSONValue: type error";
        }
        
        const long double& Number() const
        {
            if (mType == VJSONValueType::Number)
            {
                return VAnyCast<const long double&>(*this);
            }
            throw "VJSONValue: type error";
        }
        
        // String
        //----------------------------------------------------------------------------------------------------
        std::string& String()
        {
            if (mType == VJSONValueType::String)
            {
                return VAnyCast<std::string&>(*this);
            }
            throw "VJSONValue: type error";
        }
        
        const std::string& String() const
        {
            if (mType == VJSONValueType::String)
            {
                return VAnyCast<const std::string&>(*this);
            }
            throw "VJSONValue: type error";
        }
        
        void PushBack(char _character)
        {
            if (mType == VJSONValueType::String)
            {
                return VAnyCast<std::string&>(*this).push_back(_character);
            }
            throw "VJSONValue: type error";
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        VJSONValueType mType;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VJSONValueTest();
}

#endif
