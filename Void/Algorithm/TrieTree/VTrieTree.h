#pragma once
#ifndef _V_TRIETREE_H_
#define _V_TRIETREE_H_

#include <map>
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VTrieTree
    //----------------------------------------------------------------------------------------------------
    template <typename _T>
    class VTrieTree
    {
    protected:
        // Node
        //----------------------------------------------------------------------------------------------------
        struct Node
        {
        public:
            //----------------------------------------------------------------------------------------------------
            inline Node()
                :
                isWhole(false)
            {
            }
            
            //----------------------------------------------------------------------------------------------------
            inline Node(const _T& _prefix, bool _isWhole=false)
                :
                prefix(_prefix),
                isWhole(_isWhole)
            {
            }
            
            //----------------------------------------------------------------------------------------------------
            inline virtual ~Node()
            {
            }
            
        public:
            //----------------------------------------------------------------------------------------------------
            _T prefix;
            bool isWhole;
            std::map<typename _T::value_type, Node*> children;
        };
        
    public:
        //----------------------------------------------------------------------------------------------------
        inline VTrieTree()
            :
            m_root(CreateNode(_T()))
        {
            
        }
        
        //----------------------------------------------------------------------------------------------------
        inline virtual ~VTrieTree()
        {
            Delete(m_root);
            
            return;
        }
        
        //----------------------------------------------------------------------------------------------------
        void Insert(const _T& _collection)
        {
            Node* node = m_root;
            for(auto& element : _collection)
            {
                auto it = node->children.find(element);
                if(it == node->children.end())
                {
                    auto prefix = node->prefix;
                    std::back_inserter(prefix) = element;
                    node->children[element] = CreateNode(prefix);
                }
                node = node->children[element];
            }
            node->isWhole = true;
        }
        
        //----------------------------------------------------------------------------------------------------
        bool Has(const _T& _collection)
        {
            Node* node = m_root;
            for(auto& element : _collection)
            {
                auto it = node->children.find(element);
                if(it == node->children.end())
                {
                    return false;
                }
                node = node->children[element];
            }
            if (node->isWhole)
            {
                return true;
            }
            return false;
        }
        
        //----------------------------------------------------------------------------------------------------
        std::vector<const _T*> AutoComplete(const _T& _prefix)
        {
            Node* node = m_root;
            for(auto& element : _prefix)
            {
                auto it = node->children.find(element);
                if(it == node->children.end())
                {
                    return std::vector<const _T*>();
                }
               node = node->children[element];
            }
            std::vector<const _T*> result;
            List(result, node);
            return result;
        }
        
        //----------------------------------------------------------------------------------------------------
        std::vector<const _T*> List()
        {
            std::vector<const _T*> result;
            List(result, m_root);
            return result;
        }
        
        //----------------------------------------------------------------------------------------------------
        unsigned long Size()
        {
            return List().size();
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        inline virtual Node* CreateNode(const _T& _prefix, bool _isWhole=false)
        {
            return new Node(_prefix, _isWhole);
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void Delete(Node*& _node)
        {
            if (_node)
            {
                // Delete children
                for(auto& pair : _node->children)
                {
                    Delete(pair.second);
                }
                _node->children.clear();
                
                // Delete self
                delete _node;
                _node = nullptr;
            }
        }
        
        //----------------------------------------------------------------------------------------------------
        void List(std::vector<const _T*>& _result, Node* _node)
        {
            if (_node)
            {
                if (_node->isWhole)
                {
                    _result.push_back(&_node->prefix);
                }
                for(auto& pair : _node->children)
                {
                    List(_result, pair.second);
                }
            }
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        Node* m_root;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VTrieTreeTest();
};

#endif
