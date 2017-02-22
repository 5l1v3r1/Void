#pragma once
#ifndef _V_MAXHEAP_H_
#define _V_MAXHEAP_H_

#include "../MinHeap/VMinHeap.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VMaxHeap
    //----------------------------------------------------------------------------------------------------
    template <typename _K, typename _T>
    class VMaxHeap : public VMinHeap<_K, _T>
    {
    protected:
        // MaxNode
        //----------------------------------------------------------------------------------------------------
        struct MaxNode : public VMinHeap<_K, _T>::Node
        {
        public:
            //----------------------------------------------------------------------------------------------------
            inline MaxNode(_K _key, const _T& _data)
                :
                VMinHeap<_K, _T>::Node(_key, _data)
            {
            }
            
            //----------------------------------------------------------------------------------------------------
            inline virtual bool IsKeyLess(typename VMinHeap<_K, _T>::Node* _node) const // Index
            {
                return _node ? _node->key < this->key : false;
            }
        };
        
    public:
        //----------------------------------------------------------------------------------------------------
        inline VMaxHeap()
            :
            VMinHeap<_K, _T>()
        {
            
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        inline virtual typename VMinHeap<_K, _T>::Node* CreateNode(_K _key, const _T& _data)
        {
            return new MaxNode(_key, _data);
        }
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VMaxHeapTest();
};

#endif
