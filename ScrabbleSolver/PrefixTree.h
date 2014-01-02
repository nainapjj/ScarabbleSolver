//
//  PrefixTree.h
//  ScrabbleSolver
//
//  Created by Jeff Nainaparampil on 5/28/13.
//

#ifndef __ScrabbleSolver__PrefixTree__
#define __ScrabbleSolver__PrefixTree__

#include <iostream>
using namespace std;

struct PrefixTreeNode
{
    PrefixTreeNode* nodes[26];
    bool isWord;
};

class PrefixTree
{
private:
    PrefixTreeNode* head;
protected:
    int getNumNodes(PrefixTreeNode *currentNode);
    int getNumWord(PrefixTreeNode *currentNode);
    void printWPrefix(PrefixTreeNode *currentNode, string word);
    void deletePrefixNodes(PrefixTreeNode *currentNode);
    void copyPrefixNode(PrefixTreeNode *currentNode, string word);
    int getMaxDepth(PrefixTreeNode *currentNode);
public:
    PrefixTree();
    PrefixTree(const PrefixTree& copy);
    ~PrefixTree();
    bool insert(string word); // insert function for tree
    bool isStored(string word); // search function for the tree
    bool isEmpty(); // return true is trie is empty
    int getNumWord(); // returns the number of words by traversing the tree
    int getNumNodes(); // returns the number of nodes by traversing the tree
    int getNumBytes(); // returns the number of bytes by traversing the tree
    void printWord(); // prints each word in the tree by traversing the tree
    void printWPrefix(string item); // prints each word with the starting prefix
    void optimize(); // optimize the tree (not implemented)
    int getMaxDepth(); // get the maximum depth of the tree
    
};

#endif /* defined(__ScrabbleSolver__PrefixTree__) */
