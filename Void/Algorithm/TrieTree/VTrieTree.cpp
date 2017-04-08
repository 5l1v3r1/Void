#include "VTrieTree.h"
#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // Test
    //----------------------------------------------------------------------------------------------------
    void VTrieTreeTest()
    {
        VTrieTree<std::string> trie0;
        trie0.Insert("Hi");
        trie0.Insert("Hit");
        trie0.Insert("Hint");
        trie0.Insert("Hello");
        trie0.Insert("Hit");
        trie0.Insert("Heat");
        
        auto result = trie0.List();
        result = trie0.List("Hi");
        bool has = trie0.Has("Hi");
        has = trie0.Has("Hi2");
        has = trie0.Has("Hint");
        has = trie0.Has("Heata");
        has = trie0.Has("Hea");
        
        VTrieTree<std::vector<std::string>> trie1;
        std::vector<std::string> greetings;
        greetings.push_back("Hi");
        greetings.push_back("Hello");
        trie1.MultipleInsert(std::vector<std::string>(), greetings);
        std::vector<std::string> names;
        names.push_back("Mike");
        names.push_back("Maria");
        names.push_back("Maria");
        names.push_back("Maria");
        trie1.MultipleInsert(std::vector<std::string>(1, "Hi"), names);
        trie1.Insert(std::vector<std::string>(1, "Hi"), "Jack");
        auto list1 = trie1.List();
        
        return;
    }
}
