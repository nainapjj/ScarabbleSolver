//
//  PrefixTree.cpp
//  ScrabbleSolver
//
//  Created by Jeff Nainaparampil on 5/28/13.
//

#include "PrefixTree.h"

int LETTERS_IN_ALPHABET_C = 26;
int ASCII_A_C = 97;
int POINTER_BYTES = 4;

PrefixTree::~PrefixTree()
{
    deletePrefixNodes(head);
    head = NULL;
}

// Recurively delete each Prefix node in the tree
void PrefixTree::deletePrefixNodes(PrefixTreeNode *currentNode)
{
    for (int i = 0; i < LETTERS_IN_ALPHABET_C; i++)
        if (currentNode->nodes[i] != NULL)
            deletePrefixNodes(currentNode->nodes[i]);
    
    delete currentNode;
}

// Go through the PrefixTree and copy all of it recursively
PrefixTree::PrefixTree(const PrefixTree& copy)
{
    head = new PrefixTreeNode;
    for (int i = 0; i < LETTERS_IN_ALPHABET_C; i++)
        head->nodes[i] = NULL;
    
    copyPrefixNode(copy.head, "");
}

// Copy the Prefix Tree by finding each word in the already created one and inserting them
// into the current one
void PrefixTree::copyPrefixNode(PrefixTreeNode *currentNode, string word)
{
    if (currentNode->isWord) insert(word);
    for (int i = 0; i < LETTERS_IN_ALPHABET_C; i++)
    {
        if (currentNode->nodes[i] != NULL)
        {
            string newWord = word;
            newWord.append(1, (char)(ASCII_A_C + i));
            copyPrefixNode(currentNode->nodes[i], newWord);
        }
    }
}

// Checks to see if word is in tree
bool PrefixTree::isStored(string word)
{
    PrefixTreeNode* currentNode = head;
    
    // Loop through the entire word, until either a wrong character is found
    // or no word is found.
    for (int i = 0; i < word.length(); i++)
    {
        int currentChar = word[i] - ASCII_A_C;
        if (currentNode->nodes[currentChar] != NULL)
            currentNode = currentNode->nodes[currentChar];
        else
            return false;
    }
    
    if (currentNode->isWord)
        return true;
    else
        return false;
}

// Insert a word into the tree
bool PrefixTree::insert(string word)
{
    PrefixTreeNode* currentNode = head;
    
    // Loops for the entire length of the word
    for (int i = 0; i < word.length(); i++)
    {
        int currentChar = word[i] - ASCII_A_C;
        
        // Checks to see if the word with the same prefix
        // is already in the tree.
        if (currentNode->nodes[currentChar] != NULL)
            currentNode = currentNode->nodes[currentChar];
        else
        {
            PrefixTreeNode* newCurrentNode = new PrefixTreeNode;
            for (int i = 0; i < LETTERS_IN_ALPHABET_C; i++)
                newCurrentNode->nodes[i] = NULL;
            currentNode->nodes[currentChar] = newCurrentNode;
            currentNode = newCurrentNode;
        }
    }
    
    currentNode->isWord = true;
    return true;
}

// The default constructor for the prefix tree
PrefixTree::PrefixTree()
{
    head = new PrefixTreeNode;
    
    // Set all of the pointers in the head to NULL
    // initially.
    for (int i = 0; i < LETTERS_IN_ALPHABET_C; i++)
        head->nodes[i] = NULL;
}

// Get the number of bytes by finding the number of nodes
// in the tree and multiplying by the bytes per node
int PrefixTree::getNumBytes()
{
    int numberNodes = getNumNodes();
    return POINTER_BYTES * (LETTERS_IN_ALPHABET_C + 1) * numberNodes;
}

// Returns the number of nodes by using the recursive function.
int PrefixTree::getNumNodes()
{
    return getNumNodes(head);
}

// Recursively finds the number of nodes in a particular subtree
int PrefixTree::getNumNodes(PrefixTreeNode *currentNode)
{
    int numberNodes = 0;
    for (int i = 0; i < LETTERS_IN_ALPHABET_C; i++)
    {
        if (currentNode->nodes[i] != NULL)
            numberNodes += getNumNodes(currentNode->nodes[i]);
    }
    
    return numberNodes + 1;
}

// Returns the max depth of nodes by using the recursive function.
int PrefixTree::getMaxDepth()
{
    return getMaxDepth(head);
}

// Recursively finds the max depth in a particular subtree
int PrefixTree::getMaxDepth(PrefixTreeNode *currentNode)
{
    int maxDepth = 0;
    for (int i = 0; i < LETTERS_IN_ALPHABET_C; i++)
    {
        int newMaxDepth = 0;
        if (currentNode->nodes[i] != NULL)
            newMaxDepth = getMaxDepth(currentNode->nodes[i]);
        if (newMaxDepth > maxDepth)
            maxDepth = newMaxDepth;
    }
    
    return maxDepth + 1;
}

// Returns the number of words by using the recursive function.
int PrefixTree::getNumWord()
{
    return getNumWord(head);
}

// Recursively finds the number of words in a particular subtree
int PrefixTree::getNumWord(PrefixTreeNode *node)
{
    int numberWord = 0;
    for (int i = 0; i < LETTERS_IN_ALPHABET_C; i++)
    {
        if (node->nodes[i] != NULL)
            numberWord += getNumWord(node->nodes[i]);
    }

    if (node->isWord)
        return numberWord + 1;
    else
        return numberWord;
}

// Prints the words of the tree by using the recursive function.
void PrefixTree::printWord()
{
    printWPrefix(head, "");
}

// Public version of the printWPrefix.  First finds
// the appropriate subtree to print, and then calls the recursive
// function.
void PrefixTree::printWPrefix(string item)
{
    PrefixTreeNode *currentNode = head;
    for (int i = 0; i < item.length(); i++)
    {
        currentNode = currentNode->nodes[item[i] - ASCII_A_C];
        if (!currentNode) return;
    }
    
    printWPrefix(currentNode, item);
}

// Recursively prints the number of words in a particular subtree
// The string inputted should be the prefixed word so far.
void PrefixTree::printWPrefix(PrefixTreeNode *currentNode, string word)
{
    if (currentNode->isWord) cout << word << endl;
    for (int i = 0; i < LETTERS_IN_ALPHABET_C; i++)
    {
        if (currentNode->nodes[i] != NULL)
        {
            string newWord = word;
            newWord.append(1, (char)(ASCII_A_C + i));
            printWPrefix(currentNode->nodes[i], newWord);
        }
    }
}
