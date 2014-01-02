//
//  ScrabbleLookup.cpp
//  ScrabbleSolver
//
//  Created by Jeff Nainaparampil on 6/9/13.
//  Copyright (c) 2013 Jeff Nainaparampil. All rights reserved.
//

#include "ScrabbleLookup.h"

int ASCII_VALUE_FOR_A = 97;

ScrabbleLookup::ScrabbleLookup()
{
    lookupTable[0] = 1;
    lookupTable[1] = 3;
    lookupTable[2] = 3;
    lookupTable[3] = 2;
    lookupTable[4] = 1;
    lookupTable[5] = 4;
    lookupTable[6] = 2;
    lookupTable[7] = 4;
    lookupTable[8] = 1;
    lookupTable[9] = 8;
    lookupTable[10] = 5;
    lookupTable[11] = 1;
    lookupTable[12] = 3;
    lookupTable[13] = 1;
    lookupTable[14] = 1;
    lookupTable[15] = 3;
    lookupTable[16] = 10;
    lookupTable[17] = 1;
    lookupTable[18] = 1;
    lookupTable[19] = 1;
    lookupTable[20] = 1;
    lookupTable[21] = 4;
    lookupTable[22] = 4;
    lookupTable[23] = 8;
    lookupTable[24] = 4;
    lookupTable[25] = 10;
}

// Simply look up function that returns the point value
// of a particular scrabble word
int ScrabbleLookup::pointValue(string word)
{
    int wordValue = 0;
    
    // Loop through word and sum up each letter
    // point value
    for (int i = 0; i < word.length(); i++)
    {
        int letter = word[i] - ASCII_VALUE_FOR_A;
        if (letter < 26 && letter >= 0)
            wordValue += lookupTable[letter];
        else
            cout << "Letter: " << word[i] << " is unrecognized.";
    }
    
    return wordValue;
}