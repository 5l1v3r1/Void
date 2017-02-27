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
        
        //----------------------------------------------------------------------------------------------------
        inline void Insert(Node *_node)
        {
            m_heap.push_back(_node);
            unsigned long position = m_heap.size() - 1;
            BubbleUp(position);
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void Delete(unsigned long _position)
        {
            if (_position <= 0 || m_heap.size() <= _position)
            {
                return;
            }
            
            delete m_heap[_position];
            m_heap[_position] = m_heap[m_heap.size() - 1];
            m_heap.pop_back();
            if (_position == m_heap.size())
            {
                return;
            }
            BubbleUp(_position);
            SinkDown(_position);
        }
        
        // Bubble up
        //----------------------------------------------------------------------------------------------------
        inline void BubbleUp(unsigned long _position)
        {
            while(1 < _position && m_heap[_position]->IsKeyLess(m_heap[_position / 2]))
            {
                //m_heap[_position]->HandleBubbleUp(m_heap[_position / 2]);
                Node* tmp = m_heap[_position];
                m_heap[_position] = m_heap[_position / 2];
                m_heap[_position / 2] = tmp;
                _position = _position / 2;
            }
        }
        
        // Sink down
        //----------------------------------------------------------------------------------------------------
        inline void SinkDown(unsigned long _position)
        {
            while ((_position << 1) < m_heap.size())
            {
                unsigned long newPosition = _position;
                if (m_heap[_position << 1]->IsKeyLess(m_heap[_position]))
                {
                    newPosition = _position << 1;
                }
                if ((_position << 1) + 1 < m_heap.size() && m_heap[(_position << 1) + 1]->IsKeyLess(m_heap[newPosition]))
                {
                    newPosition = (_position << 1) + 1;
                }
                
                if (newPosition != _position)
                {
                    //m_heap[_position]->HandleSinkDown(m_heap[newPosition]);
                    Node* tmp = m_heap[_position];
                    m_heap[_position] = m_heap[newPosition];
                    m_heap[newPosition] = tmp;
                    _position = newPosition;
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
