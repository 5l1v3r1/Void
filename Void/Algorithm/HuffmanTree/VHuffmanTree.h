#pragma once
#ifndef _V_HUFFMANTREE_H_
#define _V_HUFFMANTREE_H_

#include "../../Memory/SmartPtr/VSmartPtr.h"
#include "../MinHeap/VMinHeap.h"
#include <vector>
#include <map>
#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VHuffmanTree
    //----------------------------------------------------------------------------------------------------
    template <typename _T>
    class VHuffmanTree
    {
    protected:
        // Node
        //----------------------------------------------------------------------------------------------------
        struct Node
        {
        public:
            //----------------------------------------------------------------------------------------------------
            inline Node(int _weight, std::pair<const int, int>* _data)
                :
                left(nullptr),
                right(nullptr),
                weight(_weight),
                data(_data)
            {
            }
            
        public:
            //----------------------------------------------------------------------------------------------------
            VSmartPtr<Node> left;
            VSmartPtr<Node> right;
            int weight;
            std::pair<const int, int>* data;
        };
        
        // SmartNode
        //----------------------------------------------------------------------------------------------------
        typedef VSmartPtr<Node> SmartNode;
        
    public:
        // +counter
        //----------------------------------------------------------------------------------------------------
        inline void Insert(const _T& _data)
        {
            auto it = m_counter.find(_data);
            if(it != m_counter.end())
            {
                ++it->second;
            }
            else
            {
                m_counter[_data] = 1;
            }
        }
        
        // counter -> min heap -> tree -> code table
        //----------------------------------------------------------------------------------------------------
        inline const std::map<_T, std::string>& Generate()
        {
            VMinHeap<int, SmartNode> heap;
            for (std::pair<const int, int>& pair : m_counter)
            {
                heap.Insert(pair.second, SmartNode(new Node(pair.second, &pair)));
            }
            while (1 < heap.Size())
            {
                SmartNode firstNode = heap.Front();
                heap.PopFront();
                SmartNode secondNode = heap.Front();
                heap.PopFront();
                SmartNode newNode = SmartNode(new Node(firstNode->weight + secondNode->weight, nullptr));
                newNode->left = firstNode;
                newNode->right = secondNode;
                heap.Insert(newNode->weight, newNode);
            }
            
            m_codeTable.clear();
            if (heap.Size())
            {
                Generate("", heap.Front());
            }
            return m_codeTable;
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        inline void Generate(std::string _prefixCode, SmartNode _node)
        {
            if (_node)
            {
                if (_node->left)
                {
                    Generate(_prefixCode + "0", _node->left);
                }
                if (_node->right)
                {
                    Generate(_prefixCode + "1", _node->right);
                }
                if (!_node->left && !_node->right)
                {
                    m_codeTable.insert(std::pair<_T, std::string>(_node->data->first, _prefixCode));
                }
            }
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::map<_T, int> m_counter;
        std::map<_T, std::string> m_codeTable;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VHuffmanTreeTest();
};

#endif
