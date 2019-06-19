#ifndef __TRIE_H
#define __TRIE_H

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>

int ALPHABET_SIZE = 26;

template <typename T>
class Trie
{
 private:
    int count;
    std::vector<Trie<T> *> children;
    T value;
    bool isEndOfWord;
  public:
    Trie() {}

    Trie(int capacity, T value)
      : count(0),
        children(capacity, NULL),
        value(value) { }

    Trie(int capacity)
      : count(0),
        children(capacity, NULL) { }

    ~Trie() {}

 	void insert(std::string key, T value) {
		// TODO 1 implementati functia de inserare in Trie

    if (key.length() == 0){
      this->value = value;
      isEndOfWord = true;
      return;
    }
    uint32_t nextNode = key.front() - 'a';
    if (children[nextNode] == NULL){
      children[nextNode] = new Trie<T>(ALPHABET_SIZE, value);
      count++;
    }
    key.erase(key.begin());
    children[nextNode]->insert(key, value);
  }

	bool search(std::string key, T &val) {
 		// TODO 1 implementati functia de cautare in Trie
    if (key.length() == 0){
      val = value;
      return isEndOfWord;
    }
    int nextNode = key[0] - 'a';
    if (!children[nextNode]){
      return false;
    }
    key.erase(key.begin());
    return children[nextNode]->search(key, value);
  }

    bool remove(std::string key) {
    	// TODO 2 implementati functia de stergere din Trie
        if(key.length() == 0){
          value = T();
          isEndOfWord = false;
          if(count == 0){
            return true;
          }else {
            return false;
          }
        }
        int nextNode = key[0] - 'a';
        if (children[nextNode] != NULL){
          count--;
          if (children[nextNode]->remove(key.substr(1))){
            delete children[nextNode];
            children[nextNode] = NULL;
            if(count == 0){
              return true;
            }
          }
        }
        return false;
    }


    int numWordsWithPrefix(std::string prefix) {
    	// TODO BONUS implementati gasirea numarului de cuvinte din Trie avand prefixul dat
        return 0;
    }

};
#endif
