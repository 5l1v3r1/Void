#pragma once
#ifndef _V_MINMAXHEAP_H_
#define _V_MINMAXHEAP_H_

#include <vector>
#include <map>
#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VMinMaxHeap
    // Root: level 0(even)
    // Even level: min heap
    // Odd level: max heap
    //----------------------------------------------------------------------------------------------------
    template <typename _K, typename _T>
    class VMinMaxHeap
    {
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
            
        public:
            //----------------------------------------------------------------------------------------------------
            _K key;
            _T data;
        };
        
    public:
        //----------------------------------------------------------------------------------------------------
        inline VMinMaxHeap()
            :
            m_heap(1)
        {
            
        }
        
        //----------------------------------------------------------------------------------------------------
        inline virtual ~VMinMaxHeap()
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
        inline _T& MinFront()
        {
            return m_heap[1]->data;
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void PopMinFront()
        {
            Delete(1);
        }
        
        //----------------------------------------------------------------------------------------------------
        inline _T& MaxFront()
        {
            unsigned long size = Size();
            if (2 < size)
            {
                return m_heap[2]->IsKeyLess(m_heap[3]) ? m_heap[3]->data : m_heap[2]->data;
            }
            else if (size == 2)
            {
                return m_heap[2]->data;
            }
            else
            {
                return m_heap[1]->data;
            }
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void PopMaxFront()
        {
            unsigned long size = Size();
            if (2 < size)
            {
                m_heap[2]->IsKeyLess(m_heap[3]) ? Delete(3) : Delete(2);
            }
            else if (size == 2)
            {
                Delete(2);
            }
            else
            {
                Delete(1);
            }
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
            if (1 < _position)
            {
                // Min level
                if (IsEven(_position))
                {
                    if (m_heap[_position]->IsKeyLess(m_heap[_position / 2]))
                    {
                        while(3 < _position && m_heap[_position]->IsKeyLess(m_heap[_position / 4]))
                        {
                            Node* tmp = m_heap[_position];
                            m_heap[_position] = m_heap[_position / 4];
                            m_heap[_position / 4] = tmp;
                            _position = _position / 4;
                        }
                    }
                    else
                    {
                        // Switch to max level
                        Node* tmp = m_heap[_position];
                        m_heap[_position] = m_heap[_position / 2];
                        m_heap[_position / 2] = tmp;
                        _position = _position / 2;
                        while(3 < _position && m_heap[_position / 4]->IsKeyLess(m_heap[_position]))
                        {
                            Node* tmp = m_heap[_position];
                            m_heap[_position] = m_heap[_position / 4];
                            m_heap[_position / 4] = tmp;
                            _position = _position / 4;
                        }
                    }
                }
                // Max level
                else
                {
                    if (m_heap[_position]->IsKeyLess(m_heap[_position / 2]))
                    {
                        // Switch to min level
                        Node* tmp = m_heap[_position];
                        m_heap[_position] = m_heap[_position / 2];
                        m_heap[_position / 2] = tmp;
                        _position = _position / 2;
                        while(3 < _position && m_heap[_position]->IsKeyLess(m_heap[_position / 4]))
                        {
                            Node* tmp = m_heap[_position];
                            m_heap[_position] = m_heap[_position / 4];
                            m_heap[_position / 4] = tmp;
                            _position = _position / 4;
                        }
                    }
                    else
                    {
                        while(3 < _position && m_heap[_position / 4]->IsKeyLess(m_heap[_position]))
                        {
                            Node* tmp = m_heap[_position];
                            m_heap[_position] = m_heap[_position / 4];
                            m_heap[_position / 4] = tmp;
                            _position = _position / 4;
                        }
                    }
                }
            }
        }
        
        // Sink down
        //----------------------------------------------------------------------------------------------------
        inline void SinkDown(unsigned long _position)
        {
            // Min level
            if (IsEven(_position))
            {
                unsigned long newPosition = MinChildrenAndGrandChildren(_position);
                if (newPosition != _position)
                {
                    Node* tmp = m_heap[_position];
                    m_heap[_position] = m_heap[newPosition];
                    m_heap[newPosition] = tmp;
                    // Grand child
                    if (1 < newPosition - (_position << 1))
                    {
                        if (m_heap[newPosition >> 1]->IsKeyLess(m_heap[newPosition]))
                        {
                            tmp = m_heap[newPosition];
                            m_heap[newPosition] = m_heap[newPosition >> 1];
                            m_heap[newPosition >> 1] = tmp;
                        }
                        SinkDown(newPosition);
                    }
                }
            }
            // Max level
            else
            {
                unsigned long newPosition = MaxChildrenAndGrandChildren(_position);
                if (newPosition != _position)
                {
                    Node* tmp = m_heap[_position];
                    m_heap[_position] = m_heap[newPosition];
                    m_heap[newPosition] = tmp;
                    // Grand child
                    if (1 < newPosition - (_position << 1))
                    {
                        if (m_heap[newPosition]->IsKeyLess(m_heap[newPosition >> 1]))
                        {
                            tmp = m_heap[newPosition];
                            m_heap[newPosition] = m_heap[newPosition >> 1];
                            m_heap[newPosition >> 1] = tmp;
                        }
                        SinkDown(newPosition);
                    }
                }
            }
        }
        
        //----------------------------------------------------------------------------------------------------
        inline unsigned long MinChildrenAndGrandChildren(unsigned long _position)
        {
            unsigned long size = Size();
            unsigned long result = _position;
            // Next level
            for (unsigned long i = (_position << 1); i <= (_position << 1) + 1 && i <= size; ++i)
            {
                if (m_heap[i]->IsKeyLess(m_heap[result]))
                {
                    result = i;
                }
            }
            // Next next level
            for (unsigned long i = (_position << 2); i <= (_position << 2) + 3 && i <= size; ++i)
            {
                if (m_heap[i]->IsKeyLess(m_heap[result]))
                {
                    result = i;
                }
            }
            return result;
        }
        
        //----------------------------------------------------------------------------------------------------
        inline unsigned long MaxChildrenAndGrandChildren(unsigned long _position)
        {
            unsigned long size = Size();
            unsigned long result = _position;
            // Next level
            for (unsigned long i = (_position << 1); i <= (_position << 1) + 1 && i <= size; ++i)
            {
                if (m_heap[result]->IsKeyLess(m_heap[i]))
                {
                    result = i;
                }
            }
            // Next next level
            for (unsigned long i = (_position << 2); i <= (_position << 2) + 3 && i <= size; ++i)
            {
                if (m_heap[result]->IsKeyLess(m_heap[i]))
                {
                    result = i;
                }
            }
            return result;
        }
        
        //----------------------------------------------------------------------------------------------------
        inline bool IsEven(unsigned long _position)
        {
            do
            {
                if (_position == 1)
                {
                    return true;
                }
                if (_position == 0)
                {
                    return false;
                }
                _position >>= 2;
            }
            while (true);
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::vector<Node*> m_heap;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VMinMaxHeapTest();
};

#endif
