#include "VAhoCorasick.h"
#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // Test
    //----------------------------------------------------------------------------------------------------
    void VAhoCorasickTest()
    {
        VAhoCorasick<std::string> trie;
        trie.Insert("hers");
        trie.Insert("his");
        trie.Insert("she");
        trie.Insert("he");
        auto outputs = trie.Parse("ushers");
        
        return;
    }
}
