#pragma once
#ifndef _V_ROULETTEWHEEL_H_
#define _V_ROULETTEWHEEL_H_

#include <vector>
#include <iterator>
#include <cstdlib>
#include "../RedBlackTree/VRedBlackTree.h"


//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VRouletteWheel
    // Todo: size
    //----------------------------------------------------------------------------------------------------
    template <typename _T>
    class VRouletteWheel : protected VRedBlackTree<_T>
    {
    protected:
        // Section
        // Key: range
        //----------------------------------------------------------------------------------------------------
        struct Section : public VRedBlackTree<_T>::Node
        {
        public:
            //----------------------------------------------------------------------------------------------------
            inline Section(float _range, const _T& _data)
                :
                VRedBlackTree<_T>::Node(_range, _data),
                totalRange(_range)
            {
            }
            
            //----------------------------------------------------------------------------------------------------
            inline virtual bool AssignData(typename VRedBlackTree<_T>::Node* _node)
            {
                if (VRedBlackTree<_T>::Node::AssignData(_node))
                {
                    Calculate();
                }
                return true;
            }
            
            //----------------------------------------------------------------------------------------------------
            inline virtual void Calculate()
            {
                totalRange = this->key;
                if (this->left)
                    totalRange += ((Section*)this->left)->totalRange;
                if (this->right)
                    totalRange += ((Section*)this->right)->totalRange;
                
                if (this->parent)
                    this->parent->Calculate();
            }
            
            //----------------------------------------------------------------------------------------------------
            inline virtual void HandleInsert(typename VRedBlackTree<_T>::Node* _node)
            {
                if (_node)
                {
                    totalRange += ((Section*)_node)->totalRange;
                }
            }
            
        public:
            //----------------------------------------------------------------------------------------------------
            float totalRange;
        };
        
    public:
        //----------------------------------------------------------------------------------------------------
        inline VRouletteWheel()
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        inline virtual ~VRouletteWheel()
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        inline typename VRedBlackTree<_T>::NodeIterator begin()
        {
            return VRedBlackTree<_T>::begin();
        }
        
        //----------------------------------------------------------------------------------------------------
        inline typename VRedBlackTree<_T>::NodeIterator end()
        {
            return VRedBlackTree<_T>::end();
        }
        
        //----------------------------------------------------------------------------------------------------
        inline _T& Front()
        {
            return VRedBlackTree<_T>::Front();
        }
        
        //----------------------------------------------------------------------------------------------------
        inline _T& Back()
        {
            return VRedBlackTree<_T>::Back();
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void PopFront()
        {
            return VRedBlackTree<_T>::PopFront();
        }
        
        //----------------------------------------------------------------------------------------------------
        inline unsigned int Size()
        {
            return VRedBlackTree<_T>::Size();
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void Insert(float _range, const _T& _data)
        {
            VRedBlackTree<_T>::Insert(CreateNode(_range, _data));
        }
        
        //----------------------------------------------------------------------------------------------------
        inline bool Delete(float _range, const _T& _data)
        {
            Section section(_range, _data);
            typename VRedBlackTree<_T>::Node *target = VRedBlackTree<_T>::FindNode(this->m_root, &section);
            if (target)
            {
                VRedBlackTree<_T>::Delete(target);
                return true;
            }
            return false;
        }
        
        //----------------------------------------------------------------------------------------------------
        inline float GetTotalRange()
        {
            if (this->m_root)
                return ((Section*)this->m_root)->totalRange;
            return 0.f;
        }
        
        //----------------------------------------------------------------------------------------------------
        inline bool Select(float _pos, _T& _result)
        {
            float turns = _pos / GetTotalRange();
            if (turns < 0.f)
                turns += 1.f;
            _pos = GetTotalRange() * (turns - (int)turns);
            return Select(this->m_root, _pos, _result);
        }
        
        //----------------------------------------------------------------------------------------------------
        inline bool RandomSelect(_T& _result)
        {
            float pos = GetTotalRange() * ((float)rand() / (float)RAND_MAX);
            return Select(pos, _result);
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        inline virtual typename VRedBlackTree<_T>::Node* CreateNode(float _range, const _T& _data)
        {
            return new Section(_range, _data);
        }
        
        //----------------------------------------------------------------------------------------------------
        inline bool Select(typename VRedBlackTree<_T>::Node* _node, float _pos, _T& _result)
        {
            if (_node)
            {
                // Left
                if (_node->left)
                {
                    if (_pos <= ((Section*)_node->left)->totalRange)
                        return Select(_node->left, _pos, _result);
                    _pos -= ((Section*)_node->left)->totalRange;
                }
                
                // Self
                if (_pos <= ((Section*)_node)->key)
                {
                    _result = _node->data;
                    return true;
                }
                _pos -= ((Section*)_node)->key;
                
                // Right
                if (_node->right)
                {
                    if (_pos <= ((Section*)_node->right)->totalRange)
                        return Select(_node->right, _pos, _result);
                    // Overflow
                    return false;
                }
            }
            
            return false;
        }
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VRouletteWheelTest();
};

#endif
