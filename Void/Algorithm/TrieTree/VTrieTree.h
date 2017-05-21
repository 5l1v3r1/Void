#pragma once
#ifndef _V_TRIETREE_H_
#define _V_TRIETREE_H_

#include <map>
#include <vector>
#include <iterator>

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
                size(0),
                isWhole(false)
            {
            }
            
            //----------------------------------------------------------------------------------------------------
            inline Node(const _T& _prefix, bool _isWhole=false)
                :
                size(0),
                prefix(_prefix),
                isWhole(_isWhole)
            {
            }
            
            //----------------------------------------------------------------------------------------------------
            inline virtual ~Node()
            {
            }
            
            //----------------------------------------------------------------------------------------------------
            inline virtual void HandleInsert(Node* _node) // Dirction: ↑
            {
                if (_node)
                {
                    size += 1;
                }
            }
            
        public:
            //----------------------------------------------------------------------------------------------------
            unsigned int size;
            _T prefix; // Todo: optional
            bool isWhole;
            std::map<typename _T::value_type, Node*> children;
        };
        
    public:
        //----------------------------------------------------------------------------------------------------
        inline VTrieTree()
            :
            m_root(nullptr)
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
            std::vector<Node*> prefixNodes;
            Node* node = FindOrCreate(_collection, true, &prefixNodes);
            if (node->isWhole == false)
            {
                AfterInserted(node);
                for (auto& prefixNode : prefixNodes)
                {
                    prefixNode->HandleInsert(node);
                }
            }
        }
        
        //----------------------------------------------------------------------------------------------------
        void Insert(const _T& _prefix, const typename _T::value_type& _element)
        {
            std::vector<Node*> prefixNodes;
            Node* node = FindOrCreate(_prefix, true, &prefixNodes);
            
            auto it = node->children.find(_element);
            if(it == node->children.end())
            {
                auto prefix = node->prefix;
                std::back_inserter(prefix) = _element;
                node->children[_element] = CreateNode(prefix);
                
                Node* newNode = node->children[_element];
                AfterInserted(newNode);
                for (auto& prefixNode : prefixNodes)
                {
                    prefixNode->HandleInsert(newNode);
                }
            }
        }
        
        //----------------------------------------------------------------------------------------------------
        void MultipleInsert(const _T& _prefix, const std::vector<typename _T::value_type>& _elements)
        {
            std::vector<Node*> prefixNodes;
            Node* node = FindOrCreate(_prefix, true, &prefixNodes);
            for(auto& element : _elements)
            {
                auto it = node->children.find(element);
                if(it == node->children.end())
                {
                    auto prefix = node->prefix;
                    std::back_inserter(prefix) = element;
                    node->children[element] = CreateNode(prefix);
                    
                    Node* newNode = node->children[element];
                    AfterInserted(newNode);
                    for (auto& prefixNode : prefixNodes)
                    {
                        prefixNode->HandleInsert(newNode);
                    }
                }
            }
        }
        
        //----------------------------------------------------------------------------------------------------
        bool Has(const _T& _collection)
        {
            Node* node = FindOrCreate(_collection, false);
            if (node && node->isWhole)
            {
                return true;
            }
            return false;
        }
        
        //----------------------------------------------------------------------------------------------------
        std::vector<const _T*> List(const _T& _prefix=_T())
        {
            Node* node = FindOrCreate(_prefix, false);
            std::vector<const _T*> result;
            if (node)
            {
                List(result, node);
            }
            return result;
        }
        
        //----------------------------------------------------------------------------------------------------
        unsigned long Size(const _T& _prefix=_T())
        {
            Node* node = FindOrCreate(_prefix, false);
            if (node)
            {
                return m_root->size;
            }
            return 0;
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        inline virtual Node* CreateNode(const _T& _prefix, bool _isWhole=false)
        {
            return new Node(_prefix, _isWhole);
        }
        
        //----------------------------------------------------------------------------------------------------
        inline virtual void AfterInserted(Node* _node)
        {
            if (_node)
            {
                _node->isWhole = true;
            }
        }
        
        // Todo: decrease size
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
                for (auto& pair : _node->children)
                {
                    List(_result, pair.second);
                }
            }
        }
        
        //----------------------------------------------------------------------------------------------------
        Node* FindOrCreate(const _T& _prefix, bool _isCreating=false, std::vector<Node*>* _prefixNodes=nullptr)
        {
            if (!m_root)
            {
                if (_isCreating)
                {
                    m_root = CreateNode(_T());
                }
                else
                {
                    return nullptr;
                }
            }
            
            Node* node = m_root;
            if (_prefixNodes)
            {
                _prefixNodes->push_back(node);
            }
            for(auto& element : _prefix)
            {
                auto it = node->children.find(element);
                if(it == node->children.end())
                {
                    if (_isCreating)
                    {
                        auto prefix = node->prefix;
                        std::back_inserter(prefix) = element;
                        node->children[element] = CreateNode(prefix);
                    }
                    else
                    {
                        return nullptr;
                    }
                }
                node = node->children[element];
                if (_prefixNodes)
                {
                    _prefixNodes->push_back(node);
                }
            }
            
            return node;
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
