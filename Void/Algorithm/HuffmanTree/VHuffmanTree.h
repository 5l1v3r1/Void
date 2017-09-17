#pragma once
#ifndef _V_HUFFMANTREE_H_
#define _V_HUFFMANTREE_H_

#include "../../Memory/SmartPointer/VSmartPointer.h"
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
            VSharePointer<Node> left;
            VSharePointer<Node> right;
            int weight;
            std::pair<const int, int>* data;
        };
        
        // SmartNode
        //----------------------------------------------------------------------------------------------------
        typedef VSharePointer<Node> SmartNode;
        
    public:
        // +counter
        //----------------------------------------------------------------------------------------------------
        inline void Insert(const _T& _data)
        {
            auto it = mCounter.find(_data);
            if(it != mCounter.end())
            {
                ++it->second;
            }
            else
            {
                mCounter[_data] = 1;
            }
        }
        
        // counter -> min heap -> tree -> code table
        //----------------------------------------------------------------------------------------------------
        inline const std::map<_T, std::string>& Generate()
        {
            VMinHeap<int, SmartNode> heap;
            for (std::pair<const int, int>& pair : mCounter)
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
            
            mCodeTable.clear();
            if (heap.Size())
            {
                Generate("", heap.Front());
            }
            return mCodeTable;
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
                    mCodeTable.insert(std::pair<_T, std::string>(_node->data->first, _prefixCode));
                }
            }
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::map<_T, int> mCounter;
        std::map<_T, std::string> mCodeTable;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VHuffmanTreeTest();
};

#endif
