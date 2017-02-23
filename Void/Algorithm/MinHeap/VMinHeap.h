#pragma once
#ifndef _V_MINHEAP_H_
#define _V_MINHEAP_H_

#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VMinHeap
    // Space O(n)
    // Search O(n)
    // Insert O(log n)
    // Delete O(log n)
    //----------------------------------------------------------------------------------------------------
    template <typename _K, typename _T>
    class VMinHeap
    {
    protected:
        // Node
        //----------------------------------------------------------------------------------------------------
        struct Node
        {
        public:
            //----------------------------------------------------------------------------------------------------
            inline Node(_K _key, const _T& _data)
                :
                key(_key),
                data(_data)
            {
            }
            
            //----------------------------------------------------------------------------------------------------
            inline virtual bool AssignData(Node* _node)
            {
                if (_node)
                {
                    key = _node->key;
                    data = _node->data;
                    return true;
                }
                return false;
            }
            
            //----------------------------------------------------------------------------------------------------
            inline virtual bool IsEqual(Node* _node) const // Find
            {
                return _node ? key == _node->key && data == _node->data : false;
            }
            
            //----------------------------------------------------------------------------------------------------
            inline virtual bool IsKeyEqual(Node* _node) const // Index
            {
                return _node ? key == _node->key : false;
            }
            
            //----------------------------------------------------------------------------------------------------
            inline virtual bool IsKeyLess(Node* _node) const // Index
            {
                return _node ? key < _node->key : false;
            }
            
            //----------------------------------------------------------------------------------------------------
            //inline virtual void HandleSinkDown() // Dirction: ↓
            //{
                // Nothing
            //}
            
            //----------------------------------------------------------------------------------------------------
            //inline virtual void HandleBubbleUp(Node* _node) // Dirction: ↑
            //{
                // Nothing
            //}
            
        public:
            //----------------------------------------------------------------------------------------------------
            _K key;
            _T data;
        };
        
    public:
        //----------------------------------------------------------------------------------------------------
        inline VMinHeap()
            :
            m_heap(1)
        {
            
        }
        
        //----------------------------------------------------------------------------------------------------
        inline virtual ~VMinHeap()
        {
            for (auto& node : m_heap)
            {
                if (node)
                {
                    delete node;
                    node = nullptr;
                }
            }
            m_heap.clear();
        }
        
        //----------------------------------------------------------------------------------------------------
        inline _T& Front()
        {
            return m_heap[1]->data;
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void PopFront()
        {
            Delete(1);
        }
        
        //----------------------------------------------------------------------------------------------------
        inline unsigned long Size()
        {
            return m_heap.size() - 1;
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void Insert(_K _key, const _T& _data)
        {
            Insert(CreateNode(_key, _data));
        }
        
        
    protected:
        //----------------------------------------------------------------------------------------------------
        inline virtual Node* CreateNode(_K _key, const _T& _data)
        {
            return new Node(_key, _data);
        }
        
        // Bubble up
        //----------------------------------------------------------------------------------------------------
        inline void Insert(Node *_node)
        {
            m_heap.push_back(_node);
            unsigned long position = m_heap.size() - 1;
            while(1 < position && m_heap[position]->IsKeyLess(m_heap[position / 2]))
            {
                //m_heap[position]->HandleBubbleUp(m_heap[position / 2]);
                Node* tmp = m_heap[position];
                m_heap[position] = m_heap[position / 2];
                m_heap[position / 2] = tmp;
                position = position / 2;
            }
        }
        
        // Sink down
        //----------------------------------------------------------------------------------------------------
        inline void Delete(int _index)
        {
            if (_index <= 0 || m_heap.size() <= _index)
            {
                return;
            }
            
            delete m_heap[_index];
            m_heap[_index] = m_heap[m_heap.size() - 1];
            m_heap.pop_back();
            while ((_index << 1) < m_heap.size())
            {
                int newIndex = _index;
                if (m_heap[_index << 1]->IsKeyLess(m_heap[_index]))
                {
                    newIndex = _index << 1;
                }
                if ((_index << 1) + 1 < m_heap.size() && m_heap[(_index << 1) + 1]->IsKeyLess(m_heap[newIndex]))
                {
                    newIndex = (_index << 1) + 1;
                }
                
                if (newIndex != _index)
                {
                    //m_heap[_index]->HandleSinkDown(m_heap[newIndex]);
                    Node* tmp = m_heap[_index];
                    m_heap[_index] = m_heap[newIndex];
                    m_heap[newIndex] = tmp;
                    _index = newIndex;
                }
                else
                {
                    break;
                }
            }
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::vector<Node*> m_heap;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VMinHeapTest();
};

#endif
