#pragma once
#ifndef _V_AHOCORASICK_H_
#define _V_AHOCORASICK_H_

#include "../TrieTree/VTrieTree.h"
#include <queue>
#include <set>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAhoCorasick
    //----------------------------------------------------------------------------------------------------
    template <typename _T>
    class VAhoCorasick : public VTrieTree<_T>
    {
    protected:
        // Node
        //----------------------------------------------------------------------------------------------------
        struct Node : public VTrieTree<_T>::Node
        {
        public:
            //----------------------------------------------------------------------------------------------------
            inline Node()
                :
                VTrieTree<_T>::Node(),
                failure(nullptr),
                outputs()
            {
            }
            
            //----------------------------------------------------------------------------------------------------
            inline Node(const _T& _prefix, bool _isWhole=false)
                :
                VTrieTree<_T>::Node(_prefix, _isWhole),
                failure(nullptr),
                outputs()
            {
            }
            
            //----------------------------------------------------------------------------------------------------
            inline virtual ~Node()
            {
            }
            
        public:
            //----------------------------------------------------------------------------------------------------
            Node* failure;
            std::set<_T> outputs;
        };

    public:
        //----------------------------------------------------------------------------------------------------
        inline VAhoCorasick()
            :
            VTrieTree<_T>()
        {
        }
        
        //---------------------------------------------------------------------------------------------------
        std::vector<_T> Parse(const _T& _collection)
        {
            std::vector<_T> result;
            if (this->m_root)
            {
                UpdateFailures();
                
                Node *node = (Node*)this->m_root;
                for(auto& element : _collection)
                {
                    node = NextNode(node, element);
                    std::copy(node->outputs.begin(), node->outputs.end(), std::back_inserter(result));
                }
            }
            return result;
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        inline virtual typename VTrieTree<_T>::Node* CreateNode(const _T& _prefix, bool _isWhole=false)
        {
            return new Node(_prefix, _isWhole);
        }
        
        //----------------------------------------------------------------------------------------------------
        inline virtual void AfterInserted(typename VTrieTree<_T>::Node* _node)
        {
            VTrieTree<_T>::AfterInserted(_node);
            if (_node)
            {
                ((Node*)_node)->outputs.insert(_node->prefix);
                m_isFailuresDirty = true;
            }
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void UpdateFailures()
        {
            if (this->m_root && m_isFailuresDirty)
            {
                m_isFailuresDirty = false;
                
                std::queue<Node*> queue;
                // Init first level
                for(auto& pair : this->m_root->children)
                {
                    ((Node*)pair.second)->failure = (Node*)this->m_root;
                    queue.push((Node*)pair.second);
                }
                // Rest level
                while (!queue.empty())
                {
                    Node *node = queue.front();
                    queue.pop();
                    
                    for(auto& pair : node->children)
                    {
                        const typename _T::value_type &element = pair.first;
                        queue.push((Node*)pair.second);
                        
                        Node *failureNode = node->failure;
                        while (failureNode && failureNode->children.find(element) == failureNode->children.end())
                        {
                            failureNode = failureNode->failure; // Case: root failure => null (root)
                        }
                        if (failureNode)
                        {
                            Node *failure = (Node*)failureNode->children[element];
                            ((Node*)pair.second)->failure = failure;
                            ((Node*)pair.second)->outputs.insert(failure->outputs.begin(), failure->outputs.end());
                        }
                        else
                        {
                            ((Node*)pair.second)->failure = (Node*)this->m_root;
                        }
                    }
                }
            }
            
            return;
        }
        
        //----------------------------------------------------------------------------------------------------
        inline Node* NextNode(Node* _node, const typename _T::value_type& _element)
        {
            auto it = _node->children.find(_element);
            if(it == _node->children.end())
            {
                if (_node == this->m_root) // Totally failed
                {
                    return _node;
                }
                else
                {
                    return NextNode(_node->failure, _element);
                }
            }
            else
            {
                return (Node*)it->second;
            }
            return nullptr; // Impossible
        }
        
        
    protected:
        //----------------------------------------------------------------------------------------------------
        bool m_isFailuresDirty;
        
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VAhoCorasickTest();
};

#endif
