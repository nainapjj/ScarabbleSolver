//
//  main.cpp
//  ScrabbleSolver
//
//  Created by Jeff Nainaparampil on 5/19/13.
//

#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <cstdlib>
#include <string>

#include "PrefixTree.h"
#include "MaxHeap.h"
#include "ScrabbleLookup.h"
using namespace std;

// Hold the constants that are held consistent throughout the
// program.
int WORDS_TO_OUTPUT = 10;
int ASCII_A = 97;
int LETTERS_IN_ALPHABET = 26;

// The structure that holds the possible word restrictions
// for the word.
struct RestrictionNode
{
    char letter;
    int position;
};

// The following variables are vectors holding the different
// permuations of words made using the user inputted collection
// of letters.
vector<string> combinations_pre;
vector<string> combinations;
vector<RestrictionNode> restrictions;
set<string> permutation_set;

// The following function converts the '?' character to
// character 'a' to 'z' using recursion.
void convertQuestionMarks(string word, int index)
{
    // If reached the end of the word, add it to the vector
    if (index == word.length())
        combinations.push_back(word);
    else
        if (word[index] == '?')
            // Change the '?' to all possible letters, and then put back
            // into this funtion
            for (int i = ASCII_A; i < LETTERS_IN_ALPHABET + ASCII_A; i++)
                convertQuestionMarks(word.substr(0, index) + ((char)i) +
                                     word.substr(index+1,string::npos), index+1);
        else
            convertQuestionMarks(word, index+1);
}

// The following function checks to see if the generated word
// follows the rules held by the vector "restrictions"
bool checkRestrictions(string word)
{
    
    for (int i = 0; i < restrictions.size(); i++)
    {
        // Two ways to fail a restriction:
        // 1) The restriction is pointing to an index bigger than the word
        // 2) The character at the index is wrong
        RestrictionNode restric = restrictions[i];
        if (restric.position > word.length())
            return false;
        if (word[restric.position - 1] != restric.letter)
            return false;
    }
    return true;
}

// The following function takes the words from combination_pre
// and changes all of the '?' to letters, then adds them into
// combinations
void convertAllQuestionMarks()
{
    for (int i = 0; i < combinations_pre.size(); i++)
        convertQuestionMarks(combinations_pre[i], 0);
}

// The following function recursively finds all the combinations
// of a set of of letters.
void generate_combinations_recursive(string word, int choose, int min, int currentPos, string currentStr)
{
    if (currentPos == choose)
        combinations_pre.push_back(currentStr);
    else
        for (int x = min + 1; x < word.length(); x++)
            generate_combinations_recursive(word, choose, x, currentPos + 1,
                                            currentStr + word[x]);
}

// Finds the combinations of a set of letters.
void generate_combinations(string word, int choose)
{
    generate_combinations_recursive(word, choose, -1, 0, "");
}

// Finds all of the permutations of a set of letters, recursively
// Then it adds them into a set.
void generate_permutations_recursive(string beforeString, string listOfLetters)
{
    if (listOfLetters.length() == 1) {
        if (checkRestrictions(beforeString + listOfLetters[0])) {
            permutation_set.insert(beforeString + listOfLetters[0]);
        }
    }
    else
        for (int x = 0; x < listOfLetters.length(); x++)
        {
            string newListOfLetters = listOfLetters.substr(0, x) + listOfLetters.substr(x + 1);
            generate_permutations_recursive(beforeString + listOfLetters[x], newListOfLetters);
        }
}

// Finds all of the permutations of a word, and then adds them
// into a set.
void generate_permutations(string word)
{
    generate_permutations_recursive("", word);
}

int main(int argc, const char * argv[])
{
    PrefixTree tree;
    ScrabbleLookup lookup;
    string dictionaryFile;
    
    // Parse the command line argument by looping through all
    // of the command line arguments
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i],"-d") == 0) dictionaryFile = argv[i+1];
    }

    // Open all dictionary file, and import all the words into the
    // trie.
    ifstream myfile;
    myfile.open(dictionaryFile.c_str());
    while (!myfile.eof())
    {
        string word;
        myfile >> word;
        tree.insert(word);
    }
    
    
    // Print tree information.
    cout << "Number of word in tree: " << tree.getNumWord() << endl;
    cout << "Number of nodes in tree: " << tree.getNumNodes() << endl;
    cout << "Maximum depth of the tree: " << tree.getMaxDepth() << endl;
    cout << "Number of bytes in tree: " << tree.getNumBytes() << endl << endl;
    
    // Continue looping the program until all of the words have been entered.
    string word = "";
    while (word != "!")
    {
        MaxHeap heap;
        
        // Prompt the user for the word to solve.
        cout << "Please enter a collection of letters (all lowercase) or questions marks to solve, or ! if you want to quit: ";
        cin >> word;
        
        if (word == "!") break;
        
        cout << endl << "Any restrictions? Please enter the position number of the letter first, and then the character.  An example is 2a for forcing the second letter to be a. Keep entering restrictions, and then enter ! when finished. ";
        string restric = "";
        while (restric != "!")
        {
            cin >> restric;
            if (restric == "!") break;
            RestrictionNode restrictNode;
            restrictNode.letter = restric[1];
            restrictNode.position = atoi(restric.substr(0,1).c_str());
            restrictions.push_back(restrictNode);
        }
    
        // Generate all of the combinations of the collection of letters, and store in a vector.
        for (int x = 0; x <= word.length(); x++)
            generate_combinations(word, x);
        
        // Change all of the question marks in the set to 26 different words per question mark
        convertAllQuestionMarks();
        
        // From the combinations, make permutations of all of the words
        for (int x = 0; x < combinations.size(); x++)
            generate_permutations(combinations[x]);
        
        
        // Iterate through all of the permutations, and include known words into the heap.
        for (set<string>::iterator it = permutation_set.begin();
             it != permutation_set.end(); it++) {
            if (tree.isStored(*it))
            {
                heap.insert(*it, lookup.pointValue(*it));
            }
        }
        
        cout << endl << "The following are the top Scrabble words: " << endl;
        
        // Output the words in order of the word score.
        for (int i = 0; i < WORDS_TO_OUTPUT; i++)
        {
            string word = heap.dequeueMax();
            int score = lookup.pointValue(word);
            if (word != "")
                cout << word << " " << score << endl;
        }
        
        cout << endl;
        
        combinations.clear();
        restrictions.clear();
        combinations_pre.clear();
        permutation_set.clear();
    }
}



