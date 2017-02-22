#pragma once
#ifndef _V_HUFFMANTREE_H_
#define _V_HUFFMANTREE_H_

#include "../../Memory/SmartPtr/VSmartPtr.h"
#include <vector>
#include <map>
#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VRedBlackTree
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
            inline Node(int _weight, const _T& _data)
                :
                parent(nullptr),
                left(nullptr),
                right(nullptr),
                weight(_weight),
                data(_data)
            {
            }
            
        public:
            //----------------------------------------------------------------------------------------------------
            Node *parent;
            Node *left;
            Node *right;
            int weight;
            _T data;
        };
        
    public:
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
        
        //----------------------------------------------------------------------------------------------------
        inline const std::map<_T, std::string>& Generate()
        {
            std::vector<VSmartPtr<Node>> nodes;
            m_codeTable.clear();
            for (auto& it : m_counter)
            {
                nodes.push_back(VSmartPtr<Node>(new Node(it.second, it.first)));
            }
            // Todo
            
            return m_codeTable;
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
