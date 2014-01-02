//
//  ScrabbleLookup.h
//  ScrabbleSolver
//
//  Created by Jeff Nainaparampil on 6/9/13.
//  Copyright (c) 2013 Jeff Nainaparampil. All rights reserved.
//

#ifndef __ScrabbleSolver__ScrabbleLookup__
#define __ScrabbleSolver__ScrabbleLookup__

#include <iostream>
using namespace std;

class ScrabbleLookup
{
private:
    // Array of scrabble point values
    int lookupTable[26];
public:
    ScrabbleLookup();
    int pointValue(string word); // Returns the total point value of a certain word
};

#endif /* defined(__ScrabbleSolver__ScrabbleLookup__) */
