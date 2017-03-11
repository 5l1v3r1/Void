#pragma once
#ifndef _V_DOUBLEARRAYTRIE_H_
#define _V_DOUBLEARRAYTRIE_H_

#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VDoubleArrayTrie
    //----------------------------------------------------------------------------------------------------
    template <typename _T>
    class VDoubleArrayTrie
    {
    public:
        //----------------------------------------------------------------------------------------------------
        inline VDoubleArrayTrie()
        {
            
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void Build()
        {
            if (m_collections.empty())
            {
                return;
            }
            
            m_childrenTable.clear();
            m_parentTable.clear();
            m_states.clear();
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::vector<_T> m_collections;
        std::vector<int> m_childrenTable; // Base
        std::vector<int> m_parentTable; // Check
        std::vector<_T> m_states;
        
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VDoubleArrayTrieTest();
};

#endif
