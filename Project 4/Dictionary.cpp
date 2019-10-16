// Dictionary.cpp

// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <utility>      // for swap, std::pair
#include <functional>   // for std::hash
#include <algorithm>
using namespace std;

void removeNonLetters(string& s);

  // This class does the real work of the implementation.

class DictionaryImpl
{
  public:
    DictionaryImpl() {}
    ~DictionaryImpl() {}
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
  private:
    list<pair<string, int>> m_buckets[50000];
};

void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);
    if ( ! word.empty())
    {
        string wordCopy = word;
        sort(wordCopy.begin(), wordCopy.end());
        hash<string> strHash;
        pair<string, int> newPair (word, (int) strHash(wordCopy));
        int arrayLoc = abs((int) strHash(wordCopy) % 50000);
        m_buckets[arrayLoc].push_back(newPair);
    }
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    if (callback == nullptr)
        return;

    removeNonLetters(letters);
    if (letters.empty())
        return;
    
    hash<string> strHash;
    sort(letters.begin(), letters.end());
    int arrayLoc = abs((int) strHash(letters) % 50000);
    list<pair<string, int>>::const_iterator iter = m_buckets[arrayLoc].begin();
    while (iter != m_buckets[arrayLoc].end())
    {
        if ((*iter).second == (int) strHash(letters))
            callback((*iter).first);
        iter++;
    }
}
    
void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}

//******************** Dictionary functions ********************************

// These functions simply delegate to DictionaryImpl's functions.
// You probably don't want to change any of this code

Dictionary::Dictionary()
{
    m_impl = new DictionaryImpl;
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters,callback);
}
