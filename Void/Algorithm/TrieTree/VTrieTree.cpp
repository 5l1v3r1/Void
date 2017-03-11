#include "VTrieTree.h"
#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // Test
    //----------------------------------------------------------------------------------------------------
    void VTrieTreeTest()
    {
        VTrieTree<std::string> trie;
        trie.Insert("Hi");
        trie.Insert("Hit");
        trie.Insert("Hint");
        trie.Insert("Hello");
        trie.Insert("Hit");
        trie.Insert("Heat");
        
        auto result = trie.List();
        result = trie.AutoComplete("Hi");
        bool has = trie.Has("Hi");
        has = trie.Has("Hi2");
        has = trie.Has("Hint");
        has = trie.Has("Heata");
        has = trie.Has("Hea");
        
        return;
    }
}
