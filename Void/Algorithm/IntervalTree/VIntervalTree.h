#pragma once
#ifndef _V_INTERVALTREE_H_
#define _V_INTERVALTREE_H_

#include "../RedBlackTree/VRedBlackTree.h"
#include <math.h>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VIntervalTree
    //----------------------------------------------------------------------------------------------------
    template <typename _K, typename _T>
    class VIntervalTree : protected VRedBlackTree<_K, _T>
    {
    protected:
        //----------------------------------------------------------------------------------------------------
        struct Interval : public VRedBlackTree<_K, _T>::Node
        {
            // key: lowValue
            float highValue;
            float maxValue;
            
            //----------------------------------------------------------------------------------------------------
            inline Interval(float _lowValue, float _highValue, const _T& _data)
                :
                VRedBlackTree<_K, _T>::Node(_lowValue, _data),
                highValue(_highValue),
                maxValue(_highValue)
            {}
            
            //----------------------------------------------------------------------------------------------------
            inline virtual bool AssignData(typename VRedBlackTree<_K, _T>::Node* _node)
            {
                if (VRedBlackTree<_K, _T>::Node::AssignData(_node))
                {
                    highValue = ((Interval*)_node)->highValue;
                    Calculate();
                }
                return true;
            }
            
            //----------------------------------------------------------------------------------------------------
            inline virtual void Calculate()
            {
                maxValue = highValue;
                if (this->left)
                {
                    maxValue = std::max(maxValue, ((Interval*)this->left)->maxValue);
                }
                if (this->right)
                {
                    maxValue = std::max(maxValue, ((Interval*)this->right)->maxValue);
                }
            }
            
            //----------------------------------------------------------------------------------------------------
            inline virtual void HandleInsert(typename VRedBlackTree<_K, _T>::Node* _node)
            {
                if (_node)
                {
                    maxValue = std::max(maxValue, ((Interval*)_node)->highValue);
                }
            }
        };
        
    public:
        //----------------------------------------------------------------------------------------------------
        inline VIntervalTree()
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        inline virtual ~VIntervalTree()
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void Insert(float _lowValue, float _highValue, const _T& _data)
        {
            VRedBlackTree<_K, _T>::Insert(CreateNode(_lowValue, _highValue, _data));
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void FindData(float _lowValue, float _highValue, std::vector<_T>& _data)
        {
            _data.clear();
            FindData(this->m_root, _lowValue, _highValue, _data);
        }
        
        //----------------------------------------------------------------------------------------------------
        inline bool FindData(float _lowValue, float _highValue, _T& _data)
        {
            return FindData(this->m_root, _lowValue, _highValue, _data);
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        inline typename VRedBlackTree<_K, _T>::Node* CreateNode(float _lowValue, float _highValue, const _T& _data)
        {
            return new Interval(_lowValue, _highValue, _data);
        }
        
        //----------------------------------------------------------------------------------------------------
        inline bool FindData(typename VRedBlackTree<_K, _T>::Node* _node, float _lowValue, float _highValue, _T& _data)
        {
            if (_node && _lowValue <= ((Interval*)_node)->maxValue)
            {
                if (IsOverlap(_node, _lowValue, _highValue))
                {
                    _data = _node->data;
                    return true;
                }
                
                if (FindData(_node->left, _lowValue, _highValue, _data))
                {
                    return true;
                }
                if (((Interval*)_node)->key <= _highValue)
                {
                    return FindData(_node->right, _lowValue, _highValue, _data);
                }
            }
            
            return false;
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void FindData(typename VRedBlackTree<_K, _T>::Node* _node, float _lowValue, float _highValue, std::vector<_T>& _data)
        {
            if (_node && _lowValue <= ((Interval*)_node)->maxValue)
            {
                if (IsOverlap(_node, _lowValue, _highValue))
                {
                    _data.push_back(_node->data);
                }
                
                FindData(_node->left, _lowValue, _highValue, _data);
                if (((Interval*)_node)->key <= _highValue)
                {
                    FindData(_node->right, _lowValue, _highValue, _data);
                }
            }
        }
        
        //----------------------------------------------------------------------------------------------------
        inline bool IsOverlap(typename VRedBlackTree<_K, _T>::Node* _node, float _lowValue, float _highValue)
        {
            if (((Interval*)_node)->highValue < _lowValue)
                return false;
            else if (_highValue < ((Interval*)_node)->key)
                return false;
            
            return true;
        }
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VIntervalTreeTest();
};

#endif
